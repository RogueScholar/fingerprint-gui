/*
 * SPDX-FileCopyrightText: © 2008-2016 Wolfgang Ullrich <w.ullrich@n-view.net>
 * SPDX-FileCopyrightText: 🄯 2021 Peter J. Mello <admin@petermello.net.>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later OR MPL-2.0
 *
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: DeviceHandler.cpp, DeviceHandler.h
 * Purpose: A module to deal with devices
 *
 * @author Wolfgang Ullrich
 */

#ifndef _DEVICEHANDLER_H
#define _DEVICEHANDLER_H

#include "FingerprintDevice.h"
#include "UsbDevice.h"
#include <QApplication>
#include <QObject>
#include <QtWidgets>
#include <string>

#include "Globals.h"

// Header files for the proprietary "libbsapi" from UPEK
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

/* Insert headers for other proprietary driver libraries here */

using namespace std;

typedef struct {
  int vendorId;
  int deviceId;
  string displayName;
} supportedFingerprintDevice;

typedef enum { DISPLAY_VENDOR_NAME, DISPLAY_DRIVER_NAME } display_name_mode;

class DeviceHandler : public QObject {
  Q_OBJECT

  USBDevice *knownUSBDevices; // Linked list of all known USB devices according
                              // to "usb.ids"
  USBDevice *attachedUSBDevices; // Linked list of all attached USB devices
  struct fp_dscv_dev *
      *discoveredFpDevices; // Fingerprint devices discovered by libfprint
  ABS_DEVICE_LIST
      *discoveredBsDevices; // Fingerprint devices discovered by libbsapi
  FingerprintDevice *fingerprintDevices; // Linked list of all attached and
                                         // supported fingerprint devices
  FingerprintDevice *
      identifierDevices; // Linked list of fingerprint devices that CAN identify
  FingerprintDevice *verifierDevices; // linked list of fingerprint devices that
                                      // CANNOT identify
  FingerprintDevice *currentDevice; // Pointer to the current fingerprint device
                                    // (as chosen by combo box)
  int currentDeviceIndex; // Current fingerprint device index (in combo box)
  display_name_mode displayNameMode;

  // Functions to access the proprietary "libbsapi" from UPEK
  void *bsapiHandle;                            // Handle to loaded library
  ABS_STATUS BSAPI (*bsapiInitFunction)();      // Initialize the library
  ABS_STATUS BSAPI (*bsapiTerminateFunction)(); // Terminate the library
  void BSAPI (*bsapiFreeFunction)( // Free allocated memory in libbsapi
      ABS_DEVICE_LIST *);
  ABS_STATUS
      BSAPI (*bsapiDiscoverFunction)( // Discover devices handled by libbsapi
          const ABS_CHAR *, ABS_DEVICE_LIST **);

  /* Insert functions for other proprietary driver libraries here */

public:
  DeviceHandler(display_name_mode mode);
  ~DeviceHandler();
  USBDevice *getAttachedUsbDevices();
  FingerprintDevice *getCurrentDevice(int *index);
  FingerprintDevice *getFingerprintDevices();
  void setDisplayNameMode(display_name_mode mode);
  FingerprintDevice *getIdentifiers();
  FingerprintDevice *getVerifiers();
  int initialize(); // Initialize all devices
  int release();    // Terminate all devices

public slots:
  void rescan();
  void setCurrentDevice(int index);
signals:
  void deviceAdded(const string displayName);
  void rescanFinished();

private:
  int getKnownUSBDevices();
  int findAttachedUSBDevices();
  USBDevice *findKnownDevice(int vendor, int product);
  void addDevice(FingerprintDevice *fpDevice);
  /* Loaders for proprietary driver libraries */
  // Loader for "libbsapi" from UPEK
  void upekLoader();
  /* Insert loaders for other proprietary driver libraries here */
};

#endif /* _DEVICEHANDLER_H */
