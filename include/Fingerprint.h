/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: Fingerprint.cpp, Fingerprint.h
 * Purpose: Represents a single fingerprint, its data and the assigned device
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

#ifndef _FINGERPRINT_H
#define _FINGERPRINT_H

#include <QtWidgets>
#include <QLabel>
#include "FingerprintDevice.h"

#include "Globals.h"

using namespace std;

extern bool debugTest;
static volatile bool busy=false;

class Fingerprint : public QObject {
    Q_OBJECT

private:
    int finger;
    int dataSize;
    pthread_t thread;
    void *data; // fingerprint data for this finger (type either uchar* for fprint or struct abs_bir* for libbsapi)
    struct fp_pic_data *fpPic;
    bool valid;
    int stage;
    FingerprintDevice *device;
    // There are 5 empty labels reserved in GUI for user interaction while verify/acquire
    QLabel* textLabels[5];
    QLabel* iconLabels[5];

    string getFilename(string* user);//returns filepath to store the users data to
    bool loadData();                //loads fingerprint data for this finger and this device from file
    bool saveData();                //saves fingerprint data for this finger and this device to disk
    void setAcquireStage(int result);
    void setVerifyStage(int result);
    void initLabels();

public:
    Fingerprint(int finger,FingerprintDevice *device,QLabel* textLabels[5],QLabel* iconLabels[5]);
    bool swipe();
    void cancel();
    bool isBusy();
    bool isValid();
    int  getFinger();
    FingerprintDevice *getDevice();
    void modeVerify();

public slots:
    void newAcquireResult(int result);
    void newVerifyResult(int result,struct fp_pic_data *pic);
signals:
    void neededStages(int stages);
    void acquireFinished(int result,struct fp_pic_data *pic);
    void verifyFinished(int result,struct fp_pic_data *pic);
};

#endif /* _FINGERPRINT_H */
