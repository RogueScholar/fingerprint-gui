/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintPlugin.cpp
 * Purpose: Plugin to be used for authentication with gnome-screensaver and other plugin-aware applications
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

#include <syslog.h>
#include <unistd.h>
#include <string>
//#include <qt4/QtGui/qwidget.h>
#include <qwidget.h>

#include "PluginDialog.h"

using namespace std;

static string syslogIdent=string(PLUGIN_NAME);

int main(int argc,const char **argv){
    // Create a named pipe to receive messages from fingerprintHelper
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
        }
    }
    syslog(LOG_DEBUG,"started.");
    QApplication app(argc,(char **)argv);
    PluginDialog dialog(NULL,true);
    syslog(LOG_DEBUG,"PluginDialog created.");
    WId id=dialog.winId();      // Write window-ID to stdout
    syslog(LOG_DEBUG,"WId: %li sent to stdout.",id);
    fprintf(stdout, "%li\n", id);
    fflush(stdout);
    dialog.showPlugin();
    return app.exec();
    unlink(PLUGIN_FIFO);
}

