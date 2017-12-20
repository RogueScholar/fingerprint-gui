/**
 * @file bserror.h
 *
 * BSAPI error codes
 *
 * Copyright (C) 2007-2012 AuthenTec Inc.
 */
 
#ifndef bserror_h
#define bserror_h

#ifdef __cplusplus
extern "C" {
#endif



/** 
 * Success return status.
 */
#define ABS_STATUS_OK      (0)



/** 
 * General, unknown, or unspecified error.
 */
#define ABS_STATUS_GENERAL_ERROR      (-5001)



/** 
 * Internal error.
 */
#define ABS_STATUS_INTERNAL_ERROR      (-5002)



/** 
 * BSAPI has been already initialized.
 */
#define ABS_STATUS_ALREADY_INITIALIZED      (-5003)



/** 
 * BSAPI is not initialized.
 */
#define ABS_STATUS_NOT_INITIALIZED      (-5004)



/** 
 *  Connection is already opened.
 */
#define ABS_STATUS_ALREADY_OPENED      (-5005)



/** 
 * Invalid parameter.
 */
#define ABS_STATUS_INVALID_PARAMETER      (-5006)



/** 
 * Invalid (connection) handle.
 */
#define ABS_STATUS_INVALID_HANDLE      (-5007)



/** 
 * No such device found.
 */
#define ABS_STATUS_NO_SUCH_DEVICE      (-5008)



/** 
 * Operation has been interrupted due timeout.
 */
#define ABS_STATUS_TIMEOUT      (-5009)



/** 
 * Requested feature/function not implemented.
 */
#define ABS_STATUS_NOT_IMPLEMENTED      (-5010)



/** 
 * Requested feature/function not supported.
 */
#define ABS_STATUS_NOT_SUPPORTED      (-5011)



/** 
 * The operation has been canceled.
 */
#define ABS_STATUS_CANCELED      (-5012)



/** 
 * The operation has not been found (invalid operation ID or the operation 
 * already finished).
 */
#define ABS_STATUS_NO_SUCH_OPERATION      (-5013)



/** 
 * Communication error related to remote session (Terminal Services or Citrix)
 * has occured.
 */
#define ABS_STATUS_REMOTE_COMM_ERROR      (-5014)



/** 
 * The operation is not permitted. It might be a matter insufficient rights of the current user.
 */
#define ABS_STATUS_ACCESS_DENIED      (-5015)



/** 
 * There is not enough permanent memory to store the data.
 */
#define ABS_STATUS_NOT_ENOUGH_PERMANENT_MEMORY      (-5016)




#ifdef __cplusplus
} 		/* extern "C" */
#endif

#endif	/* bserror_h */


