/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: UsbDevice.cpp, UsbDevice.h
 * Purpose: General properties and methods for USB devices
 *
 * @author Wolfgang Ullrich
 */

#ifndef _USBDEVICE_H
#define _USBDEVICE_H

#include <QObject>
#include <QtGui>
#include <libusb-1.0/libusb.h>
#include <string>

using namespace std;

// USB device
class USBDevice {
public:
  int vendorID;
  string vendorName;
  int deviceID;
  string deviceName;
  struct usb_device *device;
  USBDevice *next;

  USBDevice(string vendor, string device);

public:
  QString getDeviceDescriptor();
};

#endif /* _USBDEVICE_H */
