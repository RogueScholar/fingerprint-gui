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

#include <pthread.h>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include "DeviceHandler.h"
#include "UpekDevice.h"
#include "UsbDevice.h"

using namespace std;

UpekDevice::UpekDevice(void *libHandle,struct abs_device_list_item *bs,USBDevice *knownUSBDevices):FingerprintDevice(){
    char *error;
    bsData=NULL;
    conn=0;
    absFlag=0;
    bsapiHandle=libHandle;

    //load library symbols
    *(void **)(&bsapiOpenFunction)=dlsym(bsapiHandle,BSAPI_OPEN);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_OPEN,error);
    }
    *(void **)(&bsapiCloseFunction)=dlsym(bsapiHandle,BSAPI_CLOSE);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_CLOSE,error);
    }
    *(void **)(&bsapiErrorFunction)=dlsym(bsapiHandle,BSAPI_ERROR);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_ERROR,error);
    }
    *(void **)(&bsapiCancelFunction)=dlsym(bsapiHandle,BSAPI_CANCEL);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_CANCEL,error);
    }
    *(void **)(&bsapiEnrollFunction)=dlsym(bsapiHandle,BSAPI_ENROLL);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_ENROLL,error);
    }
    *(void **)(&bsapiVerifyFunction)=dlsym(bsapiHandle,BSAPI_VERIFY);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_VERIFY,error);
    }
    *(void **)(&bsapiPropertyFunction)=dlsym(bsapiHandle,BSAPI_PROPERTY);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_PROPERTY,error);
    }
    *(void **)(&bsapiSetledFunction)=dlsym(bsapiHandle,BSAPI_SETLED);
    if((error=dlerror())!=NULL){
        syslog(LOG_ERR,"Could not find symbol \"%s\" (%s).",BSAPI_SETLED,error);
    }

    driverName=string("");
    displayName=string("");
    bsDevice=string(strdup(bs->DsnSubString));
    driverName.append("libbsapi");
// We need vendor- and product-id
    string s=string(strdup(bs->DsnSubString));
    // for BSAPI version 3.6
    if(!(s.find("VID_",0)==string::npos || s.find("_PID_",0)==string::npos)){
        vendorId=strtol(s.substr(s.find("VID_",0)+4,4).data(),NULL,16);
        productId=strtol(s.substr(s.find("_PID_",0)+5,4).data(),NULL,16);
        syslog(LOG_INFO,"initializing libbsapi device (vend/prod) 0x%x/0x%x",vendorId,productId);
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
            displayName.append(strdup(bs->DsnSubString));
        }
        return;
    }
    // for BSAPI version 4.0
    if(s.find("device=#",0)!=string::npos){     // Found for 147e:1000 devices
        vendorId=strtol(s.substr(s.find("device=#",0)+10,4).data(),NULL,16);
        productId=strtol(s.substr(s.find("device=#",0)+15,4).data(),NULL,16);
        syslog(LOG_INFO,"initializing libbsapi device (vend/prod) 0x%x/0x%x",vendorId,productId);
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
            displayName.append(strdup(bs->DsnSubString));
        }
        return;
    }
    
    
    if(s.find("device=",0)!=string::npos){     // Found for 147e:2016 devices
        vendorId=strtol(s.substr(s.find("device=",0)+7,4).data(),NULL,16);
        productId=strtol(s.substr(s.find("device=",0)+12,4).data(),NULL,16);
        syslog(LOG_INFO,"initializing libbsapi device (vend/prod) 0x%x/0x%x",vendorId,productId);
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
            displayName.append(strdup(bs->DsnSubString));
        }
        return;
    }
    syslog(LOG_ERR,"FIXME! Couldn't parse vendor/productin line:\"%s\"",s.data());
}

// public getters and setters --------------------------------------------------
string* UpekDevice::getDisplayName(int mode){
    if(mode==DISPLAY_DRIVER_NAME)
        return &driverName;
    return &displayName;
}

void UpekDevice::setMode(int m){
    mode=m;
}

bool UpekDevice::canIdentify(){
    // libbsapi type devices support it always
    return true;
}

void UpekDevice::setIdentifyData(FingerprintData *iData){
    int i;
    FingerprintData *d;
    for(d=iData,numIdentify=0;d!=NULL;numIdentify++){
        d=d->next;
    }
    if(numIdentify==0){
        syslog(LOG_ERR,"FIXME: numPrints=0.");
        return;
    }
    identifyData=new ABS_BIR*[numIdentify+1];
    for(d=iData,i=0;d!=NULL;i++){
        identifyData[i]=(ABS_BIR*)d->getData();
        d=d->next;
    }
    identifyData[numIdentify]=NULL;
}

int UpekDevice::getData(void **d,struct fp_pic_data **pic){
    if ( NULL != pic ) *pic=&fpPic;
    *d=(void*)bsData;
    return bsData->Header.Length;
}

void UpekDevice::setData(void *d,int){
    bsData=(ABS_BIR*)d;
}

// Here we go...
void UpekDevice::run(){
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

void UpekDevice::stop(){
    if(conn==0){
        syslog(LOG_DEBUG,"No device to stop.");
        return;
    }
//syslog(LOG_DEBUG,"Stopping bsapi-device.");
    if(bsapiSetledFunction)(*bsapiSetledFunction)(conn,ABS_LED_MODE_OFF,0,0);	//lED would stay on after cancelling
    if(bsapiCancelFunction)(*bsapiCancelFunction)(conn,mode);
}

// private helpers -------------------------------------------------------------
// These are helpers for the callback
// I need them only because I don't know how to handover a member function of
// UpekDevice as callback to the ABS... functions.
void UpekDevice::emitAcquireResult(int result){
    emit acquireResult(result);
}

void UpekDevice::emitVerifyResult(int result){
    emit verifyResult(result,&fpPic);
}

static UpekDevice *upekDevice;

//opens an ABS... device
bool UpekDevice::bsDevOpen(string bsDevice,ABS_CONNECTION *conn){
    if(bsDevice.length()==0){
        syslog(LOG_ERR,"FIXME: BsDevice string empty.");
        return false;
    }
        
    if(bsapiOpenFunction){
        ABS_STATUS res=(*bsapiOpenFunction)(bsDevice.data(),conn);
        if(res!=ABS_STATUS_OK) {
            const ABS_CHAR *ErrorMessage;
            ABS_DWORD ErrorCode;
            if(bsapiErrorFunction){
                (*bsapiErrorFunction)(&ErrorCode,&ErrorMessage);
                syslog(LOG_ERR,"ABSOpen() failed %d (%s).",(int)ErrorCode,ErrorMessage);
                return false;
            }
            return false;
        }
        // WORKAROUND!!
        // In my opinion there is a bug in libbsapi.so when opening a devie with
        // NVM emulation. It creates a file in /var/upek_data that is owned by this
        // user created with his umask. If another user opens the device, hi has
        // insufficient permissions to acces this file.
        // So each time we open the device, we try to set the permissions to 0666
        // if it has created a NVM file.
        QFile cfg(UPEK_CFG);
        if(cfg.exists()){   // We have a NVM config file in /etc
            if(cfg.open(QIODevice::ReadOnly)){
                QString config(cfg.readAll());
                if(!config.isEmpty()){  // It contains something
                    QString nvmPath(config.section("nvmprefix",1));
                    nvmPath=nvmPath.section("=",1);
                    if(nvmPath.contains('"')){
                        nvmPath=nvmPath.section('"',1,1);
                    }
                    nvmPath=nvmPath.trimmed();
                    if(!nvmPath.isEmpty()){ // We have a NVM path entry
                        QString nvmName(nvmPath.right(nvmPath.length()-nvmPath.lastIndexOf('/')-1));
                        nvmPath=nvmPath.left(nvmPath.lastIndexOf('/'));
                        QDir var(nvmPath);
                        if(var.exists()){   // A directory for NVM data exists
                            QStringList filter;filter << nvmName+"*";
                            var.setNameFilters(filter);
                            foreach(QString entry,var.entryList(QDir::Hidden|QDir::Files)){
                                QFile f(nvmPath+"/"+entry); // This is the NVM file
                                syslog(LOG_DEBUG,"NVM file \"%s\" detected.",f.fileName().toStdString().data());
                                f.setPermissions(QFile::ReadUser|QFile::WriteUser
                                    |QFile::ReadGroup|QFile::WriteGroup
                                    |QFile::ReadOther|QFile::WriteOther
                                );
                                syslog(LOG_DEBUG,"NVM file permissions 0%x.",0xfff&(int)f.permissions());
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

void swipe(const ABS_OPERATION* p_operation){
    switch(p_operation->OperationID){
        case MODE_ACQUIRE:
            upekDevice->emitAcquireResult(RESULT_SWIPE);
            break;
        case MODE_VERIFY:
        case MODE_IDENTIFY:
            upekDevice->emitVerifyResult(RESULT_SWIPE);
    }
}

void retry(const ABS_OPERATION* p_operation){
    switch(p_operation->OperationID){
        case MODE_ACQUIRE:
            upekDevice->emitAcquireResult(RESULT_ENROLL_RETRY);
            break;
        case MODE_VERIFY:
        case MODE_IDENTIFY:
            upekDevice->emitVerifyResult(RESULT_VERIFY_RETRY);
    }
}

void center(const ABS_OPERATION* p_operation){
    switch(p_operation->OperationID){
        case MODE_ACQUIRE:
            upekDevice->emitAcquireResult(RESULT_ENROLL_RETRY_CENTER);
            break;
        case MODE_VERIFY:
        case MODE_IDENTIFY:
            upekDevice->emitVerifyResult(RESULT_VERIFY_RETRY_CENTER);
    }
}

void tooShort(const ABS_OPERATION* p_operation){
    switch(p_operation->OperationID){
        case MODE_ACQUIRE:
            upekDevice->emitAcquireResult(RESULT_ENROLL_RETRY_TOO_SHORT);
            break;
        case MODE_VERIFY:
        case MODE_IDENTIFY:
            upekDevice->emitVerifyResult(RESULT_VERIFY_RETRY_TOO_SHORT);
    }
}

static ABS_DWORD lastMsg=-1;

void BSAPI callback(const ABS_OPERATION* p_operation,ABS_DWORD msg,void* /*data*/){
    switch(msg) {
        case ABS_MSG_PROCESS_SUCCESS:
            syslog(LOG_DEBUG,"ABS_MSG_PROCESS_SUCCESS.");
            break;
        case ABS_MSG_PROCESS_FAILURE:
            syslog(LOG_DEBUG,"ABS_MSG_PROCESS_FAILURE.");
            break;
        /* Prompt messages should inform the user that he should do something. */
        case ABS_MSG_PROMPT_SCAN:
            if(lastMsg==ABS_MSG_PROCESS_SUCCESS&&p_operation->OperationID==MODE_ACQUIRE){
                upekDevice->emitAcquireResult(RESULT_ENROLL_PASS);
            }
            syslog(LOG_DEBUG,"ABS_MSG_PROMPT_SCAN.");
            swipe(p_operation);
            break;
        case ABS_MSG_PROMPT_TOUCH:
            syslog(LOG_DEBUG,"ABS_MSG_PROMPT_TOUCH.");
            break;
        case ABS_MSG_PROMPT_KEEP:
            syslog(LOG_DEBUG,"ABS_MSG_PROMPT_KEEP.");
            break;
        case ABS_MSG_PROMPT_LIFT:
            syslog(LOG_DEBUG,"ABS_MSG_PROMPT_LIFT.");
            break;
        case ABS_MSG_PROMPT_CLEAN:
            syslog(LOG_DEBUG,"ABS_MSG_PROMPT_CLEAN.");
            break;
        
        /* Quality messages come if something went wrong. E.g. the user
         * did not scan his finger in the right way. */
        case ABS_MSG_QUALITY_CENTER_HARDER:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_CENTER_HARDER.");
            center(p_operation);
            break;
        case ABS_MSG_QUALITY_CENTER:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_CENTER.");
            center(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_LEFT:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_LEFT.");
            center(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_RIGHT:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_RIGHT.");
            center(p_operation);
            break;
        case ABS_MSG_QUALITY_HARDER:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_HARDER.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_LIGHT:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_LIGHT.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_DRY:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_DRY.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_SMALL:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_SMALL.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_SHORT:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_SHORT.");
            tooShort(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_HIGH:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_HIGH.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_LOW:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_LOW.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_FAST:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_FAST.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_SKEWED:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_SKEWED.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_TOO_DARK:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_TOO_DARK.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_BACKWARD:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_BACKWARD.");
            retry(p_operation);
            break;
        case ABS_MSG_QUALITY_JOINT:
            syslog(LOG_DEBUG,"ABS_MSG_QUALITY_JOINT.");
            retry(p_operation);
            break;
            
//UNUSED MESSAGES:
//        /* These messages just inform us how the interactive operation
//         * progresses. Typical applications do not need it. */
        case ABS_MSG_PROCESS_BEGIN:
        case ABS_MSG_PROCESS_END:
//        /* On some platforms, the biometric operastion can be suspended
//         * when other process acquires sensor for other operation. */
        case ABS_MSG_PROCESS_SUSPEND:
        case ABS_MSG_PROCESS_RESUME:
//        /* Sometimes some info how the operation progresses is sent. */
        case ABS_MSG_PROCESS_PROGRESS:
//        /* Navigation messages are sent only from ABSNavigate. Its not used
//         * in this sample but we list the messages here for completeness. */
        case ABS_MSG_NAVIGATE_CHANGE:
        case ABS_MSG_NAVIGATE_CLICK:
//        /* Real application would probably use some GUI to provide feedback
//         * for user. On these messages the GUI dialog should be made vsiible
//         * and invisible respectivelly. */
        case ABS_MSG_DLG_SHOW:
        case ABS_MSG_DLG_HIDE:
            return;
        default:    // should not happen
            syslog(LOG_ERR,"ABS_MSG_ ... unknown (0x%x).",msg);
    }
    lastMsg=msg;
}

static ABS_OPERATION operation={ 
    0,          //operation identifier, used for mode (acquire, identify or verify)
    NULL,       //data to call back, not used
    callback,  
    OPERATION_TIMEOUT,      //timeout
    ABS_OPERATION_FLAG_LL_CALLBACK
};

void UpekDevice::setTimeout(bool
    timeout){
    if(timeout){
        operation.Timeout=OPERATION_TIMEOUT;
    }
    else{
        operation.Timeout=0;
    }
}

//run a verification task
bool UpekDevice::verify(){
    ABS_LONG bsResult;
//    ABS_SAMPLE_IMAGE *bsImage;

    if(bsDevice.length()!=0)
        if(!bsDevOpen(bsDevice,&conn))
            conn=0;
    upekDevice=this;
    if(conn==0){
        syslog(LOG_ERR,"No device open."); 
        emit noDeviceOpen();
        return false;
    }
    emit neededStages(1);   //always "1" for verification
    lastMsg=-1;
    operation.OperationID=MODE_VERIFY;
    if(!bsapiVerifyFunction){
        emit verifyResult(RESULT_VERIFY_NO_MATCH,&fpPic);
        return false;
    }
    if((*bsapiVerifyFunction)(conn,&operation,1,&bsData,&bsResult,0)!=ABS_STATUS_OK){
        syslog(LOG_ERR,"ABSVerify() failed.");
        emit verifyResult(RESULT_VERIFY_NO_MATCH,&fpPic);
        return false;
    }
    //maybe we insert "image" stuff here in a later version of libbsapi
//        syslog(LOG_DEBUG,"Verify: grab image start.");
//        if(ABSGrab(conn,&operation,ABS_PURPOSE_VERIFY,&bsImage,0)==ABS_STATUS_OK){
//            syslog(LOG_DEBUG,"Verify: have image.");
//            ABSFree(bsImage);
//        }
//        syslog(LOG_DEBUG,"Verify: grab image end.");

    if(bsapiCloseFunction){
        if((*bsapiCloseFunction)(conn)!=ABS_STATUS_OK) {
            syslog(LOG_ERR,"ABSClose() failed.");
            emit verifyResult(RESULT_VERIFY_NO_MATCH,&fpPic);
            return false;
        }
    }
    if(bsResult==0){
        syslog(LOG_DEBUG,"Verify result RESULT_VERIFY_MATCH");
        emit verifyResult(RESULT_VERIFY_MATCH,&fpPic);
        return true;
    }
    syslog(LOG_DEBUG,"Verify result RESULT_VERIFY_NO_MATCH");
    emit verifyResult(RESULT_VERIFY_NO_MATCH,&fpPic);
    return false;
}

//run an enrollment task
bool UpekDevice::acquire(){
    mode=MODE_ACQUIRE;
    if(bsDevice.length()!=0)
        if(!bsDevOpen(bsDevice,&conn))
            conn=0;
    upekDevice=this;
    if(conn==0){
        syslog(LOG_ERR,"No device open."); 
        emit noDeviceOpen();
        return false;
    }

    emit neededStages(1);       //we use a dynamic number of needed stages
    lastMsg=-1;
    operation.OperationID=mode;
    if(!bsapiEnrollFunction){
        syslog(LOG_ERR,"ABSEnroll() failed.");
        emit acquireResult(RESULT_ENROLL_FAIL);
        return false;
    }
    if((*bsapiEnrollFunction)(conn,&operation,&bsData,0)!=ABS_STATUS_OK){
        syslog(LOG_ERR,"ABSEnroll() failed.");
        emit acquireResult(RESULT_ENROLL_FAIL);
        return false;
    }
    //insert "image" stuff here in later version
    if(bsapiCloseFunction){
        if((*bsapiCloseFunction)(conn)!=ABS_STATUS_OK) {
            syslog(LOG_ERR,"ABSClose() failed.");
            return false;
        }
    }
    syslog(LOG_DEBUG,"Acquire result RESULT_ENROLL_COMPLETE");
    emit acquireResult(RESULT_ENROLL_COMPLETE);
    return true;
}

bool UpekDevice::identify(){
    long match=-1L;

    if(identifyData==NULL||numIdentify==0){
        syslog(LOG_ERR,"No data to identify."); 
        return false;
    }
    lastMsg=-1;
    if(bsDevice.length()!=0)
        if(!bsDevOpen(bsDevice,&conn))
            conn=0;
    if(conn==0){
        syslog(LOG_ERR,"Could not open libbsapi-device.");
        emit noDeviceOpen();
        return false;
    }
    upekDevice=this;
    operation.OperationID=MODE_IDENTIFY;
    if(bsapiVerifyFunction){
        if((*bsapiVerifyFunction)(conn,&operation,numIdentify,identifyData,(ABS_LONG*)&match,absFlag)!=ABS_STATUS_OK){
            const ABS_CHAR *ppErrorMessage;
            ABS_DWORD pErrorCode;
            if(bsapiErrorFunction){
                (*bsapiErrorFunction)(&pErrorCode,&ppErrorMessage);
                syslog(LOG_ERR,"ABSVerify() failed with %s.",ppErrorMessage);
            }
            match=-1L;
        }
    }
    if(bsapiCloseFunction){
        if((*bsapiCloseFunction)(conn)!=ABS_STATUS_OK) {
            syslog(LOG_ERR,"ABSClose() failed.");
            match=-1L;
        }
    }
    syslog(LOG_DEBUG,"Match result %u.",(int)match);
    emit matchResult(match,&fpPic);
    return true;
}
