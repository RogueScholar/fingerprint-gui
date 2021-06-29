/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintPlugin.cpp
 * Purpose: Plugin to be used for authentication with gnome-screensaver and
 *          other plugin-aware applications
 *
 * @author Wolfgang Ullrich
 */

#include <QWidget>
#include <string>
#include <syslog.h>
#include <unistd.h>

#include "PluginDialog.h"

using namespace std;

static string syslogIdent = string(PLUGIN_NAME);

int main(int argc, const char **argv) {
  // Create a named pipe to receive messages from fingerprintHelper
  mkfifo(PLUGIN_FIFO, S_IRWXU | S_IRWXG | S_IRWXO);
  chmod(PLUGIN_FIFO, S_IRWXU | S_IRWXG | S_IRWXO);
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
  QApplication app(argc, (char **)argv);
  PluginDialog dialog(nullptr, true);
  syslog(LOG_DEBUG, "PluginDialog created.");
  WId id = dialog.winId(); // Write window-ID to stdout
  syslog(LOG_DEBUG, "WId: %llu sent to stdout.", id);
  fprintf(stdout, "%llu\n", id);
  fflush(stdout);
  dialog.showPlugin();
  return app.exec();
  unlink(PLUGIN_FIFO);
}
