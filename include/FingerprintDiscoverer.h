/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDiscoverer.cpp, FingerprintDiscoverer.h
 * Purpose: Tries to load all stored fingerprints of all users on local machine
 *          Doesn't load fingerprint data from home dirs where it has no
 *          permission to read, so only running it as root can identify all
 *          users.
 *
 * @author Wolfgang Ullrich
 */

#ifndef _FINGERPRINTDISCOVERER_H
#define _FINGERPRINTDISCOVERER_H

#include "FingerprintData.h"
#include "FingerprintDevice.h"
#include <string>

#include "Globals.h"

using namespace std;

class FingerprintDiscoverer : public QObject {
  Q_OBJECT
private:
  FingerprintDevice *device;
  FingerprintData *allFingerprints; // linked list of discovered fingerprints
  int numPrints;

private:
  void discoverFingerprints(string user, FingerprintDevice *device, bool debug);
  void addFingerprintData(FingerprintData *fpd);

public:
  FingerprintDiscoverer(FingerprintDevice *devices, bool debug);
  FingerprintDiscoverer(FingerprintDevice *devices, string user, bool debug);
  FingerprintData *getIdentifyData();
};

#endif /* _FINGERPRINTDISCOVERER_H */
