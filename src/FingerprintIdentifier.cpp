/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: fingerprintIdentifier.cpp
 * Purpose: Main application to be used for fingerprint identifier
 *
 * @author Wolfgang Ullrich
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>

#include "DeviceHandler.h"
#include "Fingercodes.h"
#include "FingerprintDevice.h"
#include "FingerprintDiscoverer.h"
#include "IdentifierGUI.h"
#include "ui_FingerprintIdentifier.h"

static string syslogIdent = string(IDENTIFIER_NAME);

#define IDENTIFIER_RETURN                                                      \
  deviceHandler.release();                                                     \
  closelog();                                                                  \
  return rc;

void printHelp() {
  cerr << "Usage: " << syslogIdent.data() << " [debug] [decorated]" << endl;
  cerr << "\tdebug    \t-- send debug output to syslog" << endl;
  cerr << "\tdecorated\t-- show dialog decoration" << endl;
  cerr << endl;
  cerr << syslogIdent.data() << " identifies users by their fingerprints."
       << endl;
  cerr << "It returns 0 on success and -1 on error/abort." << endl;
  cerr << "On success the login name of the identified user is sent to stdout."
       << endl;
  cerr << endl;
}

int main(int argc, char **argv) {
  int rc = -1;
  bool decorated = false;
  bool debug = false;
  QApplication app(argc, argv);

  openlog(syslogIdent.data(), LOG_NDELAY | LOG_PID, LOG_AUTH);
  setlogmask(LOG_UPTO(LOG_ERR));
  for (int i = 0; i < argc; i++) {
    if ((strcmp(argv[i], ARG_DEBUG1) == 0) |
        (strcmp(argv[i], ARG_DEBUG2) == 0) |
        (strcmp(argv[i], ARG_DEBUG3) == 0)) {
      setlogmask(-1);
      debug = true;
      continue;
    }
    if (strcmp(argv[i], ARG_DECORATED) == 0) {
      decorated = true;
      continue;
    }
    if (i > 0) {
      printHelp();
      return -1;
    }
  }
  syslog(LOG_INFO, "Started.");

  // Find identifier devices
  FingerprintDevice *devices = nullptr;
  DeviceHandler deviceHandler(DISPLAY_DRIVER_NAME);
  deviceHandler.rescan();
  devices = deviceHandler.getIdentifiers();

  if (devices == nullptr) {
    string message = "Found no devices that can identify. Aborting.";
    syslog(LOG_ERR, "%s", message.data());
    cerr << message.data() << endl;
    IDENTIFIER_RETURN
  }
  if (devices->next != nullptr) {
    syslog(LOG_WARNING, "Found more then one devices. Using %s.",
           devices->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  }
  // Collect fingerprints from all users for this device
  FingerprintDiscoverer discoverer(devices, debug);
  FingerprintData *identifyData = discoverer.getIdentifyData();
  if (identifyData == nullptr) { // We have no fingerprints at all
    string message = "No fingerprintData! Aborting.";
    syslog(LOG_ERR, "%s", message.data());
    cerr << message.data() << endl;
    IDENTIFIER_RETURN
  }
  devices->setMode(MODE_IDENTIFY);
  devices->setIdentifyData(identifyData);

  IdentifierGUI mainWindow(decorated, devices, identifyData);
  rc = app.exec();
  if (rc >= 0) {
    FingerprintData *fingerprintData = identifyData;
    for (int i = 0; i < rc; i++)
      fingerprintData = fingerprintData->next;
    syslog(LOG_DEBUG, "Have index %d (user: %s).", rc,
           fingerprintData->getUserName()->data());
    cout << fingerprintData->getUserName()->data(); // Send username to stdout
  }

  rc = 0;
  IDENTIFIER_RETURN
}
