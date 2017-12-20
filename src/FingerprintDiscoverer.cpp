/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDiscoverer.cpp, FingerprintDiscoverer.h
 * Purpose: Try to load all stored fingerprints of all users on local machine
 *          Doesn't load fingerprint data from dirs where it has no permission to read
 *          So only running it as root can indentify all users.
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

#include <sstream>
#include <iostream>
#include <fstream>
#include <QtGui>
#include <qstring.h>
#include <qwidget.h>
#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

#include "FingerprintDevice.h"
#include "FingerprintData.h"
#include "Fingercodes.h"
#include "DeviceHandler.h"
#include "FingerprintDiscoverer.h"

//constructor to be used for fingerprintIdentifier (for all users)
FingerprintDiscoverer::FingerprintDiscoverer(FingerprintDevice *d,bool debug){
    QString dataPath(DATA_DIR);
    QDir dataDir(dataPath);
    if(!dataDir.exists()){
        syslog(LOG_ERR,"%s does not exist.",DATA_DIR);
//        return;
    }
    device=d;
    numPrints=0;
    allFingerprints=NULL;
    QStringList entryList=dataDir.entryList();
    for(QStringListIterator it(entryList);it.hasNext();){
        QString user(it.next());
        if(QString(".").compare(user)==0)continue;
        if(QString("..").compare(user)==0)continue;
        if(QDir().exists(dataPath+user)){
            syslog(LOG_DEBUG,"Have user: %s.",user.toStdString().data());
            discoverFingerprints(user.toStdString(),device,debug);
        }
    }
}

//constructor to be used for libpam_fingerprint (for a known user only)
FingerprintDiscoverer::FingerprintDiscoverer(FingerprintDevice *d, string user,bool debug){
    device=d;
    numPrints=0;
    allFingerprints=NULL;

    discoverFingerprints(user,d,debug);
}

// public getters and setters --------------------------------------------------
FingerprintData *FingerprintDiscoverer::getIdentifyData(){
    return  allFingerprints;
}

// private helpers -------------------------------------------------------------
void FingerprintDiscoverer::addFingerprintData(FingerprintData *fpd){
    syslog(LOG_DEBUG,"Adding %s -- %s.",fpd->getUserName()->data(),fpd->getFingerName());
    if(allFingerprints==NULL){
        allFingerprints=fpd;
        fpd->next=NULL;
        return;
    }
    for(FingerprintData *fp=allFingerprints;fp!=NULL;fp=fp->next){
        if(fp->next==NULL){
            fp->next=fpd;
            fpd->next=NULL;
            return;
        }
    }
}

// discover stored fingerprints fitting this device for an user in his datadir
void FingerprintDiscoverer::discoverFingerprints(string user,FingerprintDevice *d,bool debug){
    pid_t child;
    int rc;
    struct stat bStat;
    string fname=string(DATA_DIR);
    fname.append(user);
    fname.append("/");
    fname.append(d->getDisplayName(DISPLAY_DRIVER_NAME)->data());
    fname.append("/");

    std::ifstream check(fname.data());
    if(!check){                         //directory does not exists
        syslog(LOG_DEBUG,"Could not open %s",fname.data());
        return;
    }
    for(int f=0;f<10;f++){
        std::ostringstream o;
        o<<f;
        string fileName=string(fname);
        fileName.append(o.str());
        fileName.append(DATA_EXT);
    	if(stat(fileName.data(),&bStat)!=0)	// could not be stated
            continue;

    	if(geteuid()==0){	// running as root (no pkexec needed)
            syslog(LOG_ERR,"Running as root (no pkexec needed).");
            ifstream birFile(fileName.data(),ios_base::binary);
            if(birFile.is_open()){
                birFile.seekg(0,ios::end);
                int dataSize=birFile.tellg();
                if(dataSize==0){
                    birFile.close();
                    continue;
                }
                birFile.seekg(0,ios::beg);
                syslog(LOG_DEBUG,"Reading %s (%d byte).",fileName.data(),dataSize);
                char *birData=new char[dataSize];
                birFile.read((char*)birData,dataSize);
                birFile.close();
                FingerprintData *fpd=NULL;
                fpd=new FingerprintData(user,f,birData,dataSize);
                if(fpd)
                    addFingerprintData(fpd);
                numPrints++;
            }
	}
	else{	// not running as root
            syslog(LOG_ERR,"Not running as root (need pkexec).");
	    string filename=string("");
            filename.append(o.str());
            filename.append(DATA_EXT);
    	    syslog(LOG_DEBUG,"Parent PID: %d.",getpid());
    	    child=fork();           // here we start a child process that copies fingerprint data to tempfile
    	    switch(child){
                case 0:             // This is the child
            	    rc=execl("/usr/bin/pkexec","pkexec",READ_COMMAND,
                        ARG_USER,user.data(),
		        ARG_DRIVER,device->getDisplayName(DISPLAY_DRIVER_NAME)->data(),
		        ARG_FILE,filename.data(),
                        debug?ARG_DEBUG1:NULL,
                        NULL);
            	    syslog(LOG_ERR,"ERROR: Could not execute %s %d (%s).",READ_COMMAND,rc,strerror(errno));
            	    _exit(EXIT_FAILURE);
                case -1:            // Fork error
            	    syslog(LOG_ERR,"ERROR FORKING CHILD PROCESS.");
            	    return;
                default:            // This is the parent
            	    syslog(LOG_DEBUG,"Child PID: %d.",child);
            	    waitpid(child,&rc,0);
            	    if(rc!=EXIT_SUCCESS){
            	        syslog(LOG_ERR,"ERROR: %s returned %d.",READ_COMMAND_NAME,rc);
            	        return;
            	    }
    	    }
	    //read file from /tmp
	    string tempfile=string("/tmp/read-");
	    tempfile.append(filename);
            ifstream birFile(tempfile.data(),ios_base::binary);
            if(birFile.is_open()){
                birFile.seekg(0,ios::end);
                int dataSize=birFile.tellg();
                if(dataSize==0){
                    birFile.close();
                    continue;
                }
                birFile.seekg(0,ios::beg);
                syslog(LOG_DEBUG,"Reading %s (%d byte).",tempfile.data(),dataSize);
                char *birData=new char[dataSize];
                birFile.read((char*)birData,dataSize);
                birFile.close();
                FingerprintData *fpd=NULL;
                fpd=new FingerprintData(user,f,birData,dataSize);
                if(fpd)
                    addFingerprintData(fpd);
                numPrints++;
            }
	    if(unlink(tempfile.data())){
	        syslog(LOG_ERR,"Could not delete file %s!",tempfile.data());
	    }
	}
    }
}


