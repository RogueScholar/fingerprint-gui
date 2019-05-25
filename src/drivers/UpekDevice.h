/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: UpekDevice.cpp, UpekDevice.h
 * Purpose: A device driver wrapper for fingerprint devices from UPEK inc. (former SGS Thomson)
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

#ifndef _UPEKDEVICE_H
#define _UPEKDEVICE_H

#define _MULTI_THREADED

#include <string>
#include <QObject>
#include "UsbDevice.h"

#include "Globals.h"
#include "FingerprintDevice.h"
#include "bsapi.h"
#include "bserror.h"
#include "bstypes.h"

#define BSAPI_OPEN "ABSOpen"
#define BSAPI_CLOSE "ABSClose"
#define BSAPI_ERROR "ABSGetLastErrorInfo"
#define BSAPI_CANCEL "ABSCancelOperation"
#define BSAPI_ENROLL "ABSEnroll"
#define BSAPI_VERIFY "ABSVerify"
#define BSAPI_PROPERTY "ABSGetDeviceProperty"


#define BSAPI_SETLED "ABSSetLED"


#define UPEK_CFG "/etc/upek.cfg"    // NVM configuration file

using namespace std;

//UpekDevice
class UpekDevice : public FingerprintDevice
 {
    string displayName;
    string driverName;
    string bsDevice;
    int mode;
    ABS_BIR **identifyData;
    int numIdentify;
    ABS_BIR* bsData;
    ABS_CONNECTION conn;
    int absFlag;

    // runtime dynamic loaded library libbsapi.so
    void *bsapiHandle;                          // handle to loaded library
    ABS_STATUS BSAPI (*bsapiOpenFunction)(      // open an UPEK device
        const ABS_CHAR*,
        ABS_CONNECTION*);
    ABS_STATUS BSAPI (*bsapiCloseFunction)(     // close an UPEK device
        ABS_CONNECTION);
    void (*bsapiErrorFunction)(                 // get last error
        ABS_DWORD*,
        const ABS_CHAR**);
    ABS_STATUS BSAPI (*bsapiCancelFunction)(    // cancel operation
        ABS_CONNECTION,
        int);
    ABS_STATUS BSAPI (*bsapiEnrollFunction)(    // enroll a fingerprint
        ABS_CONNECTION,
        ABS_OPERATION*,
        ABS_BIR**,
        ABS_DWORD);
    ABS_STATUS BSAPI (*bsapiVerifyFunction)(    // verify a fingerprint
        ABS_CONNECTION,
        ABS_OPERATION*,
        ABS_DWORD,
        ABS_BIR**,
        ABS_LONG*,
        ABS_DWORD);
    ABS_STATUS BSAPI (*bsapiPropertyFunction)(  // get device property
        ABS_CONNECTION,
        ABS_DWORD,
        ABS_DATA**);
    ABS_STATUS BSAPI (*bsapiSetledFunction)(    // set LED mode
        ABS_CONNECTION,
        ABS_DWORD,
        ABS_DWORD,
        ABS_DWORD);

public:
    UpekDevice(void *,struct abs_device_list_item *bs,USBDevice *knownUSBDevices=NULL);
    void emitAcquireResult(int result);
    void emitVerifyResult(int result);
    string* getDisplayName(int);            //returns a display name for this device
    bool canIdentify();
    void setData(void *data,int size);      //loads data into driver
    int getData(void **d,struct fp_pic_data **pic);                  //gets data, return datasize
    void setMode(int mode);
    void setTimeout(bool timeout);          //timeot after OPERATION_TIMEOUT if true
    void setIdentifyData(FingerprintData *identifyData);
    void stop();

protected:
    void run();
private :
    bool acquire();
    bool verify();
    bool identify();
    bool bsDevOpen(string bsDevice,ABS_CONNECTION *conn);
};

#endif /* _UPEKDEVICE_H */
