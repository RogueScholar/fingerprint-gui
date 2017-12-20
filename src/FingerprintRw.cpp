/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintRw.cpp
 * Purpose: Helper process running as root and will be called from "fingerprint-gui" only.
 *          Creates DATA_DIR and DATA_DIR/<username>/ if required.
 *          Checks ownership and mode of directories and files
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

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

#include "Globals.h"

using namespace std;

static string syslogIdent=string(RW_COMMAND_NAME);

int main(int argc, char** argv) {
    struct stat bStat;
    struct passwd *passwd;
    bool configfile=false;
    bool put=false;
    string userdir(DATA_DIR);
    string tempdir("/tmp/");
    const char* user=NULL;
    const char* driver=NULL;
    gid_t gid;
    uid_t uid;
    char* filename=NULL;
    FILE *source,*target;
    int ch;

    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    setlogmask(LOG_UPTO(LOG_ERR));
    for(int i=0;i<argc;i++){
        if((strcmp(argv[i],ARG_USER)==0)){
            user=argv[++i];
        }
        if((strcmp(argv[i],ARG_DRIVER)==0)){
            driver=argv[++i];
        }
        if((strcmp(argv[i],ARG_FILE)==0)){
            filename=argv[++i];
        }

        if((strcmp(argv[i],ARG_DEBUG1)==0)
                | (strcmp(argv[i],ARG_DEBUG2)==0)
                | (strcmp(argv[i],ARG_DEBUG3)==0)){
            setlogmask(-1);
            syslog(LOG_INFO,"Got \"debug\" argument.");
        }
    }

    // Are we running as root?
    if(geteuid()!=0){
        syslog(LOG_ERR,"%s is not running as root. Aborting!",RW_COMMAND_NAME);
        return (EXIT_FAILURE);
    }

    syslog(LOG_DEBUG,"Called as %s.",argv[0]);
    if(strstr(argv[0],"fingerprint-rw-read")!=NULL){		// read file
	put=false;
    }
    else{
	if(strstr(argv[0],"fingerprint-rw-write")!=NULL){	// write file
	    put=true;
	}
	else{
	    syslog(LOG_ERR,"Wrong call (%s). Aborting!",argv[0]);
            return (EXIT_FAILURE);
	}
    }

    // Do we have a valid username?
    if(user==NULL){
        syslog(LOG_ERR,"Username unknown. Aborting!");
        return (EXIT_FAILURE);
    }
    passwd=getpwnam(user);
    if(passwd==NULL){
        syslog(LOG_ERR,"Invalid username. Aborting!");
        return (EXIT_FAILURE);
    }
    // users primary group
    gid=passwd->pw_gid;
    // users uid
    uid=passwd->pw_uid;

    //do we have a valid filename?
    if(filename==NULL){
        syslog(LOG_ERR,"Filename unknown. Aborting!");
        return (EXIT_FAILURE);
    }
    if(!strcmp(filename,"config.xml")){
	// config.xml -- no drivername needed
	configfile=true;
    }
    else{
	//birfile must have strlen 5, start with 0...9 and end with ".bir"
	if((*filename<'0')||(*filename>'9')||(strlen(filename)!=5)||(strcmp(filename+1,".bir"))){
	    syslog(LOG_ERR,"Invalid filename (%s). Aborting!",filename);
            return (EXIT_FAILURE);
	}
	// Do we have a drivername?
	if(driver==NULL){
	    syslog(LOG_ERR,"Drivername unknown. Aborting!");
            return (EXIT_FAILURE);
	}
	// drivername must'nt contain a '/'
	if(strstr(driver,"/")){
	    syslog(LOG_ERR,"Invalid drivername (%s). Aborting!",driver);
            return (EXIT_FAILURE);
	}
    }

    syslog(LOG_DEBUG,"Have user:%s, driver:%s, filename:%s.",user,driver,filename);

    // Check sanity of DATA_DIR first
    if(stat(DATA_DIR,&bStat)!=0){           // could not be stated, try to create it
        syslog(LOG_WARNING,"%s doesn't exist. Creating.",DATA_DIR);
        if(mkdir(DATA_DIR,DATA_DIR_MODE)){
            syslog(LOG_ERR,"Could not create %s. Aborting!",DATA_DIR);
            return (EXIT_FAILURE);
        }
        if(chown(DATA_DIR,0,0)){
            syslog(LOG_ERR,"Could not chown %s to root.root. Aborting!",DATA_DIR);
            return (EXIT_FAILURE);
        }
        stat(DATA_DIR,&bStat);              // Stat again
    }
    if(bStat.st_uid!=0||bStat.st_gid!=0){   // check ownership
        syslog(LOG_ERR,"%s not owned by root.root. Aborting!",DATA_DIR);
        return (EXIT_FAILURE);
    }
    syslog(LOG_DEBUG,"%s owned by root.root.",DATA_DIR);
    if((bStat.st_mode&MODE_MASK)!=DATA_DIR_MODE){    // check permissions
        syslog(LOG_ERR,"%s has not mode %o. This directory will be ignored!",DATA_DIR,DATA_DIR_MODE);
        return (EXIT_FAILURE);
    }
    syslog(LOG_DEBUG,"%s has mode %o.",DATA_DIR,bStat.st_mode);

    // Check existance of userdir
    userdir.append(user);
    if(stat(userdir.data(),&bStat)!=0){     // could not be stated, try to create it
        syslog(LOG_DEBUG,"%s doesn't exist. Creating.",userdir.data());
        if(mkdir(userdir.data(),USER_DIR_MODE)){
            syslog(LOG_ERR,"Could not create %s. Aborting!",userdir.data());
            return (EXIT_FAILURE);
        }
        if(chown(userdir.data(),0,0)){
            syslog(LOG_ERR,"Could not chown %s to root.root. Aborting!",userdir.data());
            return (EXIT_FAILURE);
        }
        stat(userdir.data(),&bStat);        // Stat again
    }

    // Check ownership and permissions of userdir
    if(bStat.st_uid!=0||bStat.st_gid!=0){   // check ownership
        syslog(LOG_ERR,"%s not owned by root.root. This directory will be ignored!",userdir.data());
        return (EXIT_FAILURE);
    }
    if((bStat.st_mode&MODE_MASK)!=USER_DIR_MODE){                // check permissions
        syslog(LOG_ERR,"%s has not mode %o. This directory will be ignored!",userdir.data(),USER_DIR_MODE);
        return (EXIT_FAILURE);
    }
    syslog(LOG_DEBUG,"%s is owned by root.root with mode %o.",userdir.data(),bStat.st_mode);

    if(!configfile){	//is birfile, need driverdir
	// Check existance of driverdir
	userdir.append("/");
	userdir.append(driver);
	if(stat(userdir.data(),&bStat)!=0){     // could not be stated, try to create it
            syslog(LOG_DEBUG,"%s doesn't exist. Creating.",userdir.data());
            if(mkdir(userdir.data(),USER_DIR_MODE)){
                syslog(LOG_ERR,"Could not create %s. Aborting!",userdir.data());
                return (EXIT_FAILURE);
            }
            if(chown(userdir.data(),0,0)){
		syslog(LOG_ERR,"Could not chown %s to root.root. Aborting!",userdir.data());
		return (EXIT_FAILURE);
            }
            stat(userdir.data(),&bStat);        // Stat again
    	}

	// Check ownership and permissions of driverdir
	if(bStat.st_uid!=0||bStat.st_gid!=0){   // check ownership
            syslog(LOG_ERR,"%s not owned by root.root. This directory will be ignored!",userdir.data());
            return (EXIT_FAILURE);
    	}
    	if((bStat.st_mode&MODE_MASK)!=USER_DIR_MODE){                // check permissions
            syslog(LOG_ERR,"%s has not mode %o. This directory will be ignored!",userdir.data(),USER_DIR_MODE);
            return (EXIT_FAILURE);
    	}
    	syslog(LOG_DEBUG,"%s is owned by root.root with mode %o.",userdir.data(),bStat.st_mode);
    }

    userdir.append("/");userdir.append(filename);
    if(put){	//save file
    	tempdir.append(filename);
	// copy file from /tmp to userdir
	source=fopen(tempdir.data(),"rb");
	target=fopen(userdir.data(),"wb");
	if((source==NULL)||(target==NULL)){
	    syslog(LOG_ERR,"Could not copy file %s to %s!",tempdir.data(),userdir.data());
            return (EXIT_FAILURE);
	}
    }
    else{	//get file
    	tempdir.append("read-");	//read files are named "read-{0-9}.bir"
    	tempdir.append(filename);
	// check ownership and permissions first
	if(stat(userdir.data(),&bStat)!=0){     // could not be stated
	    syslog(LOG_ERR,"Could not stat file %s!",userdir.data());
            return (EXIT_FAILURE);
	}
	if((bStat.st_uid!=0)||(bStat.st_gid!=0)){ // file has wrong ownership
	    syslog(LOG_ERR,"File %s is not owned by root.root -- ignoring.",userdir.data());
            return (EXIT_FAILURE);
	}
	syslog(LOG_DEBUG,"File %s is owned by root.root.",userdir.data());
	if((bStat.st_mode&MODE_MASK)!=(configfile?CONFIG_FILE_MODE:BIR_FILE_MODE)){ //Wrong file permissions
            syslog(LOG_ERR,"Mode of %s is \"%o\", must be \"%o\" -- ignoring.",userdir.data(),bStat.st_mode&MODE_MASK,configfile?CONFIG_FILE_MODE:BIR_FILE_MODE);
            return (EXIT_FAILURE);
	}
	syslog(LOG_DEBUG,"%s has mode \"%o\" -- OK.",userdir.data(),bStat.st_mode&MODE_MASK);

	// copy file from userdir to /tmp
	source=fopen(userdir.data(),"rb");
	target=fopen(tempdir.data(),"wb");
	if((source==NULL)||(target==NULL)){
	    syslog(LOG_ERR,"Could not copy file %s to %s!",userdir.data(),tempdir.data());
            return (EXIT_FAILURE);
	}
    }
    while((ch=fgetc(source))!=EOF)fputc(ch,target);
    fclose(source);
    fclose(target);

    // set ownership and permissions of target
    if(put){
	// remove sourcefile
	if(unlink(tempdir.data())){
	    syslog(LOG_ERR,"Could not delete file %s. Aborting!",tempdir.data());
	    return (EXIT_FAILURE);
	}
    	if(chown(userdir.data(),0,0)){
	    syslog(LOG_ERR,"Could not chown %s to root.root. Aborting!",userdir.data());
	    return (EXIT_FAILURE);
        }
        if(chmod(userdir.data(),configfile?CONFIG_FILE_MODE:BIR_FILE_MODE)){
	    syslog(LOG_ERR,"Could not chmod %s to %o. Aborting!",userdir.data(),configfile?CONFIG_FILE_MODE:BIR_FILE_MODE);
	    return (EXIT_FAILURE);
        }
    }
    else{
	//tempfile must be removed by the reading module!
    	if(chown(tempdir.data(),uid,gid)){
	    syslog(LOG_ERR,"Could not chown %s to %d.%d. Aborting!",tempdir.data(),uid,gid);
	    return (EXIT_FAILURE);
        }
        if(chmod(tempdir.data(),TMP_FILE_MODE)){
	    syslog(LOG_ERR,"Could not chmod %s to %o. Aborting!",tempdir.data(),TMP_FILE_MODE);
	    return (EXIT_FAILURE);
        }
    }
    syslog(LOG_DEBUG,"%s OK.",userdir.data());
    return (EXIT_SUCCESS);
}

