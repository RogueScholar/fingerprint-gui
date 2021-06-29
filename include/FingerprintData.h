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

#ifndef _FINGERPRINTDATA_H
#define _FINGERPRINTDATA_H
#define QT_I18N 1

#include <QObject>
#include <string>

#include "Fingercodes.h"
#include "Globals.h"

using namespace std;

// FingerprintData holds all required info of a stored fingerprint
class FingerprintData : public QObject {
  Q_OBJECT

  string user;
  int finger;
  void *birData;
  int birSize;

public:
  FingerprintData *next;

public:
  string *getUserName();
  const char *getFingerName();
  FingerprintData(string userName, int finger, void *birData, int birSize);
  void *getData();
  int getSize();
};

#endif /* _FINGERPRINTDATA_H */
