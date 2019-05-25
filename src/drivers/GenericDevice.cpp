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

#include <pthread.h>
#include <string>
#include <libusb-1.0/libusb.h>
#include <iostream>
#include "DeviceHandler.h"
#include "GenericDevice.h"
#include "UsbDevice.h"
#include "FingerprintData.h"

using namespace std;

GenericDevice::GenericDevice(struct fp_dscv_dev *fp,USBDevice *knownUSBDevices):FingerprintDevice(){
    fpDevice=fp;
    fpData=NULL;
    identifyData=NULL;
    dev=NULL;
    struct libusb_device_descriptor desc;

    if(libusb_get_device_descriptor(fp->udev,&desc)<0){
        syslog(LOG_ERR,"failed to get usb device descriptor");
        vendorId=0;
        productId=0;
    }
    else{
        vendorId=desc.idVendor;
        productId=desc.idProduct;
    }

    driverName=string("");
    displayName=string("");
    driverName.append(fp_driver_get_name(fp_dscv_dev_get_driver(fpDevice)));
    syslog(LOG_INFO,"initializing libfprint device (vend/prod) 0x%x/0x%x, driver: %s",vendorId,productId,driverName.data());
    if(knownUSBDevices!=NULL){
        for(USBDevice *u=knownUSBDevices;u!=NULL;u=u->next){
            if(u->vendorID==vendorId&&u->deviceID==productId){
                displayName.append(string(u->vendorName));
                displayName.append(" ");
                displayName.append(string(u->deviceName));
                break;
            }
        }
    }
    else{
        displayName.append(fp_driver_get_full_name(fp_dscv_dev_get_driver(fpDevice)));
    }
}

// public getters and setters --------------------------------------------------
string* GenericDevice::getDisplayName(int mode){
    if(mode==DISPLAY_DRIVER_NAME)
        return &driverName;
    return &displayName;
}

void GenericDevice::setMode(int m){
    mode=m;
}

void GenericDevice::setIdentifyData(FingerprintData *iData){
    int i,numPrints;
    FingerprintData *d;
    for(d=iData,numPrints=0;d!=NULL;numPrints++){
        d=d->next;
    }
    if(numPrints==0){
        syslog(LOG_ERR,"FIXME: numPrints=0.");
        return;
    }
    identifyData=new fp_print_data*[numPrints+1];
    for(d=iData,i=0;d!=NULL;i++){
        identifyData[i]=fp_print_data_from_data((unsigned char*)d->getData(),d->getSize());
        d=d->next;
    }
    identifyData[numPrints]=NULL;
}

bool GenericDevice::canIdentify(){
    bool rc=false;
    if(fpDevice==NULL){  //Uups!
        syslog(LOG_ERR,"FIXME: fpDevice NULL.");
        return rc;
    }
    dev=fp_dev_open(fpDevice);
    if(!dev){
        syslog(LOG_ERR,"Could not open fpDevice.");
        return rc;
    }
    else{
        if(fp_dev_supports_identification (dev)!=0){
            rc=true;
        }
        fp_dev_close(dev);
        dev=NULL;
    }
    return rc;
}

int GenericDevice::getData(void **d,struct fp_pic_data **pic){
    int size=0;
    if ( NULL != pic ) *pic = &fpPic;
    if((size=fp_print_data_get_data(fpData,(unsigned char**)d))==0){
        syslog(LOG_ERR,"Could not convert fpData!");
    }
    fp_print_data_free(fpData);
    fpData=NULL;
    return size;
}

void GenericDevice::setData(void *d,int size){
    if(fpData!=NULL){
        fp_print_data_free(fpData);
        fpData=NULL;
    }
    fpData=fp_print_data_from_data((unsigned char*)d,size);
}

// Here we go...
void GenericDevice::run(){
    syslog(LOG_DEBUG,"Starting %s.",(mode==MODE_VERIFY?"verify":mode==MODE_ACQUIRE?"acquire":"identify"));
    switch(mode){
        case MODE_VERIFY:
            verify();
            break;
        case MODE_ACQUIRE:
            acquire();
            break;
        case MODE_IDENTIFY:
            identify();
            break;
    }
    syslog(LOG_DEBUG,"Thread ended normally.");
}

static void sync_close_cb(struct fp_dev *dev,void *user_data){
    Q_UNUSED(dev);
    bool *closed=(bool *)user_data;
    *closed=true;
}

void GenericDevice::stop(){
    bool stopped;

    if(dev==NULL)
	return;
	syslog(LOG_DEBUG,"FP_DEV_STOP.");

    wait(1000);
    switch(mode){
        case MODE_VERIFY:
	    syslog(LOG_DEBUG,"FP_ASYNC_VERIFY_STOP.");
	    if(fp_async_verify_stop(dev,sync_close_cb,&stopped)==0){
		while(!stopped)
		    if(fp_handle_events()<0)
			break;
	    }
            break;
        case MODE_ACQUIRE:
	    syslog(LOG_DEBUG,"FP_ASYNC_ENROLL_STOP.");
	    if(fp_async_enroll_stop(dev,sync_close_cb,&stopped)==0){
		while(!stopped)
		    if(fp_handle_events()<0)
			break;
	    }
            break;
        case MODE_IDENTIFY:
	    syslog(LOG_DEBUG,"FP_ASYNC_IDENTIFY_STOP.");
	    if(fp_async_identify_stop(dev,sync_close_cb,&stopped)==0){
		while(!stopped)
		    if(fp_handle_events()<0)
			break;
	    }
            break;
    }

    fpDevClose();
    return;
}

//open fp_dev
bool GenericDevice::fpDevOpen(struct fp_dscv_dev *fpDevice){
    if(fpDevice==NULL){
        syslog(LOG_ERR,"FIXME: fpDevice NULL.");
        return false;
    }
    dev=fp_dev_open(fpDevice);
    if(!dev){
        syslog(LOG_ERR,"Could not open fpDevice.");
        return false;
    }
    return true;
}

bool GenericDevice::fpDevClose(){
    if(!dev){
        syslog(LOG_ERR,"FIXME: dev NULL (fpDevClose).");
        return false;
    }
    syslog(LOG_DEBUG,"FP_DEV_CLOSE.");
    fp_dev_close(dev);
    dev=NULL;
    return true;
}

void GenericDevice::setTimeout(bool){
    //nothing to do here
}

// Translate fp messages into our result codes
int translateVerify(int fp_result){
    int rc=-1;
    switch(fp_result){
        case FP_VERIFY_MATCH:                  
            syslog(LOG_DEBUG,"FP_VERIFY_MATCH.");
            rc=RESULT_VERIFY_MATCH;
            break;
        case FP_VERIFY_NO_MATCH:               
            syslog(LOG_DEBUG,"FP_VERIFY_NO_MATCH.");
            rc=RESULT_VERIFY_NO_MATCH;
            break;
        case FP_VERIFY_RETRY:                  
            syslog(LOG_DEBUG,"FP_VERIFY_RETRY.");
            rc=RESULT_VERIFY_RETRY;
            break;
        case FP_VERIFY_RETRY_CENTER_FINGER:    
            syslog(LOG_DEBUG,"FP_VERIFY_RETRY_CENTER_FINGER.");
            rc=RESULT_VERIFY_RETRY_CENTER;
            break;
        case FP_VERIFY_RETRY_REMOVE_FINGER:    
            syslog(LOG_DEBUG,"FP_VERIFY_RETRY_REMOVE_FINGER.");
            rc=RESULT_VERIFY_RETRY_REMOVE;
            break;
        case FP_VERIFY_RETRY_TOO_SHORT:        
            syslog(LOG_DEBUG,"FP_VERIFY_RETRY_TOO_SHORT.");
            rc=RESULT_VERIFY_RETRY_TOO_SHORT;
            break;
    }
    return rc;
}

// Translate fp messages into our result codes
int translateAcquire(int fp_result){
    int rc=-1;
    switch(fp_result){
        case FP_ENROLL_COMPLETE:               
            syslog(LOG_DEBUG,"FP_ENROLL_COMPLETE.");
            rc=RESULT_ENROLL_COMPLETE;
            break;
        case FP_ENROLL_FAIL:                   
            syslog(LOG_DEBUG,"FP_ENROLL_FAIL.");
            rc=RESULT_ENROLL_FAIL;
            break;
        case FP_ENROLL_PASS:                   
            syslog(LOG_DEBUG,"FP_ENROLL_PASS.");
            rc=RESULT_ENROLL_PASS;
            break;
        case FP_ENROLL_RETRY:                  
            syslog(LOG_DEBUG,"FP_ENROLL_RETRY.");
            rc=RESULT_ENROLL_RETRY;
            break;
        case FP_ENROLL_RETRY_CENTER_FINGER:    
            syslog(LOG_DEBUG,".");
            rc=RESULT_ENROLL_RETRY_CENTER;
            break;
        case FP_ENROLL_RETRY_REMOVE_FINGER:    
            syslog(LOG_DEBUG,"FP_ENROLL_RETRY_REMOVE_FINGER.");
            rc=RESULT_ENROLL_RETRY_REMOVE;
            break;
        case FP_ENROLL_RETRY_TOO_SHORT:        
            syslog(LOG_DEBUG,"FP_ENROLL_RETRY_TOO_SHORT.");
            rc=RESULT_ENROLL_RETRY_TOO_SHORT;
            break;
    }
    return rc;
}

//run a verification task
bool GenericDevice::verify(){
    int result;

    if(fpDevice!=NULL){
        if(!fpDevOpen(fpDevice)){
            syslog(LOG_ERR,"Could not open generic device (verify).");
            emit noDeviceOpen();
            return false;
        }
    }
    emit neededStages(1);   //always "1" for verification
    do{
        emit verifyResult(RESULT_SWIPE,&fpPic);
        sleep(1);   //don't know what this is good for; found it in some sample code of libfprint
//        result=fp_verify_finger(dev,fpData);
        //"img" to be used in later version
        struct fp_img *img=NULL;
        result=fp_verify_finger_img(dev,fpData,&img);
        //"img" to be used in later version
        if(img){
            syslog(LOG_DEBUG,"Verify: have image.");
			img_to_pixmap ( img );
            fp_img_free(img);
        }
        else {
            img_to_pixmap ( NULL );
        }
        if(result<0){
            syslog(LOG_ERR,"Verify failed with error %d.",result);
        }
        emit verifyResult(translateVerify(result),&fpPic);
    }while(result!=FP_VERIFY_NO_MATCH&&result!=FP_VERIFY_MATCH);
    fpDevClose();
    //This is for identifying with "no identifying" devices
    if(result==FP_VERIFY_MATCH){
        syslog(LOG_DEBUG,"Verify result FP_VERIFY_MATCH.");
        emit matchResult(0,&fpPic);
    }
    else{
        syslog(LOG_DEBUG,"Verify result FP_VERIFY_NO_MATCH.");
        emit matchResult(-1,&fpPic);
    }
    return true;
}

//run an enrollment task
bool GenericDevice::acquire(){
    int result;
    mode=MODE_ACQUIRE;
    if(fpDevice!=NULL){
        if(!fpDevOpen(fpDevice)){
            syslog(LOG_ERR,"Could not open generic device (acquire).");
            emit noDeviceOpen();
            return false;
        }
    }

    emit neededStages(1);       //we use a dynamic number of needed stages
    do{
        emit acquireResult(RESULT_SWIPE);
        sleep(1);   //don't know what this is good for; found it in some sample code of libfprint
        //result=fp_enroll_finger(dev,&fpData);
        //"img" to be used in later version
        struct fp_img *img=NULL;
        result=fp_enroll_finger_img(dev,&fpData,&img);
        if(img){
            syslog(LOG_DEBUG,"Acquire: have image.");
            img_to_pixmap ( img );
            fp_img_free(img);
        }
        else {
            img_to_pixmap ( NULL );
        }
        if(result<0){
            syslog(LOG_ERR,"Acquire failed with error %d.",result);
        }
        else{
            syslog(LOG_DEBUG,"Acquire result %d.",result);
        }
        emit acquireResult(translateAcquire(result));
    }while(result!=FP_ENROLL_COMPLETE);
    syslog(LOG_DEBUG,"Acquire result FP_ENROLL_COMPLETE.");
    fpDevClose();
    return true;
}

bool GenericDevice::identify(){
    long match=-1L;

    if(identifyData==NULL){
        syslog(LOG_ERR,"No data to identify."); 
        return false;
    }
    if(fpDevice!=NULL){
        if(!fpDevOpen(fpDevice)){
            syslog(LOG_ERR,"Could not open generic device (identify).");
            if(fpData!=NULL){
                fp_print_data_free(fpData);
                fpData=NULL;
            }
            emit noDeviceOpen();
            return false;
        }
    }

	struct fp_img *img=NULL;
	int result=fp_identify_finger_img(dev,identifyData,(size_t*)&match,&img);
    // result=fp_identify_finger(dev,identifyData,(size_t*)&match);
    if(img){
        syslog(LOG_DEBUG,"Identify: have image.");
		img_to_pixmap ( img );
        fp_img_free(img);
    }
    else {
        img_to_pixmap ( NULL );
    }
    if(result<0){
        syslog(LOG_ERR,"Identify failed with error %d.",result);
        match=-1L;
    }
    fpDevClose();
    if(fpData!=NULL){
        fp_print_data_free(fpData);
        fpData=NULL;
    }
    syslog(LOG_DEBUG,"Match result %u.",(int)match);
    emit matchResult(match,&fpPic);
    return true;
}
