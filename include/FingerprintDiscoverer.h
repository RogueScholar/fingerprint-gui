/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDiscoverer.cpp, FingerprintDiscoverer.h
 * Purpose: Try to load all stored fingerprints of all users on local machine
 *          Doesn't load fingerprint data from homedirs where it has no permission to read
 *          So only running it as root can indentify all users.
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

#ifndef _FINGERPRINTDISCOVERER_H
#define	_FINGERPRINTDISCOVERER_H

#include <string>
#include "FingerprintDevice.h"
#include "FingerprintData.h"

#include "Globals.h"

using namespace std;

class FingerprintDiscoverer : public QObject {
    Q_OBJECT
private:
    FingerprintDevice *device;
    FingerprintData *allFingerprints;   //linked list of discovered fingerprints
    int numPrints;

private:
    void discoverFingerprints(string user,FingerprintDevice *device,bool debug);
    void addFingerprintData(FingerprintData *fpd);

public:
    FingerprintDiscoverer(FingerprintDevice *devices,bool debug);
    FingerprintDiscoverer(FingerprintDevice *devices, string user,bool debug);
    FingerprintData *getIdentifyData();
};

#endif	/* _FINGERPRINTDISCOVERER_H */

