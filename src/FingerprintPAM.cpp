/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintPAM.cpp
 * Purpose: Main library to be used for PAM authentication
 *
 * @author  Wolfgang Ullrich
 * Copyright (C) 2008-2016 Wolfgang Ullrich
 */

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/wait.h>
#include <syslog.h>
#include <malloc.h>
#include <errno.h>
#include <pwd.h>
#include <string>

#include "../include/Globals.h"

//#define DEBUG_ALL // Debug all function calls. If not defined pam_sm_authenticate is debugged only

using namespace std;

#define PASS_PROMPT  "Password: "
#define LOGIN_PROMPT "Login: "
#define POLL_TIMEOUT 100    // Timeout for polling the fifo (ms)

#define PAM_SM_AUTH
#include <security/pam_modules.h>
#include <security/_pam_macros.h>

static bool tryFirstIdent=false;
static string firstIdent=string(ARG_TRY_FIRST_IDENT);
static string syslogIdent=string(PAM_NAME);
static bool exitNow=false;

// In case we get killed
static void handler_SIGTERM(int sig){
    if(sig==SIGTERM)
	exitNow=true;
    syslog(LOG_DEBUG,"Got SIGNAL %d (%s).",sig,strsignal(sig));
}

// Check whether a user's homedir is encrypted and not mounted

/* found in: http://ecryptfs.sourceforge.net/README
eCryptfs should only be mounted on (1) empty directories or (2)
directories containing files only created by eCryptfs. If you mount a
directory that has pre-existing files not created by eCryptfs, then
behavior is undefined. Do not run eCryptfs in higher verbosity levels
unless you are doing so for the sole purpose of development, since
secret values will be written out to the system log in that case.
*/

// First we check whether the user's homedir is empty.
// If yes, we assume the homedir to be encrypted and not mounted.
// If no, we look for a file "README.txt" (like found on Ubuntu 9.10) and
// check whether this file is a symlink to a path containing "ecryptfs-utils"
// If yes, we assume the homedir to be encrypted and not mounted.
// Returns true if the homedir seems to be encrypted and not mounted.
bool isEncrypted(const char *homedir){
    char encFile[FILENAME_MAX];
    char encLink[FILENAME_MAX];
    int linkNameSize;
    bool dirEmpty=true;
    DIR *home;
    struct dirent *entry;

    syslog(LOG_DEBUG,"Checking for encrypted homedir \"%s\".",homedir);
    home=opendir(homedir);
    if(home!=NULL){
        while((entry=readdir(home))!=NULL){
            if(string(entry->d_name).compare(".")==0)continue;
            if(string(entry->d_name).compare("..")==0)continue;
            //directory is not empty
            dirEmpty=false;
            break;
        }
        closedir(home);
    }
    else{
        syslog(LOG_ERR,"Could not open homedir \"%s\".",homedir);
        return true;
    }
    if(dirEmpty){
        syslog(LOG_DEBUG,"Homedir \"%s\" is empty; assuming encrypted.",homedir);
        return true;
    }

    // Looking for a file "README.txt"
    sprintf(encFile,"%s/README.txt",homedir);
    struct stat fileStat;
    if(stat(encFile,&fileStat)<0){
        syslog(LOG_DEBUG,"File \"%s/README.txt\" doesn't exist; assuming not encrypted or already mounted.",homedir);
        return false;                   // file seems not to exist
    }
    if(S_ISLNK(fileStat.st_mode)){
        syslog(LOG_DEBUG,"File \"%s/README.txt\" is not a symlink; assuming not encrypted.",homedir);
        return false;                   // file is not a symlink
    }
    if((linkNameSize=readlink(encFile,encLink,FILENAME_MAX))<0){
        syslog(LOG_ERR,"Could not get link filename for \"%s\".",homedir);
        return false;                   // could not get the link filename
    }
    encLink[linkNameSize]='\0';         // terminate the filename
    string s=encLink;
    if(s.find("ecryptfs-utils")==string::npos){
        syslog(LOG_DEBUG,"symlink \"%s/README.txt\" doesn't point to ecryptfs-utils; assuming not encrypted.",homedir);
        return false;                   // sequence "ecryptfs-utils" not found in filename
    }
    syslog(LOG_DEBUG,"Homedir \"%s\" seems to be encrypted and not mounted.",homedir);
    return true;
}

// Get current time in milliseconds
double get_time_ms(){
    struct timeval t;
    gettimeofday(&t,NULL);
    return (t.tv_sec+(t.tv_usec/1000000.0))*1000.0;
}

bool file_exists(const char* filename){
    if(FILE* file=fopen(filename,"r")){
        fclose(file);
        return true;
    }
    return false;
}

static void pam_set_data_free(pam_handle_t*,void *ptr,int){
    if(ptr)free(ptr);
}

void reopenSyslog(bool debug){  // Some evil stuff might have opened their own syslog meanwhile so we open ours again
    closelog();
    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    if(debug)
        setlogmask(-1);
    else
        setlogmask(LOG_UPTO(LOG_ERR));
}

static int pamErrorMessage(pam_handle_t *pamh, char *msg)
{
    struct pam_message message;
    const struct pam_message *pmsg=&message;
    message.msg_style=PAM_ERROR_MSG;
    message.msg=msg;
    const struct pam_conv *conv;
    struct pam_response *resp;

    int rc=pam_get_item(pamh,PAM_CONV,(const void **)&conv);
    if(rc!=PAM_SUCCESS) return 0;
    if(!conv||!conv->conv) return 0;
    return conv->conv(1,&pmsg,&resp,conv->appdata_ptr);
}

#define PAM_SILENT_STR "+PAM_SILENT"
#define PAM_DISALLOW_NULL_AUTHTOK_STR "PAM_DISALLOW_NULL_AUTHTOK"
#define PAM_ESTABLISH_CRED_STR "PAM_ESTABLISH_CRED"
#define PAM_DELETE_CRED_STR "PAM_DELETE_CRED"
#define PAM_REINITIALIZE_CRED_STR "PAM_REINITIALIZE_CRED"
#define PAM_REFRESH_CRED_STR "PAM_REFRESH_CRED"

const char* flag_to_str(unsigned flag){
    switch(flag & ~PAM_SILENT){
	case PAM_DISALLOW_NULL_AUTHTOK: return PAM_DISALLOW_NULL_AUTHTOK_STR;
	case PAM_ESTABLISH_CRED: return PAM_ESTABLISH_CRED_STR;
	case PAM_DELETE_CRED: return PAM_DELETE_CRED_STR;
	case PAM_REINITIALIZE_CRED: return PAM_REINITIALIZE_CRED_STR;
	case PAM_REFRESH_CRED: return PAM_REFRESH_CRED_STR;
    }
    return "UNKNOWN";
}

bool getargs(int argc,const char **argv){
    bool debug=false;

    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    setlogmask(LOG_UPTO(LOG_ERR));
    for(int i=0;i<argc;i++){
        if((strcmp(argv[i],ARG_DEBUG1)==0)
                | (strcmp(argv[i],ARG_DEBUG2)==0)
                | (strcmp(argv[i],ARG_DEBUG3)==0)){
            setlogmask(-1);
            syslog(LOG_INFO,"Got \"debug\" argument.");
	    debug=true;
        }
	else{
            if(strcmp(argv[i],ARG_TRY_FIRST_IDENT)==0){
                syslog(LOG_INFO,"Got \"%s\" argument.",ARG_TRY_FIRST_IDENT);
                tryFirstIdent=true;
            }
            else {
                syslog(LOG_ERR,"WARNING: Got unknown argument \"%s\".",argv[i]);
            }
	}
    }
    return debug;
}

// Call from PAM ---------------------------------------------------------------
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh,int flags,int argc,const char **argv){
    bool debug=false;
    int rc=PAM_AUTHINFO_UNAVAIL;
    const char *rhost=NULL;
    const char *service=NULL;
    const char *sshconn=NULL;
    char *username=NULL;
    const void* firstUsername=NULL;
    char *password=NULL;
    pid_t child;
    int fifo[2];
    char identifiedUser[256]; memset(identifiedUser,0,sizeof(identifiedUser));
    char randomString[256];
    char hostname[HOST_NAME_MAX+1];
    struct stat bStat;
#ifndef _OPENPAM
    struct pam_conv *conv;
    struct pam_message msg;
    const struct pam_message *msgp;
    struct pam_response *resp;
#endif
    char* xdisp=getenv("DISPLAY");
    char* xauth=getenv("XAUTHORITY");
    char X_lock[256];
    int xlock,i;
    struct pollfd pfds;
    struct passwd *p_entry;
    
    debug=getargs(argc,argv);
    if(debug)
	syslog(LOG_INFO,"Pam_sm_authenticate was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");

    // We don't request fingerprints for remote sessions
    pam_get_item(pamh,PAM_RHOST,(const void **)(const void*)&rhost);
    if (rhost!=NULL&&strlen(rhost)>0){  // remote login?
        gethostname(hostname, HOST_NAME_MAX+1);
	if((strcmp(rhost,hostname))!=0){        // yes
            syslog(LOG_DEBUG,"Remote session detected from: %s.",rhost);
            goto auth_return;
        }
        syslog(LOG_DEBUG,"Got PAM_RHOST %s.",rhost);
    }
    else{
        syslog(LOG_DEBUG,"Got no PAM_RHOST.");
    }

    sshconn=getenv("SSH_CONNECTION");
    if(sshconn){  // This is a remote session
        syslog(LOG_DEBUG,"Got SSH_CONNECTION %s, guess this is a remote session.",sshconn);
        goto auth_return;
    }
    syslog(LOG_DEBUG,"Got no SSH_CONNECTION.");

    srand((unsigned)time(NULL));
    memset(randomString,0,sizeof(randomString));
    sprintf(randomString,"%ld",1000000000L+(rand()%1000000000L));
    // If we have a password already; other PAM modules may handle it.
    pam_get_item(pamh,PAM_AUTHTOK,(const void **)(const void*)&password);
    if(password!=NULL){
        syslog(LOG_INFO,"Have a password. Should be handled by other PAM modules.");
        goto auth_return;
    }
    else{
        syslog(LOG_DEBUG,"Have no PAM_AUTHTOK.");
    }
    
    // Requested service
    pam_get_item(pamh,PAM_SERVICE,(const void **)(const void*)&service);
    if (service!=NULL&&strlen(service)>0){
        syslog(LOG_DEBUG,"PAM_SERVICE: %s.",(const char*)service);
	if(strcmp(service,"webmin")==0){	// webmin can not authenticate a user by fingerprint!
            syslog(LOG_INFO,"Have service webmin. Should be handled by other PAM modules.");
            goto auth_return;
	}
 
//!!!! Dirty hack to workaround bug #862559 in lightdm (Ubuntu 11.10)
// Seems fixed since lightdm 1.1.4 (Ubuntu 12.04)
// THIS WILL ONLY WORK WITH DISPLAY :0
        if(xdisp==NULL&&strcmp(service,"lightdm")==0){
                pam_get_item(pamh,PAM_XDISPLAY,(const void **)(const void*)&xdisp);
                if(xdisp==NULL){
                        syslog(LOG_ERR,"APPLYING WORKAROUND FOR lightdm (setting XDISPLAY to :0).");
                        setenv("DISPLAY",":0",-1);
                        xdisp=getenv("DISPLAY");
                }
        }
//!!!! Dirty hack to workaround bug #862559 in lightdm (Ubuntu 11.10)

    }
    else{
        syslog(LOG_ERR,"Have no PAM_SERVICE.");
    }

//!!!! A new dirty hack needed since Ubuntu 12.10. They call pam_sm_authenticate twice from unity greeter and kill the first one
// So we need to kill the first instance of fingerprint-helper
    if(strcmp(service,"lightdm")==0){
        signal(SIGTERM,handler_SIGTERM);
        sleep(1);	//waiting to be killed if we are the first called pam_sm_authenticate. In the hope one second is enough!
        if(exitNow){
	    syslog(LOG_DEBUG,"EXIT");
	    _exit(EXIT_SUCCESS);
        }
        //unset the handler, needed in gnome-scrensaver if ESC is typed while authenticating
        signal(SIGTERM,SIG_DFL);
    }
//!!!! A new dirty hack needed since Ubuntu 12.10. They call pam_sm_authenticate twice from unity greeter

   //==========================================================================
    if(xdisp==NULL){    // Trying to get the xdisplay
        pam_get_item(pamh,PAM_XDISPLAY,(const void **)(const void*)&xdisp);
        if(xdisp==NULL){
            pam_get_item(pamh,PAM_TTY,(const void **)(const void*)&xdisp);
            if(xdisp==NULL||strlen(xdisp)==0){
                syslog(LOG_DEBUG,"Have no PAM_TTY.");
                xdisp=NULL;
            }
            else{
                syslog(LOG_DEBUG,"Have PAM_TTY: %s.",xdisp);
                if(xdisp[0]!=':'){// looks not like a X-Display
                    syslog(LOG_DEBUG,"Have no DISPLAY from PAM_TTY.");
                    xdisp=NULL;
                }
                else{
                    syslog(LOG_DEBUG,"Have DISPLAY %s from PAM_TTY.",xdisp);
                    setenv("DISPLAY",xdisp,-1);
                }
            }
        }
        else{
            if(xdisp[0]!=':'){// looks not like a X-Display
                syslog(LOG_DEBUG,"Have no DISPLAY from pam_get_item.");
                xdisp=NULL;
            }
            else{
                syslog(LOG_DEBUG,"Have DISPLAY %s from pam_get_item.",xdisp);
                setenv("DISPLAY",xdisp,-1);
            }
        }
    }
    else
        syslog(LOG_DEBUG,"Have DISPLAY %s from getenv.",xdisp);

// The following section is only required for systems, who have no XAUTHORITY variable in gdm environment
// Gentoo is a candidate
    if(xdisp!=NULL){
        if(xauth==NULL){    // Trying to get the xauthority
            sprintf(X_lock,"/tmp/.X%s-lock",strtok((char*)&xdisp[1],"."));
            syslog(LOG_DEBUG,"Scanning X-server PID from %s.",X_lock);
            xlock=open(X_lock,O_RDONLY);
            if(xlock>=0){
                if(read(xlock,X_lock,sizeof(X_lock))>0){// reading PID file
                    close(xlock);
                    sscanf(X_lock,"%d",&xlock);
                    syslog(LOG_DEBUG,"Have X-server PID %d.",xlock);
                    sprintf(X_lock,"/proc/%d/cmdline",xlock);
                    xlock=open(X_lock,O_RDONLY);
                    if(xlock>=0){
                        if((i=read(xlock,X_lock,sizeof(X_lock)))>0){// reading commandline
                            close(xlock);
                            for(int j=0;j<i;j++)if(X_lock[j]=='\0')X_lock[j]=' ';
                            syslog(LOG_DEBUG,"Have cmdline %s.",X_lock);
                            // searching for "-auth"
                            for(char *word=strtok(X_lock," ");word!=NULL;word=strtok(NULL," ")){
                                if(strcmp(word,"-auth")==0){
                                    xauth=strtok(NULL," ");
                                    break;
                                }
                            }
                            syslog(LOG_DEBUG,"Have XAUTHORITY %s.",xauth);
                            if(file_exists(xauth)){
                                syslog(LOG_DEBUG,"Setting XAUTHORITY to %s.",xauth);
                            }
                        }
                        close(xlock);
                    }
                }
                close(xlock);
            }
        }
    }

    syslog(LOG_DEBUG,"Have now XDisplay: \"%s\" and XAuth: \"%s\".",xdisp,xauth);
    //==========================================================================
//!!!! Another dirty hack needed since Ubuntu 12.10. They don't set complete environment variables
    if(xdisp!=NULL)setenv("DISPLAY",xdisp,-1);
    if(xauth!=NULL)setenv("XAUTHORITY",xauth,-1);
//!!!! Another dirty hack needed since Ubuntu 12.10. They don't set complete environment variables

    // If an username is available we try to authenticate by fingerprint
    // Otherwise we try to identify the user
    pam_get_item(pamh,PAM_USER,(const void **)(const void*)&username);
    if(username!=NULL){		    // PAM has a username already
        if(strlen(username)==0){    // Uups, got an empty username
            username=NULL;
        }
	else{
	    // pam_get_item limits the username to 8 chars, so we need to get the full username next
	    pam_get_user(pamh,(const char**)&username,NULL);
            syslog(LOG_DEBUG,"Have PAM username \"%s\".",username);
            // Try to compare this username with a saved username from a previous call ("try_first_identified" funtion)
            if(tryFirstIdent){
                if(pam_get_data(pamh,firstIdent.data(),&firstUsername)==PAM_SUCCESS&&firstUsername){
                    if(strcmp((const char *)firstUsername,username)==0){
                        syslog(LOG_INFO,"Found first username \"%s\". Returning PAM_SUCCESS.",(char*)firstUsername);
                        // This is because the user was identified by fingerprint from a previous call in PAM stack:
                        rc=PAM_SUCCESS;
                        goto auth_return;
                    }
                    syslog(LOG_WARNING,"Username and first_username don't match %s(%s).",username,(char*)firstUsername);
                }
            }
        }
    }
    else{
        syslog(LOG_DEBUG,"Have no PAM username.");
    }

    // We create two processes here:
    // Parent will handle the login/auth by username/password at the PAM prompt
    // Child will request fingerprints
    // When fingerprint was recognized child will send username/"random string password"
    // into a pipe and exit PAM prompt by sending the <enter> key
    
    // Create a fifo for the parent process to send "random string password" to child
    // Child resends this "random string password" back to PAM, when fingerprint was recognized
    if(pipe(fifo)==-1){
        syslog(LOG_ERR,"Creating IPC pipe failed.");
        rc=PAM_SYSTEM_ERR;
        goto auth_return;
    }
    
    syslog(LOG_DEBUG,"Parent PID: %d.",getpid());
    if(stat(HELPER_COMMAND,&bStat)!=0){ // helper could not be stated, seems missing
        syslog(LOG_ERR,"ERROR: Could not find %s.",HELPER_COMMAND);
        close(fifo[0]);close(fifo[1]);
        rc=PAM_SYSTEM_ERR;
        goto auth_return;
    }

    child=fork();           // here we start a child process that requests fingerprints
    switch(child){
        case 0:             // This is the child
            //If service is "sudo" in GUI enviroment we need to run fingerprint-helper as the current user (see http://www.gtk.org/setuid.html)
            if(xdisp!=NULL&&service!=NULL&&strcmp(service,"sudo")==0&&username!=NULL){
                p_entry=getpwnam(username); // find the uid of the calling user
                if(p_entry!=NULL){
                    syslog(LOG_DEBUG,"Running helper process with UID %d.",p_entry->pw_uid);
                    if(setreuid(p_entry->pw_uid,p_entry->pw_uid)!=0){
		        syslog(LOG_ERR,"ERROR: Could not setreuid %d.",p_entry->pw_uid);
                    }
                }
            }

            char pipestr_w[10],pipestr_r[10];// Convert pipe handles to string to be given in argv
            sprintf(pipestr_w,"%d",fifo[0]);
            sprintf(pipestr_r,"%d",fifo[1]);
            if(xdisp!=NULL)
                usleep(50000);// We want the helper window to be raised as the last one for being visible on top
            // we use "execl" for running the helper
            rc=execl(HELPER_COMMAND,HELPER_NAME,
                    pipestr_w,
                    pipestr_r,
                    xdisp==NULL?"":xdisp,
                    service,
                    debug?ARG_DEBUG1:"dUmMy1",
                    username!=NULL?ARG_USER:"dUmMy2",
                    username!=NULL?username:"dUmMy3",
                    "dUmMy4",   // reserved
                    "dUmMy5",   // reserved
                    NULL);
            reopenSyslog(debug);
            syslog(LOG_ERR,"ERROR: Child returned %d (%s).",rc,strerror(errno));
            close(fifo[0]);close(fifo[1]);
            rc=PAM_SYSTEM_ERR;
            goto auth_return;
        case -1:            // Fork error
            syslog(LOG_ERR,"ERROR FORKING CHILD PROCESS.");
            close(fifo[0]);close(fifo[1]);
            rc=PAM_SYSTEM_ERR;
            goto auth_return;
        default:            // This is the parent
            syslog(LOG_DEBUG,"Child (helper) PID: %d.",child);
            if(write(fifo[1],randomString,strlen(randomString))<0){
                syslog(LOG_ERR,"ERROR: Writing random string to fifo.");
                goto system_error;
            }
            else{
                syslog(LOG_DEBUG,"Wrote random string to fifo.");
            }

            if(username==NULL){        // user still unknown, prompt for username
                if(pam_get_user(pamh,(const char **)&username,NULL)!=PAM_SUCCESS){
                    reopenSyslog(debug);
                    syslog(LOG_ERR,"ERROR: Prompting for username.");
                    goto system_error;
                }
                reopenSyslog(debug);
                syslog(LOG_DEBUG,"Prompting username returned PAM_SUCCESS.");
                if(strlen(username)==0){    // We have an empty username.
                                            // Maybe the user has pressed <enter> only or fingerprint-helper sent it to the pipe
                    pfds.fd=fifo[0];
                    pfds.events=POLLIN;
                    switch(poll(&pfds,1,POLL_TIMEOUT)){
                        case 0:         // poll timeout, nothing in fifo. User has pressed <enter> only
                            syslog(LOG_WARNING,"Got empty username; nothing in pipe.");
                            //RETURN PAM_AUTHINFO_UNAVAIL and kill child
                            kill(child,SIGUSR2); // Stop child immediately
                            waitpid(child,&rc,0);
                            close(fifo[0]);close(fifo[1]);
                            rc=PAM_AUTHINFO_UNAVAIL;  // Let others in PAM stack handle that
                            goto auth_return;
                        case -1:        // poll error
                            syslog(LOG_ERR,"ERROR polling fifo.");
                            goto system_error;
                        default:        // fingerprint-helper wrote something to fifo
                            username=(char*)malloc(256);
                            memset(username,0,256);
                            if(read(fifo[0],username,256)<=0){
                                syslog(LOG_DEBUG,"ERROR: Read username from pipe (%s).",strerror(errno));
                                goto system_error;
                            }
                            syslog(LOG_DEBUG,"Got username \"%s\" from pipe.",username);
                    }
                }
                if(strlen(username)==0){    // Uups, username is still empty. Something went wrong
                    syslog(LOG_ERR,"ERROR: Got empty username from pipe.");
                    //RETURN PAM_AUTHINFO_UNAVAIL and kill child
                    kill(child,SIGUSR2); // Stop child immediately
                    waitpid(child,&rc,0);
                    close(fifo[0]);close(fifo[1]);
                    rc=PAM_AUTHINFO_UNAVAIL;  // Let others in PAM stack handle that
                    goto auth_return;
                }
                if(pam_set_item(pamh,PAM_USER,username)!=PAM_SUCCESS){
                    reopenSyslog(debug);
                    syslog(LOG_ERR,"ERROR: pam_set_item username.");
                    goto system_error;
                }
                syslog(LOG_DEBUG,"Have username: %s.",username);
                // We send a SIGUSR1 to the child.
                // In case the user has typed the username the child should exit now
                kill(child,SIGUSR1); // Stops child if it didn't send the username
            }
            // At this point we have a username. Let's prompt for a password
	    double startprompt=get_time_ms(); // starttime for prompting
#ifdef _OPENPAM
	    syslog(LOG_DEBUG,"running OPENPAM.");
            if(pam_get_authtok(pamh,PAM_AUTHTOK,(const char **)&password,NULL)!=PAM_SUCCESS){
#else
	    syslog(LOG_DEBUG,"running not OPENPAM.");
	    if(pam_get_item(pamh,PAM_CONV,(const void **)&conv)!=PAM_SUCCESS){
                reopenSyslog(debug);
                syslog(LOG_ERR,"ERROR: Could not get conversation function.");
                goto system_error;
	    }
	    msg.msg_style=PAM_PROMPT_ECHO_OFF;
            msg.msg=PASS_PROMPT;
            msgp=&msg;
            if((*conv->conv)(1,&msgp,&resp,conv->appdata_ptr)!=PAM_SUCCESS){
#endif
                reopenSyslog(debug);
                syslog(LOG_ERR,"ERROR: Prompting for password.");
                goto system_error;
            }
#ifndef _OPENPAM
            if(resp!=NULL){
	        password=resp->resp;
	        free(resp);
	    }
	    else{
		password=NULL;
	    }
#endif
            reopenSyslog(debug);
            syslog(LOG_DEBUG,"Prompting password returned PAM_SUCCESS.");
	    // Some services return immediately from password prompt. 
	    // This causes a deadlock when fingerprint-helper is not started yet.
	    // So we need to wait for helper start in this case.
	    double endprompt=get_time_ms();
	    if(endprompt<(startprompt+1000)){
		syslog(LOG_DEBUG,"Prompting returned within less then 1 second. Waiting 1 sec for helper start.");
		usleep(1000000);
	    }
            pfds.fd=fifo[0];
            pfds.events=POLLIN;
            switch(poll(&pfds,1,POLL_TIMEOUT)){
                case 0:         // poll timeout, nothing in fifo. Maybe we have a password.
                    kill(child,SIGUSR2); // Stop child immediately
                    waitpid(child,&rc,0);
                    close(fifo[0]);close(fifo[1]);
	            if(password!=NULL){
	                if(strlen(password)>0){     // The user has typed something as password
//!!!!!!!!!!!!!!!! USE THIS LOG OUTPUT ONLY FOR DEVELOPMENT !!!!!!!!!!!!!!!!!!!!
//syslog(LOG_DEBUG,"Got password from keyboard \"%s\".",password);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	                    pam_set_item(pamh,PAM_AUTHTOK,password);
		            free(password);
	            	    syslog(LOG_DEBUG,"Got password by keyboard.");
	            	    rc=PAM_IGNORE;  // Let others check the given username/password
	            	    goto auth_return;
	        	}
			else{
	                    syslog(LOG_DEBUG,"Got empty password by keyboard.");
			}
	    	    }
                    rc=PAM_IGNORE;  // Let others check the given username/password
                    goto auth_return;
                case -1:        // poll error
                    syslog(LOG_ERR,"ERROR polling fifo.");
                    goto system_error;
                default:        // fingerprint-helper wrote something to fifo
                    password=(char*)malloc(256);
                    if(read(fifo[0],password,256)<=0){
                        syslog(LOG_DEBUG,"ERROR: Read password from pipe (%s).",strerror(errno));
	                goto system_error;
                    }
                    waitpid(child,&rc,0);   // Child exits itself
                    close(fifo[0]);close(fifo[1]);
                    if(strcmp(randomString,password)==0){   // The correct random number was given by fingerprint-helper
                        free(password);     // No "real" password available
                        syslog(LOG_DEBUG,"User authenticated by fingerprint without password.");
                        struct passwd *passwd;
                        passwd=getpwnam(username);
                        if(!passwd){
                            syslog(LOG_ERR,"No pwd entry for user %s.",username);
                            rc=PAM_SYSTEM_ERR;
                            goto auth_return;
                        }
                        // Check whether the user's homedir is encrypted and not mounted
                        if(isEncrypted(passwd->pw_dir)){
                            // We have an encrypted (not mounted) homedir and no password here
                            // Trying to send a message to the user
                            string msg="!!!ERROR: FOUND ENCRYPTED HOMEDIR BUT NO PASSWORD!!!";
                            pamErrorMessage(pamh,(char*)msg.data());
                            sleep(5);   //let them read the message
                            rc=PAM_AUTH_ERR;
                            goto auth_return;
                        }
                        // homedir is not encrypted or already mounted
                        rc=PAM_SUCCESS; // User authenticated by fingerprint without password
                    }
                    else{   // A "real" password was written by fingerprint-helper to the pipe recovered from ext. media
                        syslog(LOG_DEBUG,"Got password from helper via pipe.");
                        pam_set_item(pamh,PAM_AUTHTOK,password);
//!!!!!!!!!!!!!!!! USE THIS LOG OUTPUT ONLY FOR DEVELOPMENT !!!!!!!!!!!!!!!!!!!!
//syslog(LOG_DEBUG,"Got password from fingerprint-helper \"%s\".",password);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        rc=PAM_IGNORE;  // Let others check the given username/password
                        goto auth_return;
                    }
                    // Here we are sure the user was identifed and authenticated by fingerprint
                    // Store username to PAM for a later call ("try_first_ident" function)
                    char* userName=(char*)malloc(256);
                    strcpy(userName,username);
                    if(pam_set_data(pamh,firstIdent.data(),(void*)userName,pam_set_data_free)!=PAM_SUCCESS){
                        syslog(LOG_ERR,"ERROR: pam_set_data.");
                        rc=PAM_SYSTEM_ERR;
                    }
                    else
                        syslog(LOG_INFO,"pam_set_data: %s.",userName);
                    goto auth_return;
            }
    }
    syslog(LOG_ERR,"This should not happen!");
    rc=PAM_SYSTEM_ERR;  // Something went totally wrong
    goto auth_return;

// Return PAM_SYSTEM_ERR and kill child
system_error:
    kill(child,SIGUSR2); // Stop child immediately
    waitpid(child,&rc,0);
    close(fifo[0]);close(fifo[1]);
    rc=PAM_SYSTEM_ERR;

auth_return:
    syslog(LOG_DEBUG,"Return %d (%s).",rc,
        rc==PAM_SUCCESS?"PAM_SUCCESS":
        rc==PAM_AUTHINFO_UNAVAIL?"PAM_AUTHINFO_UNAVAIL":
        rc==PAM_USER_UNKNOWN?"PAM_USER_UNKNOWN":
        rc==PAM_IGNORE?"PAM_IGNORE":
        rc==PAM_SYSTEM_ERR?"PAM_SYSTEM_ERR":
        rc==PAM_BUF_ERR?"PAM_BUF_ERR":
        rc==PAM_CRED_INSUFFICIENT?"PAM_CRED_INSUFFICIENT":
        rc==PAM_AUTH_ERR?"PAM_AUTH_ERR":
        "unknown");
    closelog();
    unlink(HELPER_PID); // In case there was a pidfile left over
    unlink(PLUGIN_FIFO);

    //!!!! Another dirty hack for lightdm (Ubuntu 11.10)
    // X-Server doesn't restart on logout, when XAUTHORITY and DISPLAY are set to a value :-(
    if((service!=NULL&&strlen(service)>0)&&(strcmp(service,"lightdm")==0)){
        unsetenv("XAUTHORITY");
        unsetenv("DISPLAY");
    }
    return rc;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t */*pamh*/, int flags,int argc, const char *argv[]){
#ifdef DEBUG_ALL
    bool debug=getargs(argc,argv);
    if(debug)
        syslog(LOG_INFO,"pam_sm_setcred was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");
#endif //DEBUG_ALL
    return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t */*pamh*/, int flags,int argc, const char *argv[]){
#ifdef DEBUG_ALL
    bool debug=getargs(argc,argv);
    if(debug)
        syslog(LOG_INFO,"pam_sm_acct_mgmt was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");
#endif //DEBUG_ALL
    return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t */*pamh*/, int flags,int argc, const char *argv[]){
#ifdef DEBUG_ALL
    bool debug=getargs(argc,argv);
    if(debug)
        syslog(LOG_INFO,"pam_sm_open_session was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");
#endif //DEBUG_ALL
    return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t */*pamh*/, int flags,int argc, const char *argv[]){
#ifdef DEBUG_ALL
    bool debug=getargs(argc,argv);
    if(debug)
        syslog(LOG_INFO,"pam_sm_close_session was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");
#endif //DEBUG_ALL
    return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t */*pamh*/, int flags,int argc, const char *argv[]){
#ifdef DEBUG_ALL
    bool debug=getargs(argc,argv);
    if(debug)
        syslog(LOG_INFO,"pam_sm_chauthtok was called with flags 0x%x (%s%s).",flags,flag_to_str(flags),(flags&PAM_SILENT)?PAM_SILENT_STR:"");
#endif //DEBUG_ALL
    return (PAM_SERVICE_ERR);
}

