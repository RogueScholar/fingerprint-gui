/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintPolkit.cpp
 * Purpose: Polkit agent for fingerprint authentication
 *
 * @author Wolfgang Ullrich
 */

#include <QApplication>
#include <QtGui>
#include <errno.h>
#include <fcntl.h>
#include <polkit-qt5-1/PolkitQt1/Subject>
#include <qstring.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "../include/Globals.h"
#include "../include/PolkitListener.h"
#include "i18nHelper.h"

static string syslogIdent = string(AGENT_NAME);

int main(int argc, char *argv[]) {
  openlog(syslogIdent.data(), LOG_NDELAY | LOG_PID, LOG_AUTH);
  setlogmask(LOG_UPTO(LOG_ERR));
  for (int i = 0; i < argc; i++) {
    if ((strcmp(argv[i], ARG_DEBUG1) == 0) |
        (strcmp(argv[i], ARG_DEBUG2) == 0) |
        (strcmp(argv[i], ARG_DEBUG3) == 0)) {
      setlogmask(-1);
      syslog(LOG_INFO, "Got \"debug\" argument.");
    }
  }
  syslog(LOG_DEBUG, "started.");

  QApplication agent(argc, argv);
  // Run forever
  loadTranslations(agent);
  agent.setQuitOnLastWindowClosed(false);
  PolkitListener listener;
  PolkitQt1::UnixSessionSubject session(getpid());
  if (listener.registerListener(session, POLKIT_LISTENER_ID)) {
    syslog(LOG_DEBUG, "Listener \"%s\" registered.", POLKIT_LISTENER_ID);
  } else {
    syslog(LOG_ERR, "Could not register listener \"%s\". Aborting.",
           POLKIT_LISTENER_ID);
    return EXIT_FAILURE;
  }
  agent.exec();
  return EXIT_SUCCESS;
}
