/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintData.cpp, FingerprintData.h
 * Purpose: Object to hold fingerprint data of one finger and user information
 *
 * @author Wolfgang Ullrich
 */

#include "FingerprintData.h"
#include "Fingernames.h"

FingerprintData::FingerprintData(string userName, int fi, void *bir, int size) {
  birData = bir;
  birSize = size;
  user = userName;
  next = nullptr;
  finger = fi;
}

// Public getters and setters
void *FingerprintData::getData() { return birData; }

int FingerprintData::getSize() { return birSize; }

const char *FingerprintData::getFingerName() { return fingers[finger]; }

string *FingerprintData::getUserName() { return &user; }

#include "moc_FingerprintData.cpp"
