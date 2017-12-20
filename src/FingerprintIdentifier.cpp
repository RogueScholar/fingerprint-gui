/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: fingerprintIdentifier.cpp
 * Purpose: Main application to be used for fingerprint identifier
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

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <string>

#include "FingerprintDevice.h"
#include "DeviceHandler.h"
#include "FingerprintDiscoverer.h"
#include "ui_FingerprintIdentifier.h"
#include "IdentifierGUI.h"
#include "Fingercodes.h"

static string syslogIdent=string(IDENTIFIER_NAME);

#define IDENTIFIER_RETURN \
    deviceHandler.release();\
    closelog(); \
    return rc;

void printHelp(){
    cerr << "Usage: " << syslogIdent.data() << " [debug] [decorated]" << endl;
    cerr << "\tdebug    \t-- send debug output to syslog" << endl;
    cerr << "\tdecorated\t-- show dialog decoration" << endl;
    cerr << endl;
    cerr << syslogIdent.data() << " identifies users by their fingerprints." << endl;
    cerr << "It returns 0 on success and -1 on error/abort." << endl;
    cerr << "On success the login name of the identified user is sent to stdout." << endl;
    cerr << endl;
}

int main(int argc, char** argv) {
    int rc=-1;
    bool decorated=false;
    bool debug=false;
    QApplication app(argc, argv);

    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    setlogmask(LOG_UPTO(LOG_ERR));
    for(int i=0;i<argc;i++){
        if((strcmp(argv[i],ARG_DEBUG1)==0)
                | (strcmp(argv[i],ARG_DEBUG2)==0)
                | (strcmp(argv[i],ARG_DEBUG3)==0)){
            setlogmask(-1);
	    debug=true;
            continue;
        }
        if(strcmp(argv[i],ARG_DECORATED)==0){
            decorated=true;
            continue;
        }
        if(i>0){
            printHelp();
            return -1;
        }
    }
    syslog(LOG_INFO,"Started.");

    //find "identifier" devices
    FingerprintDevice *devices=NULL;
    DeviceHandler deviceHandler(DISPLAY_DRIVER_NAME);
    deviceHandler.rescan();
    devices=deviceHandler.getIdentifiers();
    
    if(devices==NULL){
        string message="Found no devices that can identify. Aborting.";
        syslog(LOG_ERR,"%s",message.data());
        cerr<<message.data()<<endl;
        IDENTIFIER_RETURN
    }
    if(devices->next!=NULL){
        syslog(LOG_WARNING,"Found more then one devices. Using %s.",devices->getDisplayName(DISPLAY_DRIVER_NAME)->data());
    }
    //collect fingerprints from all users for this device
    FingerprintDiscoverer discoverer(devices,debug);
    FingerprintData *identifyData=discoverer.getIdentifyData();
    if(identifyData==NULL){  // We have no fingerprints at all
        string message="No fingerprintData! Aborting.";
        syslog(LOG_ERR,"%s",message.data());
        cerr<<message.data()<<endl;
        IDENTIFIER_RETURN
    }
    devices->setMode(MODE_IDENTIFY);
    devices->setIdentifyData(identifyData);

    IdentifierGUI mainWindow(decorated,devices,identifyData);
    rc=app.exec();
    if(rc>=0){
        FingerprintData *fingerprintData=identifyData;
        for(int i=0;i<rc;i++)fingerprintData=fingerprintData->next;
        syslog(LOG_DEBUG,"Have index %d (user: %s).",rc,fingerprintData->getUserName()->data());
        cout << fingerprintData->getUserName()->data();    // send username to stdout
    }

    rc=0;
    IDENTIFIER_RETURN
}
