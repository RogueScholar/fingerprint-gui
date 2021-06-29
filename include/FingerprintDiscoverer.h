/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDiscoverer.cpp, FingerprintDiscoverer.h
 * Purpose: Try to load all stored fingerprints of all users on local machine
 *          Doesn't load fingerprint data from homedirs where it has no
 * permission to read So only running it as root can indentify all users.
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * @author  Wolfgang Ullrich
 * Copyright (C) 2008-2016 Wolfgang Ullrich
 */

/*
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
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
