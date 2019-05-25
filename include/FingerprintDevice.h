/*
 * Project "Fingerprint GUI": Services for fingerprint authentication on Linux
 * Module: FingerprintDevice.h
 * Purpose: Interface class for fingerprint sensors of any type
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

#ifndef _FINGERPRINTDEVICE_H
#define _FINGERPRINTDEVICE_H

#include <string>
#include <QObject>
#include "UsbDevice.h"

#include "Globals.h"
#include "FingerprintData.h"

using namespace std;

//typedef enum {
enum {
    MODE_ACQUIRE=10,
    MODE_VERIFY,
    MODE_IDENTIFY,
};

// Result codes for enroll, identify and verify
#define RESULT_VERIFY_MATCH             0x10000000  // match
#define RESULT_VERIFY_NO_MATCH          0x10000001  // no match
#define RESULT_VERIFY_RETRY_TOO_SHORT   0x10000002  // swipe too short
#define RESULT_VERIFY_RETRY_CENTER      0x10000003  // center and retry
#define RESULT_VERIFY_RETRY_REMOVE      0x10000004  // remove and retry
#define RESULT_VERIFY_RETRY             0x10000005  // retry
#define RESULT_ENROLL_COMPLETE          0x20000000  // enroll complete
#define RESULT_ENROLL_FAIL              0x20000001  // fail
#define RESULT_ENROLL_RETRY_TOO_SHORT   0x20000002  // swipe too short
#define RESULT_ENROLL_RETRY_CENTER      0x20000003  // center and retry
#define RESULT_ENROLL_RETRY_REMOVE      0x20000004  // remove and retry
#define RESULT_ENROLL_RETRY             0x20000005  // retry
#define RESULT_ENROLL_PASS              0x20000006  // pass
#define RESULT_SWIPE                    0x30000000  // request a finger swipe

//FingerprintDevice
class FingerprintDevice : public QThread
 {
    Q_OBJECT

public:
    int vendorId;
    int productId;
    struct fp_pic_data fpPic;

public:
    FingerprintDevice* next;

public:
    FingerprintDevice(){fpPic.data=NULL;}
    ~FingerprintDevice(){if(NULL!=fpPic.data){free(fpPic.data);}}
    virtual string* getDisplayName(int)=0;            //returns a display name for this device
    virtual bool canIdentify()=0;
    virtual void setData(void *data,int size)=0;      //loads data into driver
    virtual int getData(void **d,struct fp_pic_data **pic)=0;                  //gets data, return datasize
    virtual void setMode(int mode)=0;
    virtual void setTimeout(bool timeout)=0;          //timeot after OPERATION_TIMEOUT if true
    virtual void setIdentifyData(FingerprintData *identifyData)=0;
    virtual void stop()=0;

protected:
    virtual void run()=0;
    void img_to_pixmap(struct fp_img *img) {
	size_t rgb_offset = 0;
	size_t i;
	size_t size;
	unsigned char *imgdata;
	if ( NULL != fpPic.data ) {
		free ( fpPic.data );
		fpPic.data = NULL;
	}
	if ( NULL != img ) {
		imgdata = fp_img_get_data(img);
		size = ( fpPic.width = fp_img_get_width ( img ) ) * ( fpPic.height = fp_img_get_height ( img ) );
		if ( NULL != ( fpPic.data = (unsigned char *)malloc ( size * 3 ) ) ) {
			for ( i = 0 ; i < size ; i ++ ) {
				unsigned char pixel = imgdata[i];
				fpPic.data[rgb_offset++] = pixel;
				fpPic.data[rgb_offset++] = pixel;
				fpPic.data[rgb_offset++] = pixel;
			}
		}
	}
	if ( NULL == fpPic.data ) {
		fpPic.width = 0;
		fpPic.height = 0;
	}
/*
	if ( fpPic ) {
		free ( fpPic->data );
		free ( fpPic );
		fpPic = NULL;
	}
	if ( NULL != img && NULL != ( fpPic = (struct fp_pic_data *)malloc ( sizeof ( struct fp_pic_data ) ) ) ) {
		imgdata = fp_img_get_data(img);
		size = ( fpPic->width = fp_img_get_width ( img ) ) * ( fpPic->height = fp_img_get_height ( img ) );
		if ( NULL != ( fpPic->data = (unsigned char *)malloc ( size * 3 ) ) ) {
			for ( i = 0 ; i < size ; i ++ ) {
				unsigned char pixel = imgdata[i];
				fpPic->data[rgb_offset++] = pixel;
				fpPic->data[rgb_offset++] = pixel;
				fpPic->data[rgb_offset++] = pixel;
			}
		}
		else {
			free ( fpPic );
			fpPic = NULL;
		}
	}
*/
    }

public slots:
signals:
    void neededStages(int stages);
    void acquireResult(int result);
    void verifyResult(int result,struct fp_pic_data *pic);
    void matchResult(int match,struct fp_pic_data *pic);
    void noDeviceOpen();
};

#endif /* _FINGERPRINTDEVICE_H */
