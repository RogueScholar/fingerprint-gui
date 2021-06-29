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

#include "UsbDevice.h"
#include "DeviceHandler.h"
#include <qstring.h>

using namespace std;

USBDevice::USBDevice(string vendor, string device) {
  char *nc;
  vendorID = (int)strtol(vendor.c_str(), &nc, 16);
  while (*nc == ' ' && *nc != '\0')
    nc++;
  if (*nc == '\0')
    vendorName = "unknown";
  else
    vendorName = nc;
  deviceID = (int)strtol(device.c_str(), &nc, 16);
  while (*nc == ' ' && *nc != '\0')
    nc++;
  if (*nc == '\0')
    deviceName = "unknown";
  else
    deviceName = nc;
  next = nullptr;
}

// Public getters and setters
QString USBDevice::getDeviceDescriptor() {
  return QString::fromStdString(vendorName + " (0x") +
         QString::number(vendorID, 16) +
         QString::fromStdString(") " + deviceName + " (0x") +
         QString::number(deviceID, 16) + QString::fromStdString(")");
}
