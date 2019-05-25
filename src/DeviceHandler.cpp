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

/* 
 * DeviceHandler maintains a list of all available USB devies and a list of all
 * attached and supported fingerprint reader devices.
 *
 * In the first step a list of all known vendor-id and device-id is derived from
 * the file usb.ids, that is located in the programm ressources and was found
 * on http://www.linux-usb.org/usb.ids. This is only to be able to show a list of 
 * all attached usb devices at GUI startup/rescan.
 *
 * In the second step the list of attached usb devices is created and can be 
 * obtained by getAttachedUsbDevices().
 *
 * In the third step a list of attached and supported fingerprint readers is 
 * created. On adding a device the signal "deviceAdded" is emitted.
 *
 * Calling getIdentifiers returns a list of fingerprint devices that can identify.
 * Calling getVerifiers returns a list of fingerprint devices that can verify only.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <qstring.h>
#include <qcombobox.h>
#include "../include/UsbDevice.h"
#include "../include/FingerprintDevice.h"
#include "drivers/GenericDevice.h"
#include "drivers/UpekDevice.h"
#include "../include/DeviceHandler.h"

using namespace std;

DeviceHandler::DeviceHandler(display_name_mode mode){
    knownUSBDevices=NULL;
    attachedUSBDevices=NULL;
    discoveredFpDevices=NULL;
    discoveredBsDevices=NULL;
    fingerprintDevices=NULL;
    currentDevice=NULL;
    currentDeviceIndex=0;
    identifierDevices=NULL;
    verifierDevices=NULL;
    displayNameMode=mode;

// trying to load libbsapi from UPEK
    upekLoader();

/* call libloaders for other proprietary driver libraries here */

    initialize();
    if(mode==DISPLAY_VENDOR_NAME)   //used for GUI
        getKnownUSBDevices();
}

DeviceHandler::~DeviceHandler(){
//    release();
}

// public getters and setters --------------------------------------------------
USBDevice* DeviceHandler::getAttachedUsbDevices(){
    return attachedUSBDevices;
}

FingerprintDevice* DeviceHandler::getFingerprintDevices(){
    return fingerprintDevices;
}

FingerprintDevice* DeviceHandler::getCurrentDevice(int *index){
    if(index!=NULL)*index=currentDeviceIndex;
    return currentDevice;
}

void DeviceHandler::setDisplayNameMode(display_name_mode mode){
    displayNameMode=mode;
}

// moves devices that can identify to "identifierDevices" list and
// those can not identify to "verifierDevices"
// Sets fingerprintDevices to NULL
FingerprintDevice* DeviceHandler::getIdentifiers(){
    if(fingerprintDevices==NULL){
        syslog(LOG_ERR,"No fingerprint devices found!");
        return NULL;
    }
    FingerprintDevice *current=NULL;
    FingerprintDevice *last_i=NULL;
    FingerprintDevice *last_v=NULL;
    FingerprintDevice *next=NULL;
    identifierDevices=NULL;
    verifierDevices=NULL;
    for(current=fingerprintDevices;current!=NULL;current=next){
        next=current->next;
        syslog(LOG_INFO,"Discovered device: %s.",current->getDisplayName(DISPLAY_DRIVER_NAME)->data());
        if(!current->canIdentify()){
            syslog(LOG_INFO,"Device can not identify.");
            if(verifierDevices==NULL){
                verifierDevices=current;
            }
            else{
                last_v->next=current;
            }
            last_v=current;
        }
        else{
            syslog(LOG_INFO,"Device can identify.");
            if(identifierDevices==NULL){
                identifierDevices=current;
            }
            else{
                last_i->next=current;
            }
            last_i=current;
        }
        current->next=NULL;
    }
    fingerprintDevices=NULL;
    return identifierDevices;
}

FingerprintDevice* DeviceHandler::getVerifiers(){
    if(fingerprintDevices==NULL){   //No devices or "getIdentifiers" was called already
        return verifierDevices;
    }
    getIdentifiers();   //Separate them first
    return verifierDevices;
}

// public methods --------------------------------------------------------------
void DeviceHandler::rescan(){
    //free old device lists
    for(FingerprintDevice* fp=fingerprintDevices;fp!=NULL;){
        FingerprintDevice* fp_p=fp;
        fp=fp->next;
        delete fp_p;
    }
    fingerprintDevices=NULL;

    for(FingerprintDevice* fp=identifierDevices;fp!=NULL;){
        FingerprintDevice* fp_p=fp;
        fp=fp->next;
        delete fp_p;
    }
    identifierDevices=NULL;

    for(FingerprintDevice* fp=verifierDevices;fp!=NULL;){
        FingerprintDevice* fp_p=fp;
        fp=fp->next;
        delete fp_p;
    }
    verifierDevices=NULL;

    for(USBDevice* usb=attachedUSBDevices;usb!=NULL;){
        USBDevice* usb_p=usb;
        usb=usb->next;
        delete usb_p;
    }
    attachedUSBDevices=NULL;
    
    if(findAttachedUSBDevices()>0){
        if(discoveredFpDevices!=NULL)
            fp_dscv_devs_free(discoveredFpDevices);

// discover devices handled by proprietary driver libraries
    // discover devices handled by "libbsapi" from UPEK
        if(discoveredBsDevices!=NULL)
            (*bsapiFreeFunction)(discoveredBsDevices);

        if(bsapiHandle){
            if((*bsapiDiscoverFunction)("usb",&discoveredBsDevices)==ABS_STATUS_OK){
                if(discoveredBsDevices->NumDevices>0){
                    for(uint i=0;i<discoveredBsDevices->NumDevices;i++){
                        addDevice(new UpekDevice(bsapiHandle,&discoveredBsDevices->List[i],knownUSBDevices));
                    }
                }
		else{
	            syslog(LOG_INFO,"No devices found by libbsapi.");
		}
            }
            else{
                syslog(LOG_ERR,"ABSEnumerateDevices() failed.");
            }
        }

/* discover devices handled by other proprietary driver libraries here */

    // discover "generic" devices handled by libfprint
    // this is the fallback for devices not handled by proprietary libraries
        discoveredFpDevices=fp_discover_devs();
        if(discoveredFpDevices!=NULL){
            for(int i=0;discoveredFpDevices[i]!=NULL;i++){
                addDevice(new GenericDevice(discoveredFpDevices[i],knownUSBDevices));
            }
        }
	else{
	    syslog(LOG_ERR,"No devices found by libfprint.");
	}
    }
    setCurrentDevice(currentDeviceIndex);
    emit rescanFinished();
}

// slots -----------------------------------------------------------------------
USBDevice* DeviceHandler::findKnownDevice(int vendor, int device){
    string v="0000  unknown vendor";
    string d="0000  unknown device";

    USBDevice* usb=new USBDevice(v,d);
    USBDevice* walk=knownUSBDevices;
    usb->vendorID=vendor;
    usb->deviceID=device;

    while(walk!=NULL){
        if(walk->vendorID==vendor){
            usb->vendorName=walk->vendorName;
            if(walk->deviceID==device){
                usb->deviceName=walk->deviceName;
                return usb;
            }
        }
        walk=walk->next;
    }
    return usb;
}

void DeviceHandler::setCurrentDevice(int index){
    if(index<0)return;
    int i;
    currentDevice=fingerprintDevices;
    for(i=0;i<index&&currentDevice!=NULL;i++)
        currentDevice=currentDevice->next;
    if(currentDevice!=NULL)
        syslog(LOG_DEBUG,"Current device set to %d -- %s.",i,currentDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
    currentDeviceIndex=i;
}

// private helpers -------------------------------------------------------------
void DeviceHandler::addDevice(FingerprintDevice* fpDevice){
    fpDevice->next=NULL;
    if(fingerprintDevices==NULL){
        fingerprintDevices=fpDevice;
    }
    else{
        FingerprintDevice* fpDev=fingerprintDevices;
        while(fpDev!=NULL){
            // don't add devices found by a driver that were found by another driver before
            if(fpDev->vendorId==fpDevice->vendorId && fpDev->productId==fpDevice->productId){
                string driver1=string(fpDev->getDisplayName(DISPLAY_DRIVER_NAME)->data());
                string driver2=string(fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
                if(driver1.compare(driver2)!=0){
                    // this device is handled by another driver; don't add it again
                    syslog(LOG_DEBUG,"Device %s is handled by %s already; not added.",fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data(),fpDev->getDisplayName(DISPLAY_DRIVER_NAME)->data());
                    delete fpDevice;
                    return;
                }
            }
            if(fpDev->next==NULL){
                fpDev->next=fpDevice;   // append fpDevice
                break;
            }
            fpDev=fpDev->next;
        }
    }
    syslog(LOG_DEBUG,"Added %s.",fpDevice->getDisplayName(DISPLAY_DRIVER_NAME)->data());
    emit deviceAdded(*fpDevice->getDisplayName(displayNameMode));
}

int DeviceHandler::findAttachedUSBDevices(){
    libusb_device **devs=NULL;
    libusb_device *dev;
    struct libusb_context *ctx;
    struct libusb_device_descriptor desc;
    USBDevice* lastDevice=NULL;

    libusb_init(&ctx);
    libusb_get_device_list(ctx,&devs);
    if(devs==NULL){
        syslog(LOG_ERR,"failed to get usb device list");
        return false;
    }

    for(int i=0;devs[i]!=NULL;i++){
        dev=devs[i];
        if(libusb_get_device_descriptor(dev,&desc)<0){
            syslog(LOG_ERR,"failed to get usb device descriptor");
            continue;
        }
        USBDevice* usb=findKnownDevice(desc.idVendor,desc.idProduct);
        string v=string(usb->vendorName);
        string p=string(usb->deviceName);
        syslog(LOG_DEBUG,"Found USB device: %s/%s.",v.data(),p.data());
        if(lastDevice==NULL){
            attachedUSBDevices=usb;
        }
        else{
            lastDevice->next=usb;
        }
        lastDevice=usb;
    }

    libusb_free_device_list(devs,1);
    libusb_exit(ctx);
    return true;
}

int DeviceHandler::getKnownUSBDevices(){
    string vendor;
    string device;
    USBDevice* lastDevice=NULL;
    QString endOfDeviceId=END_OF_DEVICE_IDS;

    QFile idFile(":/new/prefix1/res/usb.ids");
    if (!idFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    
    QTextStream in(&idFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.compare(endOfDeviceId)==0)
            break;
        if(line.length()!=0&&!line.startsWith("#")){  //comment lines and empty lines
            if(line.startsWith("\t")){  //device
                device=(line.toStdString()).substr(1);
                USBDevice* usb=new USBDevice(vendor,device);
                if(lastDevice==NULL){
                    knownUSBDevices=usb;
                }
                else{
                    lastDevice->next=usb;
                }
                lastDevice=usb;
            }
            else{               //vendor
                vendor=line.toStdString();
            }
        }
    }
    idFile.close();
    return true;
}

// terminate all devices
int DeviceHandler::release(){
    if(currentDevice!=NULL){
        syslog(LOG_DEBUG,"stopping device.");
        currentDevice->stop();
    }
    //exit libfprint
    syslog(LOG_DEBUG,"exit libfprint.");
    fp_exit();

    //exit libbsapi
    if(bsapiHandle){
        syslog(LOG_DEBUG,"terminating libbsapi.");
        if((*bsapiTerminateFunction)()!=0){
            syslog(LOG_ERR,"Unable to terminate libbsapi.");
            return 0;
        }
    }
    syslog(LOG_INFO,"Devices released.");
    return -1;
}

// initialize all devices
int DeviceHandler::initialize(){
    //init libfprint
    if(fp_init()!=0){
        string message="Unable to init libfprint.";
        syslog(LOG_ERR,"%s",message.data());
        cerr<<message.data()<<endl;
        return 0;
    }
    syslog(LOG_DEBUG,"Libfprint initialized.");

    //init libbsapi
    if(bsapiHandle){
        if((*bsapiInitFunction)()!=0){
            string message="Unable to init libbsapi.";
            syslog(LOG_ERR,"%s",message.data());
            cerr<<message.data()<<endl;
            return 0;
        }
        syslog(LOG_DEBUG,"Libbsapi initialized.");
    }
    syslog(LOG_INFO,"Devices initialized.");
    return -1;
}

// Libloaders for proprietary driver libraries
    // loader for "libbsapi" from UPEK
const char* getUpekLibname(){
//bsapi version 4.0 cannot handle 147e:2020
//bsapi version 4.3 cannot handle 147e:1000
//we need to load the libbsapi version that can handle the device found here
    libusb_device **devs=NULL;
    libusb_device *dev;
    struct libusb_context *ctx;
    struct libusb_device_descriptor desc;
    const char *libname=BSAPI_LIBNAME_43;	//defaults to the newest version

    libusb_init(&ctx);
    libusb_get_device_list(ctx,&devs);
    if(devs==NULL){
        syslog(LOG_ERR,"failed to get usb device list");
        return NULL;
    }

    for(int i=0;devs[i]!=NULL;i++){
        dev=devs[i];
        if(libusb_get_device_descriptor(dev,&desc)<0){
            syslog(LOG_ERR,"failed to get usb device descriptor");
            continue;
        }
        if(desc.idVendor==0x147e)	//UPEK
    	    if(desc.idProduct<0x2000)	//old device needs version 4.0
    		libname=BSAPI_LIBNAME_40;
    }

    libusb_free_device_list(devs,1);
    libusb_exit(ctx);
    return libname;
}    
    
void DeviceHandler::upekLoader(){
    char *error;
    const char *libname=getUpekLibname();
    bsapiHandle=dlopen(libname,RTLD_LAZY);
    if(!bsapiHandle){	//in case the user has no libbsapi.so.4.0 installed
			//but has a working libbsapi.so from an older installation left over
        bsapiHandle=dlopen(BSAPI_LIBNAME,RTLD_LAZY);
    }
    if(bsapiHandle){
        syslog(LOG_INFO,"Proprietary lib \"%s\" loaded.",libname);
        *(void **)(&bsapiInitFunction)=dlsym(bsapiHandle,BSAPI_INIT);
        if((error=dlerror())==NULL){
            *(void **)(&bsapiTerminateFunction)=dlsym(bsapiHandle,BSAPI_TERMINATE);
            if((error=dlerror())==NULL){
                *(void **)(&bsapiFreeFunction)=dlsym(bsapiHandle,BSAPI_FREE);
                if((error=dlerror())==NULL){
                    *(void **)(&bsapiDiscoverFunction)=dlsym(bsapiHandle,BSAPI_DISCOVER);
                    if((error=dlerror())==NULL){
                    }
                    else{
                        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_DISCOVER,error);
                        bsapiHandle=NULL;
                    }
                }
                else{
                    syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_FREE,error);
                    bsapiHandle=NULL;
                }
            }
            else{
                syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_TERMINATE,error);
                bsapiHandle=NULL;
            }
        }
        else{
            syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_INIT,error);
            bsapiHandle=NULL;
        }
    }
    else{
        syslog(LOG_INFO,"Proprietary lib \"%s\" not found in library path.",libname);
    }
}

/* insert libloaders for other proprietary driver libraries here */
