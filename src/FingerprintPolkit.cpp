/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintPolkit.cpp
 * Purpose: Polkit agent for fingerprint authentication
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

#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <QtGui>
#include <QApplication>
#include <qstring.h>
#include <polkit-qt-1/PolkitQt1/Subject>

#include "../include/PolkitListener.h"
#include "../include/Globals.h"

static string syslogIdent=string(AGENT_NAME);

int main(int argc, char *argv[])
{
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

    QApplication agent(argc,argv);
    // Run forever
    agent.setQuitOnLastWindowClosed(false);
    PolkitListener listener;
    PolkitQt1::UnixSessionSubject session(getpid());
    if(listener.registerListener(session,POLKIT_LISTENER_ID)){
        syslog(LOG_DEBUG,"Listener \"%s\" registered.",POLKIT_LISTENER_ID);
    }
    else{
        syslog(LOG_ERR,"Could not register listener \"%s\". Aborting.",POLKIT_LISTENER_ID);
        return EXIT_FAILURE;
    }
    agent.exec();
    return EXIT_SUCCESS;
}
