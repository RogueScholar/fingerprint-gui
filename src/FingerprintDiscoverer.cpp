/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDiscoverer.cpp, FingerprintDiscoverer.h
 * Purpose: Try to load all stored fingerprints of all users on local machine
 *          Doesn't load fingerprint data from dirs where it has no permission
 *          to read, so only running it as root can identify all users.
 *
 * @author Wolfgang Ullrich
 */

#include <QtGui>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <qstring.h>
#include <qwidget.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "DeviceHandler.h"
#include "Fingercodes.h"
#include "FingerprintData.h"
#include "FingerprintDevice.h"
#include "FingerprintDiscoverer.h"

// Constructor to be used for fingerprintIdentifier (for all users)
FingerprintDiscoverer::FingerprintDiscoverer(FingerprintDevice *d, bool debug) {
  QString dataPath(DATA_DIR);
  QDir dataDir(dataPath);
  if (!dataDir.exists()) {
    syslog(LOG_ERR, "%s does not exist.", DATA_DIR);
    //        return;
  }
  device = d;
  numPrints = 0;
  allFingerprints = nullptr;
  QStringList entryList = dataDir.entryList();
  for (QStringListIterator it(entryList); it.hasNext();) {
    QString user(it.next());
    if (QString(".").compare(user) == 0)
      continue;
    if (QString("..").compare(user) == 0)
      continue;
    if (QDir().exists(dataPath + user)) {
      syslog(LOG_DEBUG, "Have user: %s.", user.toStdString().data());
      discoverFingerprints(user.toStdString(), device, debug);
    }
  }
}

// Constructor to be used for libpam_fingerprint (for a known user only)
FingerprintDiscoverer::FingerprintDiscoverer(FingerprintDevice *d, string user,
                                             bool debug) {
  device = d;
  numPrints = 0;
  allFingerprints = nullptr;

  discoverFingerprints(user, d, debug);
}

// Public getters and setters
FingerprintData *FingerprintDiscoverer::getIdentifyData() {
  return allFingerprints;
}

// Private helpers
void FingerprintDiscoverer::addFingerprintData(FingerprintData *fpd) {
  syslog(LOG_DEBUG, "Adding %s -- %s.", fpd->getUserName()->data(),
         fpd->getFingerName());
  if (allFingerprints == nullptr) {
    allFingerprints = fpd;
    fpd->next = nullptr;
    return;
  }
  for (FingerprintData *fp = allFingerprints; fp != nullptr; fp = fp->next) {
    if (fp->next == nullptr) {
      fp->next = fpd;
      fpd->next = nullptr;
      return;
    }
  }
}

// Discover stored fingerprints fitting this device for a user in his data dir
void FingerprintDiscoverer::discoverFingerprints(string user,
                                                 FingerprintDevice *d,
                                                 bool debug) {
  pid_t child;
  int rc;
  struct stat bStat;
  string fname = string(DATA_DIR);
  fname.append(user);
  fname.append("/");
  fname.append(d->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  fname.append("/");

  std::ifstream check(fname.data());
  if (!check) { // Directory doesn't exist
    syslog(LOG_DEBUG, "Could not open %s", fname.data());
    return;
  }
  for (int f = 0; f < 10; f++) {
    std::ostringstream o;
    o << f;
    string fileName = string(fname);
    fileName.append(o.str());
    fileName.append(DATA_EXT);
    if (stat(fileName.data(), &bStat) != 0) // Could not get state
      continue;

    if (geteuid() == 0) { // Running as root (no pkexec needed)
      syslog(LOG_ERR, "Running as root (no pkexec needed).");
      ifstream birFile(fileName.data(), ios_base::binary);
      if (birFile.is_open()) {
        birFile.seekg(0, ios::end);
        int dataSize = birFile.tellg();
        if (dataSize == 0) {
          birFile.close();
          continue;
        }
        birFile.seekg(0, ios::beg);
        syslog(LOG_DEBUG, "Reading %s (%d byte).", fileName.data(), dataSize);
        char *birData = new char[dataSize];
        birFile.read((char *)birData, dataSize);
        birFile.close();
        FingerprintData *fpd = nullptr;
        fpd = new FingerprintData(user, f, birData, dataSize);
        if (fpd)
          addFingerprintData(fpd);
        numPrints++;
      }
    } else { // Not running as root
      syslog(LOG_ERR, "Not running as root (need pkexec).");
      string filename = string("");
      filename.append(o.str());
      filename.append(DATA_EXT);
      syslog(LOG_DEBUG, "Parent PID: %d.", getpid());
      child = fork(); // Here we start a child process that copies fingerprint
                      // data to a temporary file
      switch (child) {
      case 0: // This is the child
        rc = execl(
            "/usr/bin/pkexec", "pkexec", READ_COMMAND, ARG_USER, user.data(),
            ARG_DRIVER, device->getDisplayName(DISPLAY_DRIVER_NAME)->data(),
            ARG_FILE, filename.data(), debug ? ARG_DEBUG1 : nullptr, nullptr);
        syslog(LOG_ERR, "ERROR: Could not execute %s %d (%s).", READ_COMMAND,
               rc, strerror(errno));
        _exit(EXIT_FAILURE);
      case -1: // Fork error
        syslog(LOG_ERR, "ERROR FORKING CHILD PROCESS.");
        return;
      default: // This is the parent
        syslog(LOG_DEBUG, "Child PID: %d.", child);
        waitpid(child, &rc, 0);
        if (rc != EXIT_SUCCESS) {
          syslog(LOG_ERR, "ERROR: %s returned %d.", READ_COMMAND_NAME, rc);
          return;
        }
      }
      // Read file from /tmp
      string tempfile = string("/tmp/read-");
      tempfile.append(filename);
      ifstream birFile(tempfile.data(), ios_base::binary);
      if (birFile.is_open()) {
        birFile.seekg(0, ios::end);
        int dataSize = birFile.tellg();
        if (dataSize == 0) {
          birFile.close();
          continue;
        }
        birFile.seekg(0, ios::beg);
        syslog(LOG_DEBUG, "Reading %s (%d byte).", tempfile.data(), dataSize);
        char *birData = new char[dataSize];
        birFile.read((char *)birData, dataSize);
        birFile.close();
        FingerprintData *fpd = nullptr;
        fpd = new FingerprintData(user, f, birData, dataSize);
        if (fpd)
          addFingerprintData(fpd);
        numPrints++;
      }
      if (unlink(tempfile.data())) {
        syslog(LOG_ERR, "Could not delete file %s!", tempfile.data());
      }
    }
  }
}

#include "moc_FingerprintDiscoverer.cpp"
