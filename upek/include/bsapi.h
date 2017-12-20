/**
 * @file bsapi.h
 *
 * BSAPI standard commands
 *
 * Copyright (C) 2007-2012 AuthenTec Inc.
 */

#ifndef bsapi_h
#define bsapi_h

#include "bstypes.h"
#include "bserror.h"

#ifdef __cplusplus
extern "C" {
#endif



/** 
 * @name Application General Functions
 * The Application General Functions allow to initialize the BSAPI library,
 * open and close logical connections to FM and perform other miscellaneous
 * tasks.
 */

/** 
 * Initialize the BSAPI.DLL library. BSAPI.DLL must be initialized before you can 
 * call any other function. It is called typically during application startup.
 * 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSInitialize(
      void
);


/** 
 * Initialize the BSAPI.DLL library. BSAPI.DLL must be initialized before you can 
 * call any other function. It is called typically during application startup.
 * 
 * @param dwFlags On Windows, flags ABS_INIT_FLAG_NT_SERVICE, ABS_INIT_FLAG_FORCE_LOCAL_SENSOR 
 * and ABS_INIT_FLAG_FORCE_REMOTE_SENSOR are supported.
 * On other systems, no flags are currently supported.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSInitializeEx(
    IN ABS_DWORD dwFlags
);


/** 
 * Uninitialize the BSAPI.DLL library. Must not be called while any connections
 * to FM are still open. It is not obligatory to call this function, if the
 * BSAPI.DLL library should be kept initialized until the program exits,
 * but it is recommended practice to do so.
 * 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSTerminate(
      void
);


/** 
 * Open a new session with a FM.
 * 
 * @param pszDsn Zero-terminated ASCII string describing the FM connection
 * parameters.
 * @param phConnection Resulting connection handle. At the end of the
 * connection it should be closed with .
 * @return Status code.
 */
ABS_STATUS BSAPI ABSOpen(
    IN const ABS_CHAR* pszDsn,
    OUT ABS_CONNECTION* phConnection
);


/** 
 * Close a connection previously opened by ABSOpen.
 * 
 * @param hConnection Connection handle of the connection to be closed.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSClose(
    IN ABS_CONNECTION hConnection
);


/** 
 * Enumerate currently connected fingerprint devices.
 * 
 * @param pszEnumDsn Zero terminated ASCII string describing the connection 
 * interface, where the enumeration should be performed.
 * @param ppDeviceList Address of the pointer, which will be set to point 
 * to the list of found devices. The data has to be freed by a call 
 * to ABSFree.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSEnumerateDevices(
    IN const ABS_CHAR* pszEnumDsn,
    OUT ABS_DEVICE_LIST** ppDeviceList
);


/** 
 * Return data describing some property of device associated with the current 
 * open session.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwPropertyId One of ABS_DEVPROP_xxxx constants, specifying what 
 * device property the caller is interested in.
 * @param ppPropertyData Address of a pointer which will be set to point to 
 * a data block. The content of the data depends on dwPropertyId.
 * The data has to be freed by a call to ABSFree.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetDeviceProperty(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwPropertyId,
    OUT ABS_DATA** ppPropertyData
);


/** 
 * Use this function to releasing memory allocated by other BSAPI.DLL functions.
 * 
 * @param Memblock Address of a memory block to be released. It has no effect 
 * if this parameter is set to NULL. 
 */
void BSAPI ABSFree(
    IN void* Memblock
);




/** 
 * @name Biometric Functions
 * We will describe the biometric functions in this chapter.
 */

/** 
 * Scan the live finger, process it into a fingerprint template and return it 
 * to the caller. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param ppEnrolledTemplate Address of the pointer, which will be set to 
 * point to the resulting template (BIR). The template has to be discarded 
 * by a call to ABSFree.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSEnroll(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    OUT ABS_BIR** ppEnrolledTemplate,
    IN ABS_DWORD dwFlags
);


/** 
 * This function captures sample from the FM, processes it into template and 
 * compares it with templates, specified by the pTemplateArray parameter and 
 * finds out the first template which matches the swiped finger. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwTemplateCount Count of templates in the pTemplateArray.
 * @param pTemplateArray Pointer to the array of pointers to templates.
 * @param pResult Pointer to memory location, where result of the comparing 
 * will be stored. The result is index into the pTemplateArray, determining 
 * the matching template, or -1 if no template matches.
 * @param dwFlags Bitmask specifying flags, which modify slightly behavior 
 * of the function.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSVerify(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwTemplateCount,
    IN ABS_BIR** pTemplateArray,
    OUT ABS_LONG* pResult,
    IN ABS_DWORD dwFlags
);


/** 
 * Compares whether two given templates match or not.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pEnrolledTemplate The fiest template to be compared.
 * @param pVerificationTemplate The second template to be compared.
 * @param pResult Output parameter to be set to result of the comparing. Set 
 * to ABS_TRUE if the two BIRs do match and ABS_FALSE if they do not.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSVerifyMatch(
    IN ABS_CONNECTION hConnection,
    IN ABS_BIR* pEnrolledTemplate,
    IN ABS_BIR* pVerificationTemplate,
    OUT ABS_BOOL* pResult,
    IN ABS_DWORD dwFlags
);


/** 
 * This function captures sample for the purpose specified and creates 
 * a new fingerprint template from it.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwPurpose A value indicate a purpose of the biometric data capture. 
 * @param ppCapturedTemplate Pointer which is set to newly allocated template. 
 * Caller is responsible to release the memory with ABSFree. 
 * @param dwFlags Bitmask specifying flags, which modify slightly behavior 
 * of the function.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSCapture(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwPurpose,
    OUT ABS_BIR** ppCapturedTemplate,
    IN ABS_DWORD dwFlags
);


/** 
 * Perform antilatent check.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pReserved Reserved for future use. Set to NULL.
 * @param pboIsLatent Pointer to ABS_BOOL, where the result of the check operation is stored.
 * @param dwFlags Flags ABS_LATENT_OP_CHECK and ABS_LATENT_OP_STORE are supported.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSCheckLatent(
    IN ABS_CONNECTION hConnection,
    IN void* pReserved,
    OUT ABS_BOOL* pboIsLatent,
    IN ABS_DWORD dwFlags
);


/** 
 * Switch FM to navigation mode (a.k.a. biometric mouse).
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSNavigate(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwFlags
);


/** 
 * Detects finger presence or absence on the sensor.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwDetectPurpose Requested type of operation to be performed.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSDetectFinger(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwDetectPurpose,
    IN ABS_DWORD dwFlags
);




/** 
 * @name Image Grabbing Functions
 */

/** 
 * Grabs image sample from the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwPurpose A value indicate a purpose of the biometric data capture. 
 * @param ppImage Functions sets the pointer to newly allocated sample image.
 * @param dwFlags Only flag ABS_FLAG_HIGH_RESOLUTION is supported.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGrab(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwPurpose,
    OUT ABS_IMAGE** ppImage,
    IN ABS_DWORD dwFlags
);


/** 
 * Grabs image sample from the FM. This function is similar to ABSGrab, but 
 * it is more low level. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwProfileSize Determines how many properties are in pProfileData.
 * @param pProfileData Pointer to first member of profile data array.
 * @param ppImage Functions sets the pointer to newly allocated sample image.
 * @param ppSwipeInfo If used (i.e. not set to NULL), an additional 
 * information about the swipe are provided to the caller.
 * @param dwFlags Bitmask specifying flags, which modify slightly behavior 
 * of the function. Only flag ABS_FLAG_STRICT_PROFILE is supported.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSRawGrab(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwProfileSize,
    IN ABS_PROFILE_DATA* pProfileData,
    OUT ABS_IMAGE** ppImage,
    OUT ABS_SWIPE_INFO** ppSwipeInfo,
    IN ABS_DWORD dwFlags
);


/** 
 * Retrieves list of image formats supported by the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pdwCount Count of image formats returned.
 * @param ppImageFormatList Newly allocated array of image format structures is stored into this pointer.
 * Use ABSFree to release the memory.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSListImageFormats(
    IN ABS_CONNECTION hConnection,
    OUT ABS_DWORD* pdwCount,
    OUT ABS_IMAGE_FORMAT** ppImageFormatList,
    IN ABS_DWORD dwFlags
);


/** 
 * Grabs image sample from the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwPurpose A value indicate a purpose of the biometric data capture. 
 * @param pImageFormat Pointer to structure describing desired image format.
 * @param ppImage Functions sets the pointer to newly allocated sample image.
 * @param ppSwipeInfo If used (i.e. not set to NULL), an additional 
 * information about the swipeare provided to the caller.
 * @param pReserved Reserved for future use. Set to NULL.
 * @param dwFlags Reserved for future use. Set to zero.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGrabImage(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwPurpose,
    IN ABS_IMAGE_FORMAT* pImageFormat,
    OUT ABS_IMAGE** ppImage,
    OUT ABS_SWIPE_INFO** ppSwipeInfo,
    IN void* pReserved,
    IN ABS_DWORD dwFlags
);


/** 
 * Grabs image sample from the FM. This function is similar to ABSGrabImage, 
    but it is more low level.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pOperation See description of ABS_OPERATION.
 * @param dwProfileSize Determines how many properties are in pProfileData.
 * @param pProfileData Pointer to first member of profile data array.
 * @param pImageFormat Poitner to structure describing desired image format.
 * @param ppImage Functions sets the pointer to newly allocated sample image.
 * @param ppSwipeInfo If used (i.e. not set to NULL), an additional 
 * information about the swipeare provided to the caller.
 * @param pReserved Reserved for future use. Set to NULL.
 * @param dwFlags Bitmask specifying flags, which modify slightly behavior 
 * of the function. Only flag ABS_FLAG_STRICT_PROFILE is supported.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSRawGrabImage(
    IN ABS_CONNECTION hConnection,
    IN ABS_OPERATION* pOperation,
    IN ABS_DWORD dwProfileSize,
    IN ABS_PROFILE_DATA* pProfileData,
    IN ABS_IMAGE_FORMAT* pImageFormat,
    OUT ABS_IMAGE** ppImage,
    OUT ABS_SWIPE_INFO** ppSwipeInfo,
    IN void* pReserved,
    IN ABS_DWORD dwFlags
);




/** 
 * @name Miscellaneous Functions
 */

/** 
 * Cancels a running interactive operation. Function of the canceled 
 * operation returns ABS_STATUS_CANCELED. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwOperationID ID of the operation to be canceled, or zero to 
 * cancel the currently processed operation in the current thread.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSCancelOperation(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwOperationID
);


/** 
 * Stores arbitrary data on the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pAppData The data to be stored on the device. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSetAppData(
    IN ABS_CONNECTION hConnection,
    IN ABS_DATA* pAppData
);


/** 
 * Retrieves the data stored on the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param ppAppData Output parameter, to be set to the newly allocated 
 * structure ABS_DATA.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetAppData(
    IN ABS_CONNECTION hConnection,
    OUT ABS_DATA** ppAppData
);


/** 
 * Sets value of session-wide parameter. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwParamID ID of the parameter to set. 
 * @param pParamValue Parameter value. Format and meaning of the data is 
 * parameter dependent. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSetSessionParameter(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwParamID,
    IN ABS_DATA* pParamValue
);


/** 
 * Retrieves value of session-wide parameter.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwParamID ID of the parameter to retrieve. 
 * @param ppParamValue Output parameter for the retrieved value. The function 
 * sets it to point to newly allocated ABS_DATA. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetSessionParameter(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwParamID,
    OUT ABS_DATA** ppParamValue
);


/** 
 * Sets value of global-wide parameter.
 * 
 * @param dwParamID ID of the parameter to set. 
 * @param pParamValue Parameter value. Format and meaning of the data is 
 * parameter dependent. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSetGlobalParameter(
    IN ABS_DWORD dwParamID,
    IN ABS_DATA* pParamValue
);


/** 
 * Retrieves value of global-wide parameter.
 * 
 * @param dwParamID ID of the parameter to retrieve. 
 * @param ppParamValue Output parameter for the retrieved value. The function 
 * sets it to point to newly allocated ABS_DATA. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetGlobalParameter(
    IN ABS_DWORD dwParamID,
    OUT ABS_DATA** ppParamValue
);


/** 
 * This function allows the application to control the state and behavior 
 * of two user interface LEDs, which can be optionally connected to the FM.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwMode Mode of the LEDs. Different modes define different behavior 
 * of the LEDs during specific operations, especially the biometrics. 
 * @param dwLED1 Parameter defining the detailed behavior of the 1st LED.
 * @param dwLED2 Parameter defining the detailed behavior of the 2nd LED.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSetLED(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwMode,
    IN ABS_DWORD dwLED1,
    IN ABS_DWORD dwLED2
);


/** 
 * This function allows the application to query the state and behavior 
 * of the two user interface LEDs, which can be optionally connected to 
 * the FM. 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwMode Returns a mode of the LEDs. 
 * @param pdwLED1 Returns a value defining the detailed behavior of the 1st LED. 
 * @param pdwLED2 Returns a value defining the detailed behavior of the 2nd LED. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetLED(
    IN ABS_CONNECTION hConnection,
    OUT ABS_DWORD* dwMode,
    OUT ABS_DWORD* pdwLED1,
    OUT ABS_DWORD* pdwLED2
);


/** 
 * 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwMode Mode of the LEDs. Different modes define different behavior 
 * of the LEDs during specific operations, especially the biometrics. 
 * @param pLedParams Data defining the detailed behavior of the LEDs, depending on the mode.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSetLedEx(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwMode,
    IN ABS_DATA* pLedParams
);


/** 
 * 
 * 
 * @param hConnection Handle to the connection to FM.
 * @param pdwMode Returns a mode of the LEDs. 
 * @param ppLedParams Output parameter, to be set to the newly allocated 
 * structure of ABS_DATA.
 * @return Status code.
 */
ABS_STATUS BSAPI ABSGetLedEx(
    IN ABS_CONNECTION hConnection,
    OUT ABS_DWORD* pdwMode,
    OUT ABS_DATA** ppLedParams
);


/** 
 * The function converts gray-scale image (as obtain from callback, ABSGrab 
 * or ABSRawGrab) to binarized form, with only two colors. 
 * 
 * @param pGrayScaleImage Pointer to the input, gray-scale image structure.
 * @param ppBinarizedImage Optional output parameter for retrieving the new, 
 * binarized sample image. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSBinarizeSampleImage(
    INOUT ABS_IMAGE* pGrayScaleImage,
    OUT ABS_IMAGE** ppBinarizedImage
);


/** 
 * Retrieves additional information about last BSAPI error, which occurred 
 * in the current thread.
 * 
 * @param pErrorCode Output parameter set to additional system dependent 
 * error code.
 * @param ppErrorMessage On output this is set to point to a buffer containing 
 * zero-terminated string with textual message.
 */
void BSAPI ABSGetLastErrorInfo(
    OUT ABS_DWORD* pErrorCode,
    OUT const ABS_CHAR** ppErrorMessage
);


/** 
 * Requests special function to be processed.
 * 
 * @param dwOpcode Code of operation to perform.
 * @param pInData Input data, passed to the function requested by dwOpcode. 
 * @param ppOutData Data passed back to the caller, as a result of the 
 * operation. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSEscape(
    IN ABS_DWORD dwOpcode,
    IN ABS_DATA* pInData,
    OUT ABS_DATA** ppOutData
);


/** 
 * Requests special function to be processed.
 * 
 * @param hConnection Handle to the connection to FM.
 * @param dwOpcode Code of operation to perform.
 * @param pInData Input data, passed to the function requested by dwOpcode. 
 * @param ppOutData Data passed back to the caller, as a result of the 
 * operation. 
 * @return Status code.
 */
ABS_STATUS BSAPI ABSSessionEscape(
    IN ABS_CONNECTION hConnection,
    IN ABS_DWORD dwOpcode,
    IN ABS_DATA* pInData,
    OUT ABS_DATA** ppOutData
);





#ifdef __cplusplus
}       /* extern "C" */
#endif

#endif  /* bsapi_h */

