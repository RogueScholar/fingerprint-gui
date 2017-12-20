/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintData.cpp, FingerprintData.h
 * Purpose: Object to hold fingerprint data of one finger and user information
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

#ifndef _FINGERPRINTDATA_H
#define	_FINGERPRINTDATA_H

#include <string>
#include <QObject>

#include "Fingercodes.h"
#include "Globals.h"

using namespace std;

//FingerprintData holds all required infos of a stored fingerprint
class FingerprintData : public QObject
 {
    Q_OBJECT

    string user;
    int finger;
    void * birData;
    int birSize;
public:
    FingerprintData *next;
    
public:
    string *getUserName();
    const char *getFingerName();
    FingerprintData(string userName,int finger,void *birData,int birSize);
    void *getData();
    int getSize();
};

#endif	/* _FINGERPRINTDATA_H */
