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

/*
 * DeviceHandler maintains a list of all available USB devices and a list of all
 * attached and supported fingerprint reader devices.
 *
 * In the first step, a list of all known vendor-ids and device-ids is derived
 * from the file usb.ids that is located in the program resources and was found
 * on <http://www.linux-usb.org/usb-ids.html>. This is only to be able to show a
 * list of all attached USB devices at GUI startup/re-scan.
 *
 * In the second step, the list of attached USB devices is created and can be
 * obtained by getAttachedUsbDevices().
 *
 * In the third step, a list of attached and supported fingerprint readers is
 * created. On adding a device, the signal "deviceAdded" is emitted.
 *
 * Calling getIdentifiers returns a list of fingerprint devices that can
 * identify. Calling getVerifiers returns a list of fingerprint devices that can
 * verify only.
 */

#include "../include/DeviceHandler.h"
#include "../include/FingerprintDevice.h"
#include "../include/UsbDevice.h"
#include "drivers/GenericDevice.h"
#include "drivers/UpekDevice.h"
#include <QComboBox>
#include <QString>
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

DeviceHandler::DeviceHandler(display_name_mode mode) {
  knownUSBDevices = nullptr;
  attachedUSBDevices = nullptr;
  discoveredFpDevices = nullptr;
  discoveredBsDevices = nullptr;
  fingerprintDevices = nullptr;
  currentDevice = nullptr;
  currentDeviceIndex = 0;
  identifierDevices = nullptr;
  verifierDevices = nullptr;
  displayNameMode = mode;

  // Trying to load libbsapi from UPEK
  upekLoader();

  /* Call loaders for other proprietary driver libraries here */

  initialize();
  if (mode == DISPLAY_VENDOR_NAME) // Used for GUI
    getKnownUSBDevices();
}

DeviceHandler::~DeviceHandler() {
  //    release();
}

// Public getters and setters
USBDevice *DeviceHandler::getAttachedUsbDevices() { return attachedUSBDevices; }

FingerprintDevice *DeviceHandler::getFingerprintDevices() {
  return fingerprintDevices;
}

FingerprintDevice *DeviceHandler::getCurrentDevice(int *index) {
  if (index != nullptr)
    *index = currentDeviceIndex;
  return currentDevice;
}

void DeviceHandler::setDisplayNameMode(display_name_mode mode) {
  displayNameMode = mode;
}

// Moves devices that can identify to "identifierDevices" list and those cannot
// identify to "verifierDevices"
// Sets fingerprintDevices to nullptr
FingerprintDevice *DeviceHandler::getIdentifiers() {
  if (fingerprintDevices == nullptr) {
    syslog(LOG_ERR, "No fingerprint devices found!");
    return nullptr;
  }
  FingerprintDevice *current = nullptr;
  FingerprintDevice *last_i = nullptr;
  FingerprintDevice *last_v = nullptr;
  FingerprintDevice *next = nullptr;
  identifierDevices = nullptr;
  verifierDevices = nullptr;
  for (current = fingerprintDevices; current != nullptr; current = next) {
    next = current->next;
    syslog(LOG_INFO, "Discovered device: %s.",
           current->getDisplayName(DISPLAY_DRIVER_NAME)->data());
    if (!current->canIdentify()) {
      syslog(LOG_INFO, "Device can not identify.");
      if (verifierDevices == nullptr) {
        verifierDevices = current;
      } else {
        last_v->next = current;
      }
      last_v = current;
    } else {
      syslog(LOG_INFO, "Device can identify.");
      if (identifierDevices == nullptr) {
        identifierDevices = current;
      } else {
        last_i->next = current;
      }
      last_i = current;
    }
    current->next = nullptr;
  }
  fingerprintDevices = nullptr;
  return identifierDevices;
}

FingerprintDevice *DeviceHandler::getVerifiers() {
  if (fingerprintDevices ==
      nullptr) { // No devices or "getIdentifiers" was called already
    return verifierDevices;
  }
  getIdentifiers(); // Separate them first
  return verifierDevices;
}

// Public methods
void DeviceHandler::rescan() {
  // Free old device lists
  for (FingerprintDevice *fp = fingerprintDevices; fp != nullptr;) {
    FingerprintDevice *fp_p = fp;
    fp = fp->next;
    delete fp_p;
  }
  fingerprintDevices = nullptr;

  for (FingerprintDevice *fp = identifierDevices; fp != nullptr;) {
    FingerprintDevice *fp_p = fp;
    fp = fp->next;
    delete fp_p;
  }
  identifierDevices = nullptr;

  for (FingerprintDevice *fp = verifierDevices; fp != nullptr;) {
    FingerprintDevice *fp_p = fp;
    fp = fp->next;
    delete fp_p;
  }
  verifierDevices = nullptr;

  for (USBDevice *usb = attachedUSBDevices; usb != nullptr;) {
    USBDevice *usb_p = usb;
    usb = usb->next;
    delete usb_p;
  }
  attachedUSBDevices = nullptr;

  if (findAttachedUSBDevices() > 0) {
    if (discoveredFpDevices != nullptr)
      fp_dscv_devs_free(discoveredFpDevices);

    /* Discover devices handled by proprietary driver libraries */
    // Discover devices handled by "libbsapi" from UPEK
    if (discoveredBsDevices != nullptr)
      (*bsapiFreeFunction)(discoveredBsDevices);

    if (bsapiHandle) {
      if ((*bsapiDiscoverFunction)("usb", &discoveredBsDevices) ==
          ABS_STATUS_OK) {
        if (discoveredBsDevices->NumDevices > 0) {
          for (uint i = 0; i < discoveredBsDevices->NumDevices; i++) {
            addDevice(new UpekDevice(bsapiHandle, &discoveredBsDevices->List[i],
                                     knownUSBDevices));
          }
        } else {
          syslog(LOG_INFO, "No devices found by libbsapi.");
        }
      } else {
        syslog(LOG_ERR, "ABSEnumerateDevices() failed.");
      }
    }

    /* Discover devices handled by other proprietary driver libraries here */

    // Discover "generic" devices handled by libfprint-2
    // This is the fallback for devices not handled by proprietary libraries
    discoveredFpDevices = fp_discover_devs();
    if (discoveredFpDevices != nullptr) {
      for (int i = 0; discoveredFpDevices[i] != nullptr; i++) {
        addDevice(new GenericDevice(discoveredFpDevices[i], knownUSBDevices));
      }
    } else {
      syslog(LOG_ERR, "No devices found by libfprint-2.");
    }
  }
  setCurrentDevice(currentDeviceIndex);
  emit rescanFinished();
}

// Slots
USBDevice *DeviceHandler::findKnownDevice(int vendor, int device) {
  string v = "0000  Unknown vendor";
  string d = "0000  Unknown device";

  USBDevice *usb = new USBDevice(v, d);
  USBDevice *walk = knownUSBDevices;
  usb->vendorID = vendor;
  usb->deviceID = device;

  while (walk != nullptr) {
    if (walk->vendorID == vendor) {
      usb->vendorName = walk->vendorName;
      if (walk->deviceID == device) {
        usb->deviceName = walk->deviceName;
        return usb;
      }
    }
    walk = walk->next;
  }
  return usb;
}

void DeviceHandler::setCurrentDevice(int index) {
  if (index < 0)
    return;
  int i;
  currentDevice = fingerprintDevices;
  for (i = 0; i < index && currentDevice != nullptr; i++)
    currentDevice = currentDevice->next;
  if (currentDevice != nullptr)
    syslog(LOG_DEBUG, "Current device set to %d -- %s.", i,
           currentDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  currentDeviceIndex = i;
}

// Private helpers
void DeviceHandler::addDevice(FingerprintDevice *fpDevice) {
  fpDevice->next = nullptr;
  if (fingerprintDevices == nullptr) {
    fingerprintDevices = fpDevice;
  } else {
    FingerprintDevice *fpDev = fingerprintDevices;
    while (fpDev != nullptr) {
      // Don't add devices found by a driver that were found before by another
      if (fpDev->vendorId == fpDevice->vendorId &&
          fpDev->productId == fpDevice->productId) {
        string driver1 =
            string(fpDev->getDisplayName(DISPLAY_DRIVER_NAME)->data());
        string driver2 =
            string(fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
        if (driver1.compare(driver2) != 0) {
          // This device is handled by another driver; don't add it again
          syslog(LOG_DEBUG, "Device %s is handled by %s already; not added.",
                 fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data(),
                 fpDev->getDisplayName(DISPLAY_DRIVER_NAME)->data());
          delete fpDevice;
          return;
        }
      }
      if (fpDev->next == nullptr) {
        fpDev->next = fpDevice; // Append fpDevice
        break;
      }
      fpDev = fpDev->next;
    }
  }
  syslog(LOG_DEBUG, "Added %s.",
         fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
  emit deviceAdded(*fpDevice->getDisplayName(displayNameMode));
}

int DeviceHandler::findAttachedUSBDevices() {
  libusb_device **devs = nullptr;
  libusb_device *dev;
  struct libusb_context *ctx;
  struct libusb_device_descriptor desc;
  USBDevice *lastDevice = nullptr;

  libusb_init(&ctx);
  libusb_get_device_list(ctx, &devs);
  if (devs == nullptr) {
    syslog(LOG_ERR, "Failed to get USB device list");
    return false;
  }

  for (int i = 0; devs[i] != nullptr; i++) {
    dev = devs[i];
    if (libusb_get_device_descriptor(dev, &desc) < 0) {
      syslog(LOG_ERR, "Failed to get USB device descriptor");
      continue;
    }
    USBDevice *usb = findKnownDevice(desc.idVendor, desc.idProduct);
    string v = string(usb->vendorName);
    string p = string(usb->deviceName);
    syslog(LOG_DEBUG, "Found USB device: %s/%s.", v.data(), p.data());
    if (lastDevice == nullptr) {
      attachedUSBDevices = usb;
    } else {
      lastDevice->next = usb;
    }
    lastDevice = usb;
  }

  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);
  return true;
}

int DeviceHandler::getKnownUSBDevices() {
  string vendor;
  string device;
  USBDevice *lastDevice = nullptr;
  QString endOfDeviceId = END_OF_DEVICE_IDS;

  QFile idFile(":/new/prefix1/res/usb.ids");
  if (!idFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return false;

  QTextStream in(&idFile);
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line.compare(endOfDeviceId) == 0)
      break;
    if (line.length() != 0 &&
        !line.startsWith("#")) {   // Comment lines and empty lines
      if (line.startsWith("\t")) { // Device
        device = (line.toStdString()).substr(1);
        USBDevice *usb = new USBDevice(vendor, device);
        if (lastDevice == nullptr) {
          knownUSBDevices = usb;
        } else {
          lastDevice->next = usb;
        }
        lastDevice = usb;
      } else { // Vendor
        vendor = line.toStdString();
      }
    }
  }
  idFile.close();
  return true;
}

// Terminate all devices
int DeviceHandler::release() {
  if (currentDevice != nullptr) {
    syslog(LOG_DEBUG, "Stopping device.");
    currentDevice->stop();
  }
  // Exit libfprint-2
  syslog(LOG_DEBUG, "Exitting libfprint-2.");
  fp_exit();

  // Exit libbsapi
  if (bsapiHandle) {
    syslog(LOG_DEBUG, "Terminating libbsapi.");
    if ((*bsapiTerminateFunction)() != 0) {
      syslog(LOG_ERR, "Unable to terminate libbsapi.");
      return 0;
    }
  }
  syslog(LOG_INFO, "Devices released.");
  return -1;
}

// Initialize all devices
int DeviceHandler::initialize() {
  // Initialize libfprint-2
  if (fp_init() != 0) {
    string message = "Unable to initialize libfprint-2.";
    syslog(LOG_ERR, "%s", message.data());
    cerr << message.data() << endl;
    return 0;
  }
  syslog(LOG_DEBUG, "Libfprint-2 initialized.");

  // Initialize libbsapi
  if (bsapiHandle) {
    if ((*bsapiInitFunction)() != 0) {
      string message = "Unable to initialize libbsapi.";
      syslog(LOG_ERR, "%s", message.data());
      cerr << message.data() << endl;
      return 0;
    }
    syslog(LOG_DEBUG, "Libbsapi initialized.");
  }
  syslog(LOG_INFO, "Devices initialized.");
  return -1;
}

/* Loaders for proprietary driver libraries */
// Loader for "libbsapi" from UPEK
const char *getUpekLibname() {
  // bsapi v4.0 cannot handle 147e:2020, v4.3 cannot handle 147e:1000
  // We need to load the libbsapi version that can handle the device found here
  libusb_device **devs = nullptr;
  libusb_device *dev;
  struct libusb_context *ctx;
  struct libusb_device_descriptor desc;
  const char *libname = BSAPI_LIBNAME_43; // Defaults to the newer version

  libusb_init(&ctx);
  libusb_get_device_list(ctx, &devs);
  if (devs == nullptr) {
    syslog(LOG_ERR, "Failed to get USB device list");
    return nullptr;
  }

  for (int i = 0; devs[i] != nullptr; i++) {
    dev = devs[i];
    if (libusb_get_device_descriptor(dev, &desc) < 0) {
      syslog(LOG_ERR, "Failed to get USB device descriptor");
      continue;
    }
    if (desc.idVendor == 0x147e)   // UPEK
      if (desc.idProduct < 0x2000) // Old device needs version 4.0
        libname = BSAPI_LIBNAME_40;
  }

  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);
  return libname;
}

void DeviceHandler::upekLoader() {
  char *error;
  const char *libname = getUpekLibname();
  bsapiHandle = dlopen(libname, RTLD_LAZY);
  if (!bsapiHandle) { // In case the user has no libbsapi.so.4.0 installed
    // but has a working libbsapi.so from an older installation left over
    bsapiHandle = dlopen(BSAPI_LIBNAME, RTLD_LAZY);
  }
  if (bsapiHandle) {
    syslog(LOG_INFO, "Proprietary lib \"%s\" loaded.", libname);
    *(void **)(&bsapiInitFunction) = dlsym(bsapiHandle, BSAPI_INIT);
    if ((error = dlerror()) == nullptr) {
      *(void **)(&bsapiTerminateFunction) = dlsym(bsapiHandle, BSAPI_TERMINATE);
      if ((error = dlerror()) == nullptr) {
        *(void **)(&bsapiFreeFunction) = dlsym(bsapiHandle, BSAPI_FREE);
        if ((error = dlerror()) == nullptr) {
          *(void **)(&bsapiDiscoverFunction) =
              dlsym(bsapiHandle, BSAPI_DISCOVER);
          if ((error = dlerror()) == nullptr) {
          } else {
            syslog(LOG_ERR, "Could not find symbol \"%s\" (%s).",
                   BSAPI_DISCOVER, error);
            bsapiHandle = nullptr;
          }
        } else {
          syslog(LOG_ERR, "Could not find symbol \"%s\" (%s).", BSAPI_FREE,
                 error);
          bsapiHandle = nullptr;
        }
      } else {
        syslog(LOG_ERR, "Could not find symbol \"%s\" (%s).", BSAPI_TERMINATE,
               error);
        bsapiHandle = nullptr;
      }
    } else {
      syslog(LOG_ERR, "Could not find symbol \"%s\" (%s).", BSAPI_INIT, error);
      bsapiHandle = nullptr;
    }
  } else {
    syslog(LOG_INFO, "Proprietary lib \"%s\" not found in library path.",
           libname);
  }
}

/* Insert loaders for other proprietary driver libraries here */

#include "moc_DeviceHandler.cpp"
