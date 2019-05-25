/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: UsbDevice.cpp, UsbDevice.h
 * Purpose: General properties and methods for USB devices
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

#include <qstring.h>
#include "UsbDevice.h"
#include "DeviceHandler.h"

using namespace std;

USBDevice::USBDevice(string vendor, string device){
    char *nc;
    vendorID=(int)strtol(vendor.c_str(),&nc,16);
    while(*nc==' '&&*nc!='\0')nc++;
    if(*nc=='\0')
        vendorName="unknown";
    else
        vendorName=nc;
    deviceID=(int)strtol(device.c_str(),&nc,16);
    while(*nc==' '&&*nc!='\0')nc++;
    if(*nc=='\0')
        deviceName="unknown";
    else
        deviceName=nc;
    next=NULL;
}

// public getters and setters --------------------------------------------------
QString USBDevice::getDeviceDescriptor(){
    return QString::fromStdString(vendorName+" (0x")+
            QString::number(vendorID,16)+
            QString::fromStdString(") "+deviceName+" (0x")+
            QString::number(deviceID,16)+
            QString::fromStdString(")");
}
