/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: DeviceHandler.cpp, DeviceHandler.h
 * Purpose: A module to deal with devices
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

#ifndef _DEVICEHANDLER_H
#define _DEVICEHANDLER_H

#include <string>
#include <QtWidgets>
#include <QObject>
#include "FingerprintDevice.h"
#include "UsbDevice.h"

#include "Globals.h"

// header files for the proprietary "libbsapi" from UPEK
#include "bsapi.h"
#include "bserror.h"
#include "bstypes.h"
#define BSAPI_LIBNAME_40 "libbsapi.so.4.0"
#define BSAPI_LIBNAME_43 "libbsapi.so.4.3"
#define BSAPI_LIBNAME "libbsapi.so"
#define BSAPI_INIT "ABSInitialize"
#define BSAPI_TERMINATE "ABSTerminate"
#define BSAPI_FREE "ABSFree"
#define BSAPI_DISCOVER "ABSEnumerateDevices"

/* insert headers for other proprietary driver libraries here */

using namespace std;

typedef struct {
    int vendorId;
    int deviceId;
    string displayName;
}supportedFingerprintDevice;

typedef enum {
    DISPLAY_VENDOR_NAME,
    DISPLAY_DRIVER_NAME
}display_name_mode;

class DeviceHandler : public QObject {
    Q_OBJECT

    USBDevice* knownUSBDevices;     //linked list of all known USB devices according to "usb.ids"
    USBDevice* attachedUSBDevices;  //linked list of all attached USB devices
    struct fp_dscv_dev** discoveredFpDevices;   //Fingerprint devices discovered by libfprint
    ABS_DEVICE_LIST* discoveredBsDevices;       //Fingerprint devices discovered by libbsapi
    FingerprintDevice* fingerprintDevices;      //linked list of all attached and supported fingerprint devices
    FingerprintDevice* identifierDevices;       //linked list of fingerprint devices that can identify
    FingerprintDevice* verifierDevices;         //linked list of fingerprint devices that can not identify
    FingerprintDevice* currentDevice;           //pointer to current FingerprintDevice (as chosen by ComboBox)
    int currentDeviceIndex;                     //currrent FingerprintDevice (index in ComboBox)
    display_name_mode displayNameMode;

// functions to access the proprietary "libbsapi" from UPEK
    void *bsapiHandle;                              // handle to loaded library
    ABS_STATUS BSAPI (*bsapiInitFunction)();        // initialize the library
    ABS_STATUS BSAPI (*bsapiTerminateFunction)();   // terminate the library
    void BSAPI (*bsapiFreeFunction)(                // free allocated memory in libbsapi
        ABS_DEVICE_LIST*);
    ABS_STATUS BSAPI (*bsapiDiscoverFunction)(      // discover devices handled by libbsapi
        const ABS_CHAR*,ABS_DEVICE_LIST**);

/* insert functions for other proprietary driver libraries here */

public:
    DeviceHandler(display_name_mode mode);
    ~DeviceHandler();
    USBDevice* getAttachedUsbDevices();
    FingerprintDevice* getCurrentDevice(int *index);
    FingerprintDevice* getFingerprintDevices();
    void setDisplayNameMode(display_name_mode mode);
    FingerprintDevice* getIdentifiers();
    FingerprintDevice* getVerifiers();
    int initialize();   // initialize all devices
    int release();      // terminate all devices

public slots:
    void rescan();
    void setCurrentDevice(int index);
signals:
    void deviceAdded(const string displayName);
    void rescanFinished();

private:
    int getKnownUSBDevices();
    int findAttachedUSBDevices();
    USBDevice* findKnownDevice(int vendor, int product);
    void addDevice(FingerprintDevice* fpDevice);
// Libloaders for proprietary driver libraries
    // loader for "libbsapi" from UPEK
    void upekLoader();
/* insert libloaders for other proprietary driver libraries here */
};

#endif	/* _DEVICEHANDLER_H */
