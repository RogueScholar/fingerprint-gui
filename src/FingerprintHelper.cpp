/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintHelper.cpp
 * Purpose: Helper process to be used for PAM authentication
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

#include <QtGui>
#include <QObject>
#include <QEventLoop>
#include <QtCrypto/QtCrypto>

#include <sys/wait.h>
#include <linux/uinput.h>
#include <pwd.h>
#include <fakekey/fakekey.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>
#include "../include/FingerprintDevice.h"
#include "../include/DeviceHandler.h"
#include "../include/FingerprintDiscoverer.h"
#include "../include/PamGUI.h"
#include "../include/PamNonGUI.h"
#include "../include/Fingercodes.h"

#include "../include/Globals.h"
#include "../include/UserSettings.h"

using namespace std;

static string syslogIdent=string(HELPER_NAME);
static volatile bool userSent=false;
static volatile bool exitNow=false;
static const char *user=NULL;

// Send messages to FingerprintPlugin
void pluginMessage(const char *msg){
    int pluginFifo=open(PLUGIN_FIFO,O_WRONLY|O_NDELAY);   // In case we have a fingerprint-plugin running, stop it
    if(pluginFifo<0){ // Maybe there is no fingerprint-plugin listening
//        syslog(LOG_DEBUG,"%s not running.",PLUGIN_NAME);
    }
    else{
//        syslog(LOG_DEBUG,"Opened fifo to %s: %d",PLUGIN_NAME,pluginFifo);
        string fifoMsg(msg); // Compose a message for fingerprint-plugin
        if(write(pluginFifo,fifoMsg.data(),strlen(fifoMsg.data())+1)<0)
            syslog(LOG_ERR,"ERROR: Writing to fifo: %s",strerror(errno));
//        else
//            syslog(LOG_DEBUG,"Wrote to fifo: %s",fifoMsg.data());
        usleep(10000);  // let the plugin read it
        close(pluginFifo);
    }
}

// Send <enter> to uinput
bool uinputSendEnter(int uinput){
    struct input_event event;
    memset(&event,0,sizeof(event));
    // PRESS
    gettimeofday(&event.time,NULL);
    event.type=EV_KEY;
    event.code=KEY_ENTER;
    event.value=1;
    if(write(uinput, &event, sizeof(event))<0){
        syslog(LOG_ERR,"Write to uinput failed (%s).",strerror(errno));
        return false;
    }
    event.type=EV_SYN;
    event.code=SYN_REPORT;
    event.value=0;
    if(write(uinput,&event,sizeof(event))<0){
        syslog(LOG_ERR,"Write to uinput failed (%s).",strerror(errno));
        return false;
    }
    // RELEASE
    gettimeofday(&event.time,NULL);
    event.type=EV_KEY;
    event.code=KEY_ENTER;
    event.value=0;
    if(write(uinput, &event, sizeof(event))<0){
        syslog(LOG_ERR,"Write to uinput failed (%s).",strerror(errno));
        return false;
    }
    event.type=EV_SYN;
    event.code=SYN_REPORT;
    event.value=0;
    if(write(uinput,&event,sizeof(event))<0){
        syslog(LOG_ERR,"Write to uinput failed (%s).",strerror(errno));
        return false;
    }
    return true;
}

int uinputOpen(){
    int uinput=-1;

    uinput=open("/dev/input/uinput",O_WRONLY|O_NDELAY);
    if(uinput<0)
        uinput=open("/dev/misc/uinput",O_WRONLY|O_NDELAY);
    if(uinput<0)
        uinput=open("/dev/uinput",O_WRONLY|O_NDELAY);
    return uinput;
}

// Sends the <enter> key to PAM prompt so PAM prompt exits with an empty line
bool exitPrompt(const char *display,const char *service){
    struct uinput_user_dev dev;
    int uinput=-1;
    int child,rc;
    Display *xdpy;
    FakeKey *fakekey;

    if(strcmp(service,"polkit-1")==0)   // No prompt required
        return false;

    if(display!=NULL){  // We have a X display, using libfakekey
        syslog(LOG_DEBUG,"Using libfakekey to exit PAM conversation.");
        if((xdpy=XOpenDisplay(display))==NULL){
            syslog(LOG_ERR,"ERROR: XOpenDisplay.");
            return false;
        }
        if((fakekey=fakekey_init(xdpy))==NULL){
            syslog(LOG_ERR,"ERROR: Initializing FAKEKEY.");
            return false;
        }
        fakekey_press_keysym(fakekey,XK_Return,0);
        usleep(6000);   // Wait for X to process the key
        fakekey_release(fakekey);
        usleep(6000);   // Wait for X to process the key
    }
    else{   // No X display, using uinput
        syslog(LOG_DEBUG,"Using uinput to exit PAM conversation.");
        uinput=uinputOpen();
        if(uinput<0){      //could not open uinput, trying to load uinput module
            syslog(LOG_DEBUG,"Could not open uinput, trying to load uinput module.");
            child=fork();  // here we start "modprobe" as child process
            switch(child){
                case 0:             // This is the child
                    rc=execl(MODPROBE_COMMAND,"modprobe","uinput",NULL);
                    syslog(LOG_ERR,"ERROR: Child returned %d (%s).",rc,strerror(errno));
                    _exit(EXIT_FAILURE);
                case -1:            // Fork error
                    syslog(LOG_ERR,"ERROR FORKING CHILD PROCESS.");
                    return false;
                default:            // This is the parent, waiting for the child
                    waitpid(child,&rc,0);
            }
            uinput=uinputOpen();    // we try again to open uinput
        }
        if(uinput<0){
            syslog(LOG_ERR,"ERROR: Open uinput failed.");
            return false;
        }
        memset(&dev,0,sizeof(dev));
        strncpy(dev.name,HELPER_NAME,UINPUT_MAX_NAME_SIZE);
        dev.id.version=4;
        dev.id.bustype=BUS_USB;
        ioctl(uinput,UI_SET_EVBIT,EV_KEY);
        ioctl(uinput,UI_SET_EVBIT,EV_REP);
        ioctl(uinput,UI_SET_KEYBIT,KEY_ENTER);
        for(int i=0;i<10;i++)
            ioctl(uinput,UI_SET_KEYBIT,KEY_1+i);
        if(write(uinput,&dev,sizeof(dev))<0){
            syslog(LOG_ERR,"Write to uinput failed (%s).",strerror(errno));
            return false;
        }
        if(ioctl(uinput,UI_DEV_CREATE)){
            syslog(LOG_ERR,"Ioctl uinput failed (%s).",strerror(errno));
            return false;
        }
        uinputSendEnter(uinput);
        close(uinput);
    }
    return true;
}

// Catch SIGUSR1 and SIGUSR2.
// When SIGUSR1 is raised and we have _not_ sent a username to the parent, we can exit because the user has typed the password by keyboard.
// When SIGUSR2 is raised we are requested to exit immediately
static void handler_SIGUSR(int sig){
    switch(sig){
        case SIGUSR1:
            syslog(LOG_DEBUG,"Got SIGUSR1, %s.",userSent?"continuing":"EXIT_SUCCESS");
            if(!userSent){  // We did not send a username to parent
                exitNow=true;   // enforces EXIT_SUCCESS immediately
                qApp->exit(-1);
            }
            return;
        case SIGUSR2:
            syslog(LOG_DEBUG,"Got SIGUSR2, EXIT_SUCCESS.");
            exitNow=true;   // enforces EXIT_SUCCESS immediately
            qApp->exit(-1);
            return;
    }
    syslog(LOG_DEBUG,"Got signal %d (%s), ignoring.",sig,strsignal(sig));
}

// Request fingerprint while PAM propmts for username/password
// Returns false on error, true on success
bool requestFingerprint(int pipe_w,const char *display,char *service,char *username,int argc,char **argv,bool debug){
    int lastResult;
    FingerprintData *identifyData=NULL;
    FingerprintDevice *devices=NULL;

    // Find fingerprint device to be used
    // If no identifier device is found we fallback to verifying the first fingerprint discovered for this user
    int mode=MODE_IDENTIFY;
    DeviceHandler deviceHandler(DISPLAY_DRIVER_NAME);
    deviceHandler.rescan();
    devices=deviceHandler.getIdentifiers();
    
    if(devices==NULL){
        mode=MODE_VERIFY;
        syslog(LOG_WARNING,"WARNING: No devices can identify. Fallback to verifying only.");
        devices=deviceHandler.getVerifiers();
        if(devices==NULL){
            syslog(LOG_WARNING,"No useful devices found.");
            deviceHandler.release();
            return false;
        }
    }
    if(devices->next!=NULL){
        syslog(LOG_WARNING,"Found more then one devices.");
    }
    
    if(username==NULL){             // user not known yet, maybe it's a login
        if(mode==MODE_IDENTIFY){    // device can identify. So identifying the user is possible
            // Find the first device with fingerprints available
            for(;devices!=NULL;devices=devices->next){
                syslog(LOG_DEBUG,"Looking for fingerprints for device %s.",devices->getDisplayName(DISPLAY_DRIVER_NAME)->data());
                FingerprintDiscoverer discoverer(devices,debug);
                identifyData=discoverer.getIdentifyData();
                if(identifyData!=NULL){  // Data for this device available
                    break;
                }
                syslog(LOG_DEBUG,"Nothing found.");
            }
            if(identifyData==NULL){  // We have no fingerprints at all
                syslog(LOG_ERR,"No fingerprintData!");
                deviceHandler.release();
                return false;
            }
            else{
                int i;
                FingerprintData *f=identifyData;
                for(i=0;f!=NULL;f=f->next,i++);
                syslog(LOG_DEBUG,"Have %d fingerprints for all users.",i);
            }
            devices->setMode(MODE_IDENTIFY);
            devices->setIdentifyData(identifyData);

            if(display==NULL){
                //  NonGUI fingerprint identification is not possible! here
                //  If we would implement this, the first tty would open the fingerprint device
                //  and GUI login would never be possible.
                syslog(LOG_WARNING,"Missing X-display (required for login).");
                deviceHandler.release();
                return false;
            }
            else{
                syslog(LOG_INFO,"Have X-display %s. Starting GUI login.",display);
                QApplication app(argc,argv);
                PamGUI gui(devices,identifyData);
                if(!devices->isRunning()){  //something went wrong
                    syslog(LOG_ERR,"ERROR: Device not running!");
                    deviceHandler.release();
                    return false;
                }
                lastResult=app.exec();
            }
            if(lastResult>=0){
                FingerprintData *f=identifyData;
                for(int i=0;i<lastResult;i++)f=f->next;
                user=f->getUserName()->data();
                syslog(LOG_DEBUG,"Have index %d (user: %s).",lastResult,user);
                userSent=true;
                if(write(pipe_w,user,strlen(user)+1)<=0){ // Writing user to fifo
                    syslog(LOG_DEBUG,"ERROR: Writing user to pipe (%s).",strerror(errno));
                    return false;
                }
                exitPrompt(display,service);
                syslog(LOG_DEBUG,"Waiting for SIGUSR1.");
                usleep(1000000); // Will be interrupted by SIGUSR1
                syslog(LOG_DEBUG,"Waiting for PAM to be in password prompt.");
                usleep(100000);   //We need to wait for PAM being in the password prompt
                deviceHandler.release();
                return true;
            }
            else{           // Something went wrong
                syslog(LOG_ERR,"ERROR: GUI exited for unknown reason!");
                deviceHandler.release();
                return false;
            }
        }
        syslog(LOG_WARNING,"User unknown and device cannot identify!");
        deviceHandler.release();
        return false;
    }
    
    // At this point:
    // The user was known already (authentication only)
    syslog(LOG_INFO,"Authenticating USER: %s",username);
    // Find the first device with fingerprints for this user
    for(;devices!=NULL;devices=devices->next){
        syslog(LOG_DEBUG,"Looking for fingerprints for user %s with device %s.",username,devices->getDisplayName(DISPLAY_DRIVER_NAME)->data());
        FingerprintDiscoverer discoverer(devices,username,debug);
        identifyData=discoverer.getIdentifyData();
        if(identifyData!=NULL){  // Data for this user available
            break;
        }
        syslog(LOG_DEBUG,"Nothing found.");
    }
    if(identifyData==NULL){
        syslog(LOG_ERR,"No fingerprint data for this user.");
        deviceHandler.release();
        return false;
    }
    else{
        int i;
        FingerprintData *f=identifyData;
        for(i=0;f!=NULL;f=f->next,i++);
        syslog(LOG_DEBUG,"Have %d fingerprints for %s.",i,username);
    }

    const char *fingername=NULL;
    devices->setMode(mode);

    if(mode==MODE_VERIFY){
        devices->setData(identifyData->getData(),identifyData->getSize());
        fingername=identifyData->getFingerName();
        syslog(LOG_DEBUG,"Verifying %s.",fingername);
    }
    else{
        devices->setIdentifyData(identifyData);
        syslog(LOG_DEBUG,"Identifying all discovered fingerprints from %s.",username);
    }

    if(display==NULL
            // special handling for "su" required since Ubuntu 10.10
            ||strcmp(service,"su")==0   // no widget allowed but libfakekey for prompt required
            ||strcmp(service,"polkit-1")==0 // no widget allowed and no prompt required
        ){  // We can't use the GUI
        syslog(LOG_WARNING,"WARNING: No X-display. Starting command line authentication.");
        QCoreApplication app(argc,argv);
        PamNonGUI nonGui(strcmp(service,"polkit-1"),devices,username,fingername);
        if(!devices->isRunning()){  //something went wrong
            syslog(LOG_ERR,"ERROR: Device not running!");
            deviceHandler.release();
            return false;
        }
        lastResult=app.exec();
    }
    else{
        syslog(LOG_INFO,"Have X-display %s. Starting GUI authentication.",display);
        QApplication app(argc,argv);
        PamGUI gui(devices,username,fingername);
        if(!devices->isRunning()){  //something went wrong
            syslog(LOG_ERR,"ERROR: Device not running!");
            deviceHandler.release();
            return false;
        }
        lastResult=app.exec();
    }
    if(lastResult>=0){  // Fingerprint recognized
        deviceHandler.release();
        return true;
    }
    deviceHandler.release();
    return false;
}

// This is called via "execl" from libpam_fingerprint
// arg[0] -- "fingerprintHelper"
// arg[1] -- pipe to read from pam_fingerprint-gui.so (receiving a random number)
// arg[2] -- pipe to write to pam_fingerprint-gui.so (sending a password if available)
// arg[3] -- DISPLAY variable or empty string (for debugging only)
// arg[4] -- service (the requested service in case it requires special handling)
// more args...
//  "-d", "--debug" for debug
//  "-u <name>", "--user <name>" for username (if known already by PAM)

int main(int argc,char** argv) {
    int pipe_r;
    int pipe_w;
    int rc;
    char *username=NULL;
    char *service=NULL;
    const char *display=getenv("DISPLAY");
    const char *xauth=getenv("XAUTHORITY");
    char randomString[11];
    bool debug=false;

    // Create a named pipe to send messages to plugin
    mkfifo(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
    chmod(PLUGIN_FIFO,S_IRWXU|S_IRWXG|S_IRWXO);
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
        if(strcmp(argv[i],ARG_USER)==0){
            username=argv[++i];
            syslog(LOG_DEBUG,"Have username %s.",username);
	    user=username;
        }
    }
    syslog(LOG_INFO,"Started.");

    for(int i=0;i<argc;i++){
        syslog(LOG_DEBUG,"Arg%d: %s.",i,argv[i]);
    }

    if(argc<4){
        syslog(LOG_ERR,"Wrong number of arguments.\nIt's not intended to start fingerprint-helper manually.\n");
        return(EXIT_FAILURE);
    }
    
    signal(SIGUSR1,handler_SIGUSR);    // Install a handler for SIGUSR1: Exit when we didn't send a username before
    signal(SIGUSR2,handler_SIGUSR);    // Install a handler for SIGUSR2: Exit immediately
    
    sscanf(argv[1],"%d",&pipe_r); // Get the pipe handle for reading from pam_fingerprint-gui.so
    sscanf(argv[2],"%d",&pipe_w); // Get the pipe handle for writing to pam_fingerprint-gui.so
    syslog(LOG_DEBUG,"Have pipe_r %d and pipe_w %d.",pipe_r,pipe_w);

    syslog(LOG_DEBUG,"Have display=%s, XAUTHORITY=%s.",display,xauth);
    //syslog(LOG_DEBUG,"HELPER uid:%d, gid:%d.",getuid(),getgid());

    service=argv[4];
    memset(randomString,'\0',sizeof(randomString));
    if(read(pipe_r,randomString,sizeof(randomString))<=0){
        syslog(LOG_DEBUG,"ERROR: Read random string (%s).",strerror(errno));
        return false;
    }
    if(username==NULL)
        syslog(LOG_DEBUG,"Have no username.");
        
    // If another helper process is running kill him
    FILE *pidfile=fopen(HELPER_PID,"r");
    if(pidfile){
        char pidstr[100];
        int i=fread(pidstr,1,100,pidfile);
        if(i>0)
            pidstr[i]='\0';
        sscanf(pidstr,"%d",&i);
        if(i!=getpid()){
            syslog(LOG_WARNING,"Found another helper process %d, killing it.",i);
            kill(i,SIGUSR2);
            waitpid(i,&rc,0);
	    unlink(HELPER_PID);
            usleep(2000000);   // Wait for devices to stop
        }
        fclose(pidfile);
    }
    pidfile=fopen(HELPER_PID,"w");
    if(pidfile){
        if(fprintf(pidfile,"%d",getpid())>0){
            syslog(LOG_DEBUG,"Wrote pidfile %s.",HELPER_PID);
            fclose(pidfile);
            chmod(HELPER_PID,0666);
        }
    }
    else
        syslog(LOG_WARNING,"Could not write to pidfile.");

    if(!requestFingerprint(pipe_w,display,service,username,argc,argv,debug)){
        pluginMessage(MSG_STOP);
        unlink(HELPER_PID);
        unlink(PLUGIN_FIFO);
        if(exitNow){    // We've got SIGUSR1 or SIGUSR2 before
            closelog();
            return(EXIT_SUCCESS);
        }
        syslog(LOG_ERR,"ERROR: Requesting fingerprint, EXIT_FAILURE.");
        closelog();
        return(EXIT_FAILURE);
    }
// User was identified or authenticated by fingerprint
// Try to get a saved password from external media (USB stick) only when it runs as root (PAM)

    bool havePassword=false;

    if(geteuid()==0){	// running as root
        char *savedPassword;
        // Create a "UserSettings" object
	UserSettings userSettings((char*)user,debug);
	if(userSettings.getPassword(&savedPassword)){
	    syslog(LOG_INFO,"Have password from external media.");
//!!!!!!!!!!!!!!!! USE THIS LOG OUTPUT ONLY FOR DEVELOPMENT !!!!!!!!!!!!!!!!!!!!
//syslog(LOG_INFO,"Have password %s from external media.",savedPassword);
//!!!!!!!!!!!!!!!! USE THIS LOG OUTPUT ONLY FOR DEVELOPMENT !!!!!!!!!!!!!!!!!!!!
    	    if(write(pipe_w,savedPassword,strlen(savedPassword)+1)<=0){ // Writing this password to fifo
        	syslog(LOG_DEBUG,"ERROR: Writing password (%s) to pipe.",strerror(errno));
        	free(savedPassword);
        	pluginMessage(MSG_STOP);
        	closelog();
        	unlink(HELPER_PID);
        	return(EXIT_FAILURE);
    	    }
	    havePassword=true;
	}
    }

    if(havePassword!=true){
	syslog(LOG_INFO,"Have no password from external media.");   // Writing random string to fifo
        if(write(pipe_w,randomString,sizeof(randomString))<=0){
            syslog(LOG_DEBUG,"ERROR: Writing random number (%s) to pipe.",strerror(errno));
            pluginMessage(MSG_STOP);
            closelog();
            unlink(HELPER_PID);
            return(EXIT_FAILURE);
        }
    }
    exitPrompt(display,service);
    syslog(LOG_INFO,"Fingerprint recognized, EXIT_SUCCESS.");
    pluginMessage(MSG_AUTH);
    closelog();
    unlink(HELPER_PID);
    unlink(PLUGIN_FIFO);
    return(EXIT_SUCCESS);
}
