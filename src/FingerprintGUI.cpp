/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintGUI.cpp
 * Purpose: Main for fingerprint-gui
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

#include <string>
#include <iostream>
#include <fstream>
#include <QtGui>

#include "ui_FingerprintGUI.h"
#include "MainWindowImpl.h"
#include "DeviceHandler.h"

using namespace std;

bool debugTest=false;
string syslogIdent=string(GUI_NAME);

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    openlog(syslogIdent.data(),LOG_NDELAY|LOG_PID,LOG_AUTH);
    setlogmask(LOG_UPTO(LOG_ERR));
    for(int i=0;i<argc;i++){
        if((strcmp(argv[i],ARG_DEBUG1)==0)
                | (strcmp(argv[i],ARG_DEBUG2)==0)
                | (strcmp(argv[i],ARG_DEBUG3)==0)){
            setlogmask(-1);
            debugTest=true;
        }
    }
    syslog(LOG_INFO,"Started.");
    
    MainWindowImpl mainWindow;
    mainWindow.deviceHandler->rescan();

    mainWindow.show();
    int rc=app.exec();

    mainWindow.deviceHandler->release();
    return rc;
 }
