/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: GenericDevice.cpp, GenericDevice.h
 * Purpose: A device driver wrapper for generic fingerprint devices handled by libfprint
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

#ifndef _GENERICDEVICE_H
#define _GENERICDEVICE_H

#define _MULTI_THREADED

#include <string>
#include <QObject>
#include "UsbDevice.h"

#include "Globals.h"
#include "FingerprintDevice.h"
#include "FingerprintData.h"

using namespace std;

//This struct was copied from libfprint "fp_internal.h" is used only for 
//getting the vendorID and productID of the device to build the display name from.
//This might lead to weird results if the struct is changed in future versions
//of libfprint. It had have been a wise decision to provide a getter function for 
//vendorID and productID of the discovered device in libfprint because the 
//drivername is not sufficient to indentify a device (several devices might use
//the same driver).
#include <libusb-1.0/libusb.h>
struct fp_dscv_dev {
	struct libusb_device *udev;
	struct fp_driver *drv;
	unsigned long driver_data;
	uint32_t devtype;
};

class GenericDevice : public FingerprintDevice
 {
    string displayName;
    string driverName;
    struct fp_dscv_dev *fpDevice;
    struct fp_dev *dev;
    int mode;
    struct fp_print_data *fpData;
    struct fp_print_data **identifyData;

public:
    GenericDevice(struct fp_dscv_dev *fp,USBDevice *knownUSBDevices=NULL);
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
    bool fpDevOpen(struct fp_dscv_dev *fpDevice);
    bool fpDevClose();
    bool acquire();
    bool verify();
    bool identify();

};

#endif /* _GENERICDEVICE_H */
