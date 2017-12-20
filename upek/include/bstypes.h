/**
 * @file bstypes.h
 *
 * BSAPI types
 *
 * Copyright (C) 2007-2012 AuthenTec Inc.
 */
 
#ifndef bstypes_h
#define bstypes_h

#ifdef __cplusplus
extern "C" {
#endif

#if defined (_WIN32) ||  defined (_WIN64)
/* On Windows, all BSAPI functions use STDCALL convention */
#define BSAPI   __stdcall
#else
#define BSAPI
#endif

/** 
 * This is a definition which has sole purpose of helping readability.
 * It indicates that formal parameter is an input parameter.
 */
#ifndef IN
#define IN
#endif

/** 
 * This is a definition which has sole purpose of helping readability.
 * It indicates that formal parameter is an output parameter.
 */
#ifndef OUT
#define OUT
#endif

/** 
 * This is a definition which has sole purpose of helping readability.
 * It indicates that formal parameter is both input and output parameter.
 */
#ifndef INOUT
#define INOUT
#endif

/** 
 * This is a definition which has sole purpose of helping readability.
 * It indicates that formal parameter is an optional parameter.  
 */
#ifndef OPTIONAL
#define OPTIONAL
#endif

/** 
 * This is a definition which has sole purpose of helping readability.
 * It indicates that an array has variable length, depending on some
 * other context, usually some other members of en encosing structure.
 */
#ifndef ABS_VARLEN
#define ABS_VARLEN              1
#endif


/** 
 * Signed integer type (1 byte)
 */
typedef char     ABS_CHAR;


/** 
 * Unsigned integer type (1 byte)
 */
typedef unsigned char     ABS_BYTE;


/** 
 * Signed integer type (2 bytes)
 */
typedef short     ABS_SHORT;


/** 
 * Unsigned integer type (2 bytes)
 */
typedef unsigned short     ABS_WORD;


/** 
 * Signed integer type (4 bytes)
 */
typedef int     ABS_LONG;


/** 
 * Unsigned integer type (4 bytes)
 */
typedef unsigned int     ABS_DWORD;


/** 
 * Boolean value (zero, non-zero)
 */
typedef int     ABS_BOOL;

#define ABS_FALSE    (0)
#define ABS_TRUE    (1)


/** 
 * Return status
 */
typedef ABS_LONG     ABS_STATUS;


/** 
 * Connection handle. It represents a session with FM.
 */
typedef ABS_DWORD     ABS_CONNECTION;


/** 
 * The ABS_DATA structure is used to associate any arbitrary long data block 
 * with the length information. 
 */
typedef struct abs_data {
  ABS_DWORD Length; 	///< Length of the Data field in bytes.
  ABS_BYTE Data[ABS_VARLEN]; 	///< The data itself, variable length.
} ABS_DATA;



/** 
 * The header of the BIR. This type is equivalent to BioAPI's structure 
 * BioAPI_BIR_HEADER. 
 */
typedef struct abs_bir_header {
  ABS_DWORD Length; 	///< Length of Header + Opaque Data
  ABS_BYTE HeaderVersion; 	///< HeaderVersion = 1
  ABS_BYTE Type; 	///< Type = 4 (BioAPI_BIR_DATA_TYPE_PROCESSED)
  ABS_WORD FormatOwner; 	///< FormatOwner = 0x12 (STMicroelectronics)
  ABS_WORD FormatID; 	///< FormatID = 0
  ABS_CHAR Quality; 	///< Quality = -2 (BioAPI_QUALITY is not supported)
  ABS_BYTE Purpose; 	///< Purpose (BioAPI_PURPOSE_xxxx, ABS_PURPOSE_xxxx).
  ABS_DWORD FactorsMask; 	///< FactorsMask = 0x08 (BioAPI_FACTOR_FINGERPRINT)
} ABS_BIR_HEADER;



/** 
 * A container for biometric data. 
 */
typedef struct abs_bir {
  ABS_BIR_HEADER Header; 	///< BIR header
  ABS_BYTE Data[ABS_VARLEN]; 	///< The data composing the fingerprint template.
} ABS_BIR;




struct abs_operation;
typedef struct abs_operation ABS_OPERATION;  /* forward declaration */


/** 
 * A type of the callback function that an application can supply to 
 * the BSAPI to enable itself to display GUI state information to user. 
 * 
 * @param pOperation Pointer to ABS_OPERATION structure used when calling the interactive operation.
 * @param dwMsgID ID of message. See description of ABS_MSG_xxxx constants.
 * @param pMsgData Pointer to data with additional information related with 
 * the message. 
 */
typedef void (BSAPI  *ABS_CALLBACK) ( const ABS_OPERATION*, ABS_DWORD, void*);




/** 
 * Holds common data used by all interactive operation functions.
 */
struct abs_operation {
  ABS_DWORD OperationID; 	///< Unique operation ID or zero.
  void* Context; 	///< User defined pointer, passed into the operation callback.
  ABS_CALLBACK Callback; 	///< Pointer to application-defined function, implementing operation callback.
  ABS_LONG Timeout; 	///< Timeout of user's inactivity in milliseconds
  ABS_DWORD Flags; 	///< Bitmask of flags, tuning the operation process.
} ;




#if defined (_WIN32) ||  defined (_WIN64)


/** 
 * The following flags can be used in function ABSInitializeEx.
 */
#define ABS_INIT_FLAG_NT_SERVICE    0x1    ///< Initializes the library in a mode compatible with Windows NT service.
#define ABS_INIT_FLAG_FORCE_LOCAL_SENSOR    0x2    ///< Forces BSAPI to ignore remote sessions and always open sensors locally.
#define ABS_INIT_FLAG_FORCE_REMOTE_SENSOR    0x4    ///< Forces BSAPI to open sensors in a remote session.



#endif  /*#if defined (_WIN32) ||  defined (_WIN64)*/



/** 
 * The following flags can be used in structure ABS_OPERATION.
 */
#define ABS_OPERATION_FLAG_LL_CALLBACK    0x1    ///< Enables low level callback mode.
#define ABS_OPERATION_FLAG_USE_IDLE    0x2    ///< Enables sending of messages ABS_MSG_IDLE to operation callback.



/** 
 * The following flags can be used for biometric functions.
 */
#define ABS_FLAG_NOTIFICATION    0x1    ///< Enables notification mode of the biometric operation.
#define ABS_FLAG_AUTOREPEAT    0x2    ///< Enables auto-repeat mode of the biometric operation.
#define ABS_FLAG_STRICT_PROFILE    0x4    ///< Requires strict interpretation of raw grab profile.
#define ABS_FLAG_HIGH_RESOLUTION    0x8    ///< Requires to use high sample image resolution.



/** 
 * Possible values used where purpose of fingerprint template (BIR) 
 * is specified. 
 */
#define ABS_PURPOSE_UNDEFINED    0    ///< The purpose is not specified.
#define ABS_PURPOSE_VERIFY    1    ///< BIR is intended to be used for verification.
#define ABS_PURPOSE_ENROLL    3    ///< BIR is intended to be used for enrollment.



/** 
 * Profile data for tuning raw grab operation (ABSRawGrab).
 */
typedef struct abs_profile_data {
  ABS_DWORD Key; 	///< Profile key.
  ABS_DWORD Value; 	///< Value, key dependent.
} ABS_PROFILE_DATA;



/** 
 * This structure provides various informations about the swipe, from 
 * ABSRawGrab, ABSGrabImage or ABSRawGrabImage functions.
 */
typedef struct abs_swipe_info {
  ABS_DWORD Version; 	///< Version of the structure. Current version is 1.
  ABS_WORD Height; 	///< Height of the fingerprint image in pixels.
  ABS_BYTE ReconstructionScore; 	///< Reconstruction quality score, in range 0 - 100.
  ABS_BYTE ImageScore; 	///< Image quality score, in range 0 - 100.
  ABS_DWORD MsgID; 	///< Quality feedback message ID.
  ABS_DWORD Flags; 	///< Bitmask indicating various aspects of the swipe.
  ABS_DWORD BackgroundColor; 	///< Background color in the swiped sample image.
} ABS_SWIPE_INFO;



/** 
 * Constants ABS_PKEY_xxxx are possible values for member Key of 
 * ABS_PROFILE_DATA. Meaning of member Value depends on the key used.
 */
#define ABS_PKEY_WAIT_FOR_ACCEPTABLE    1    ///< Enables or disables waiting for acceptable scan quality.
#define ABS_PKEY_SCAN_QUALITY_QUERY    2    ///< Sets scan quality check mode.
#define ABS_PKEY_IMAGE_QUALITY_QUERY    3    ///< Sets image quality check mode.
#define ABS_PKEY_ALLOW_HW_SLEEP    4    ///< Enables HW sleep mode.
#define ABS_PKEY_IMAGE_FORMAT    5    ///< Specifies desired image format.
#define ABS_PKEY_REC_TERMINATION_POLICY    6    ///< Specifies image reconstruction termination policy.
#define ABS_PKEY_REC_RETUNING    7    ///< Enables automatic sensor retuning.
#define ABS_PKEY_REC_DIGITAL_GAIN    8    ///< This value is used for digital image enhancement.
#define ABS_PKEY_REC_FLAG_DGAIN    9    ///< This value is used for digital image enhancement.
#define ABS_PKEY_REC_FLAG_SRA_DOWN    10    ///< Enables top-down striation removal algorithm.
#define ABS_PKEY_REC_FLAG_SRA_UP    11    ///< Enables bottom-up striation removal algorithm.
#define ABS_PKEY_REC_FLAG_SKEW    12    ///< Enables skew compensation algorithm.
#define ABS_PKEY_REC_FLAG_GRADIENT    13    ///< Enables gradient compensation algorithm.
#define ABS_PKEY_REC_SWIPE_DIRECTION    14    ///< Specifies swipe direction mode.
#define ABS_PKEY_REC_NOISE_ROBUSTNESS    15    ///< Specifies noise robustness mode.
#define ABS_PKEY_REC_NOISE_ROBUSTNESS_TRIGGER    16    ///< Specifies noise robustness trigger.
#define ABS_PKEY_REC_SWIPE_TIMEOUT    17    ///< Timeout for swipe termination in milliseconds.
#define ABS_PKEY_REC_NO_MOVEMENT_TIMEOUT    18    ///< No movement timeout.
#define ABS_PKEY_REC_NO_MOVEMENT_RESET_TIMEOUT    19    ///< No movement reset timeout.
#define ABS_PKEY_SENSOR_SECURITY_MODE    20    ///< Sensor security mode.
#define ABS_PKEY_DETECT_LATENT    21    ///< Anti-latent checking mode.
#define ABS_PKEY_READER_SECURITY_MODE    22    ///< Reader security mode.
#define ABS_PKEY_REC_FLAG_DISABLE_FFE_381    23    ///< Disable Faint Finger Enhancement for 381 DPI operations.
#define ABS_PKEY_REC_FLAG_DISABLE_FFE_508    24    ///< Disable Faint Finger Enhancement for 508 DPI operations.

/** 
 * Possible image formats.
 */
#define ABS_PVAL_IFMT_381_381_8    2
#define ABS_PVAL_IFMT_254_254_8    3
#define ABS_PVAL_IFMT_381_381_8_BINARIZED    4
#define ABS_PVAL_IFMT_508_254_8    5
#define ABS_PVAL_IFMT_508_508_4    6
#define ABS_PVAL_IFMT_381_381_4    7
#define ABS_PVAL_IFMT_508_254_4    8
#define ABS_PVAL_IFMT_254_254_4    9
#define ABS_PVAL_IFMT_508_508_8_WIDTH208    10
#define ABS_PVAL_IFMT_508_508_8_COMPRESS1    11
#define ABS_PVAL_IFMT_508_508_4_SCAN4    12
#define ABS_PVAL_IFMT_381_381_8_FAST    13
#define ABS_PVAL_IFMT_508_254_4_SCAN4    14
#define ABS_PVAL_IFMT_254_254_4_SCAN4    15
#define ABS_PVAL_IFMT_381_381_4_FAST    16
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_FAST    17
#define ABS_PVAL_IFMT_508_508_8_COMPRESS2    18
#define ABS_PVAL_IFMT_381_381_8_SCAN381    19
#define ABS_PVAL_IFMT_381_381_4_SCAN381    20
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_SCAN381    21
#define ABS_PVAL_IFMT_381_381_8_LP    22
#define ABS_PVAL_IFMT_381_381_4_LP    23
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_LP    24
#define ABS_PVAL_IFMT_381_381_8_VLP    25
#define ABS_PVAL_IFMT_381_381_4_VLP    26
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_VLP    27
#define ABS_PVAL_IFMT_381_381_8_SCAN381_381_4    28
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_SCAN381_381_4    30
#define ABS_PVAL_IFMT_381_381_8_SCAN381_254_4    31
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_SCAN381_254_4    33
#define ABS_PVAL_IFMT_508_508_8_SCAN508_508_8    34
#define ABS_PVAL_IFMT_508_508_4_SCAN508_508_8    35
#define ABS_PVAL_IFMT_508_508_8_BINARIZED_SCAN508_508_8    36
#define ABS_PVAL_IFMT_508_508_8_COMPRESS3    39
#define ABS_PVAL_IFMT_508_254_8_LP    40
#define ABS_PVAL_IFMT_508_254_4_LP    41
#define ABS_PVAL_IFMT_381_381_8_FAST_LP    42
#define ABS_PVAL_IFMT_381_381_4_FAST_LP    43
#define ABS_PVAL_IFMT_381_381_8_BINARIZED_FAST_LP    44

/** 
 * See description of ABS_PKEY_REC_TERMINATION_POLICY for more information.
 */
#define ABS_PVAL_RTP_BASIC    0    ///< Basic image reconstruction termination policy.
#define ABS_PVAL_RTP_FINGERTIP    1    ///< Fingertip image reconstruction termination policy.
#define ABS_PVAL_RTP_CORE    2    ///< Core image reconstruction termination policy.
#define ABS_PVAL_RTP_CORE_PLUS    3    ///< Enhanced core image reconstruction termination policy.

/** 
 * See description of ABS_PKEY_REC_SWIPE_DIRECTION for more information.
 */
#define ABS_PVAL_SWIPEDIR_STANDARD    0    ///< Standard swipe direction.
#define ABS_PVAL_SWIPEDIR_INVERTED    1    ///< Inverted swipe direction.
#define ABS_PVAL_SWIPEDIR_AUTODETECT    2    ///< Autodetection at the beginning of the swipe.
#define ABS_PVAL_SWIPEDIR_STANDARD_WARN    3    ///< Standard swipe direction with warning.
#define ABS_PVAL_SWIPEDIR_INVERTED_WARN    4    ///< Inverted swipe direction with warning.

/** 
 * See description of ABS_PKEY_REC_NOISE_ROBUSTNESS for more information.
 */
#define ABS_PKEY_NOIR_DISABLED    0    ///< Noise robustness is switched off.
#define ABS_PKEY_NOIR_FORCED    1    ///< Noise robustness is switched on.
#define ABS_PKEY_NOIR_ON_DETECTION    2    ///< Noise robustness is in auto detection mode.

/** 
 * See description of ABS_PKEY_SENSOR_SECURITY_MODE for more information.
 */
#define ABS_PVAL_SSM_DISABLED    0    ///< Sensor security mode is disabled.
#define ABS_PVAL_SSM_ENCRYPT    1    ///< Sensor security is set to 'encryption' mode.
#define ABS_PVAL_SSM_SIGN_ALL    2    ///< Sensor security is set to 'sign all' mode.
#define ABS_PVAL_SSM_SIGN_PARTIAL_V1    3    ///< Sensor security is set to 'sign partial ver. 1'.
#define ABS_PVAL_SSM_SIGN_PARTIAL_V2    4    ///< Sensor security is set to 'sign partial ver. 2'.

/** 
 * See description of ABS_PKEY_SENSOR_SECURITY_MODE for more information.
 */
#define ABS_PVAL_RSM_DISABLED    0    ///< Reader security mode is disabled.
#define ABS_PVAL_RSM_ENCRYPT    1    ///< Reader security is set to 'encryption' mode.



/** 
 * Member Flags of structure ABS_SWIPE_INFO is a bitmask describing 
 * various attributes of user's swipe in ABSRawGrab.
 */
#define ABS_SWIPE_FLAG_TOO_FAST    0x01    ///< The swipe was too fast.
#define ABS_SWIPE_FLAG_TOO_SKEWED    0x02    ///< The swipe was too skewed.
#define ABS_SWIPE_FLAG_BACKWARDS_MOVEMENT    0x04    ///< Swipe was in wrong direction.
#define ABS_SWIPE_FLAG_JOINT_DETECTED    0x08    ///< Finger joint was detected in the swipe.
#define ABS_SWIPE_FLAG_TOO_SHORT    0x10    ///< The swipe was too short.
#define ABS_SWIPE_FLAG_TOO_LIGHT    0x20    ///< The swipe was too light.



/** 
 * Flags usable with functions ABSCheckLatent.
 */
#define ABS_LATENT_OP_CHECK    0x01    ///< Asks function ABSCheckLatent to perform anti-latent check.
#define ABS_LATENT_OP_STORE    0x02    ///< Asks function ABSCheckLatent to store the last scan for any subsequent checks.



/** 
 * Flags of dwDetectPurpose argument of ABSDetectFinger call
 */
#define ABS_DETECT_PURPOSE_TOUCH    0x00    ///< Detection of simple finger touch.
#define ABS_DETECT_PURPOSE_LIFT    0x02    ///< Detection of finger lift.
#define ABS_DETECT_PURPOSE_QUALITY_TOUCH    0x04    ///< Detection of finger touch with acceptable image quality.
#define ABS_DETECT_PURPOSE_LONG_TOUCH    0x06    ///< Detection of long finger touch.



/** 
 * Type ABS_IMAGE_FORMAT desribes desired image format for functions ABSGrabImage 
 * and ABSRawGrabImage.
 */
typedef struct abs_image_format {
  ABS_WORD ScanResolutionH; 	///< Horizontal scan resolution, in dots per inch (DPI).
  ABS_WORD ScanResolutionV; 	///< Vertical scan resolution, in dots per inch (DPI).
  ABS_WORD ImageResolutionH; 	///< Horizonatal resolution of resulted image, in dots per inch (DPI).
  ABS_WORD ImageResolutionV; 	///< Vertical resolution of resulted image, in dots per inch (DPI).
  ABS_BYTE ScanBitsPerPixel; 	///< Scan bits per pixel.
  ABS_BYTE ImageBitsPerPixel; 	///< Bits per pixel of resulted image.
} ABS_IMAGE_FORMAT;



/** 
 * Type ABS_IMAGE holds data representing one sample image of swiped 
 * finger. 
 */
typedef struct abs_image {
  ABS_DWORD Width; 	///< Width of the image in pixels.
  ABS_DWORD Height; 	///< Height of the image in pixels.
  ABS_DWORD ColorCount; 	///< Maximal color count of the image.
  ABS_DWORD HorizontalDPI; 	///< Horizontal resolution of the image (dots per inch).
  ABS_DWORD VerticalDPI; 	///< Vertical resolution of the image (dots per inch).
  ABS_BYTE ImageData[ABS_VARLEN]; 	///< Color values of all pixels.
} ABS_IMAGE;




typedef ABS_IMAGE ABS_SAMPLE_IMAGE;  /* For backward compatibility */



/** 
 * Parameters for LED blinking mode ABS_LED_MODE_MANUAL.
 */
typedef struct abs_led_params_manual {
  ABS_DWORD Version; 	///< Version of this structure. Set to 1.
  ABS_DWORD Led1; 	///< LED1 parameters.
  ABS_DWORD Led2; 	///< LED2 parameters.
  ABS_DWORD Flags; 	///< Reserved, set to zero.
} ABS_LED_PARAMS_MANUAL;




/** 
 * Parameters for LED blinking mode ABS_LED_MODE_MANUAL2.
 */
typedef struct abs_led_params_manual2 {
  ABS_DWORD Version; 	///< Version of this structure (= 1).
  ABS_WORD Drv1_OnPeriod; 	///< Driver 1: Length of "ON" period in 4ms units (range 0-2047).
  ABS_WORD Drv1_OffPeriod; 	///< Driver 1: Length of "OFF" period in 4ms units (range 0-2047).
  ABS_BYTE Drv1_BrCapHi; 	///< Driver 1: Maximum brightness value (range 0-63).
  ABS_BYTE Drv1_BrCapLo; 	///< Driver 1: Minimum brightness value (range 0-63).
  ABS_BYTE Drv1_BrStepX; 	///< Driver 1: Length of brightness change step in 4ms units (range 0-63, +1 added).
  ABS_BYTE Drv1_BrStepY; 	///< Driver 1: Amount levels the LED brightness level will change at each 'BrStepX' (range 0-63).
  ABS_DWORD Drv1_Flags; 	///< Driver 1: Additional flags, see ABS_LEDDRV_FLAG_xxx.
  ABS_WORD Drv2_OnPeriod; 	///< Driver 2: Length of "ON" period in 4ms units (range 0-2047).
  ABS_WORD Drv2_OffPeriod; 	///< Driver 2: Length of "OFF" period in 4ms units (range 0-2047).
  ABS_BYTE Drv2_BrCapHi; 	///< Driver 2: Maximum brightness value (range 0-63).
  ABS_BYTE Drv2_BrCapLo; 	///< Driver 2: Minimum brightness value (range 0-63).
  ABS_BYTE Drv2_BrStepX; 	///< Driver 1: Length of brightness change step in 4ms units (range 0-63, +1 added).
  ABS_BYTE Drv2_BrStepY; 	///< Driver 2: Amount levels the LED brightness level will change at each 'BrStepX' (range 0-63).
  ABS_DWORD Drv2_Flags; 	///< Driver 2: Additional flags, see ABS_LEDDRV_FLAG_xxx.
  ABS_BYTE Drv3_TruthTable; 	///< Definition of the Boolean combination of Driver 1 and Driver 2 that generates Driver 3.
  ABS_BYTE Led1_Mapping; 	///< LED1 mapping - 0=Drv1, 1=Drv3.
  ABS_BYTE Led2_Mapping; 	///< LED2 mapping - 0=Drv2, 1=Drv3.
  ABS_BYTE Led3_Mapping; 	///< LED3 mapping - 0=off, 1=Drv1, 2=Drv2, 3=Drv3.
  ABS_DWORD Flags; 	///< Reserved, set to zero.
} ABS_LED_PARAMS_MANUAL2;




/** 
 * This structure is a container for additional data associated with 
 * ABS_MSG_PROCESS_xxxx messages sent to callback of an interactive 
 * operation. 
 */
typedef struct abs_process_data {
  ABS_DWORD ProcessID; 	///< ID of process stage. See ABS_PROCESS_xxxx constants.
} ABS_PROCESS_DATA;



/** 
 * This structure is a container for additional data associated with 
 * ABS_MSG_PROCESS_BEGIN message sent to callback of an interactive 
 * operation. 
 */
typedef struct abs_process_begin_data {
  ABS_DWORD ProcessID; 	///< ID of process stage. See ABS_PROCESS_xxxx constants.
  ABS_DWORD Step; 	///< Step number.
  ABS_DWORD StepCount; 	///< Count of child steps of this process.
} ABS_PROCESS_BEGIN_DATA;



/** 
 * This structure is a container for additional data associated with 
 * ABS_MSG_PROCESS_PROGRESS message sent to callback of an interactive 
 * operation. 
 */
typedef struct abs_process_progress_data {
  ABS_DWORD ProcessID; 	///< ID of process stage. See ABS_PROCESS_xxxx constants.
  ABS_DWORD Percentage; 	///< Determines percentage of the process completeness. 
} ABS_PROCESS_PROGRESS_DATA;



/** 
 * This structure is a container for additional data associated with 
 * ABS_MSG_PROCESS_SUCCESS message sent to callback of an interactive 
 * operation. 
 */
typedef struct abs_process_success_data {
  ABS_DWORD ProcessID; 	///< ID of process stage. See ABS_PROCESS_xxxx constants.
  ABS_IMAGE* SampleImage; 	///< Pointer to scanned image.
  ABS_BIR* Template; 	///< Pointer to processed template.
} ABS_PROCESS_SUCCESS_DATA;



/** 
 * This structure is a container for additional data associated with 
 * ABS_MSG_NAVIGATE_CHANGE message sent to callback of an interactive 
 * operation. 
 */
typedef struct abs_navigation_data {
  ABS_LONG DeltaX; 	///< Change of the virtual pointer’s coordinates, in the horizontal direction.
  ABS_LONG DeltaY; 	///< Change of the virtual pointer’s coordinates, in the vertical direction.
  ABS_BOOL FingerPresent; 	///< ABS_TRUE if finger is present on the sensor, ABS_FALSE otherwise.
} ABS_NAVIGATION_DATA;



/** 
 * Item of the device info list
 */
typedef struct abs_device_list_item {
  ABS_CHAR DsnSubString[260]; 	///< String usable as part of DSN for ABSOpen to connect to this device.
  ABS_BYTE reserved[256]; 	///< Reserved for future use.
} ABS_DEVICE_LIST_ITEM;



/** 
 * The format of the data returned by ABSEnumerateDevices, it contains 
 * info about all enumerated devices. Please note, that the real output 
 * parameter from ABSEnumerateDevices has variable length – array List[] 
 * has NumDevices items.
 */
typedef struct abs_device_list {
  ABS_DWORD NumDevices; 	///< Number of devices in the list
  ABS_DEVICE_LIST_ITEM List[ABS_VARLEN]; 	///< The list of devices.
} ABS_DEVICE_LIST;



/** 
 * These constants identify interactive operation processes.
 */
#define ABS_PROCESS_NAVIGATE    1    ///< Root process of navigation (ABSNavigate).
#define ABS_PROCESS_ENROLL    2    ///< Root process of enrollment (ABSEnroll).
#define ABS_PROCESS_VERIFY    3    ///< Root process of verification (ABSVerify)
#define ABS_PROCESS_IDENTIFY    4    ///< Root process of identification.
#define ABS_PROCESS_CONSOLIDATED_CAPTURE    5    ///< Process of consolidated template from the scanner.
#define ABS_PROCESS_CONSOLIDATE    6    ///< Process of consolidation.
#define ABS_PROCESS_CAPTURE    7    ///< Process of template capture from scanner.
#define ABS_PROCESS_MATCH    8    ///< Process of matching template against set of templates.
#define ABS_PROCESS_GRAB    9    ///< Process of sample image grab from scanner.
#define ABS_PROCESS_NOTIFY    10    ///< Process of notification.
#define ABS_PROCESS_DETECT_FINGER    11    ///< Process of finger detection.




/** 
 * The following constants are suitable as values for dwPropertyId parameter 
 * of function ABSGetDeviceProperty.
 */
#define ABS_DEVPROP_DEVICE_VERSION    0    ///< Identifies version of the FM device ROM. 
#define ABS_DEVPROP_DEVICE_ID    1    ///< Unique identification of the device if the FM supports it. 
#define ABS_DEVPROP_FIRMWARE_VARIANT    2    ///< Identifies firmware variant. 
#define ABS_DEVPROP_SENSOR_TYPE    4    ///< Identifies sensor type. 
#define ABS_DEVPROP_SYSTEM_ID    6    ///< System identification bits.
#define ABS_DEVPROP_SYSTEM_NAME    7    ///< System identification name.
#define ABS_DEVPROP_FUNCTIONALITY    8    ///< Provides information about FM capabilities.
#define ABS_DEVPROP_DSN_STRING    11    ///< Provides DSN of the device. 
#define ABS_DEVPROP_GUID    12    ///< Gets GUID of the device.
#define ABS_DEVPROP_USAGE    13    ///< Type of the reader in which the FM is used.
#define ABS_DEVPROP_NVM_TYPE    14    ///< Type of NVM (Non-volatile memory) attached to the device.
#define ABS_DEVPROP_SENSOR_VARIANT    15    ///< Sensor variant information.



/** 
 * The following constants are bit flags for ABS_DEVPROP_SENSOR_TYPE value get from 
 * function ABSGetDeviceProperty.
 */
#define ABS_DEVPROP_SENSOR_TYPE_FLAG_STRIP    0x80000000    ///< Identifies the type of sensor. 
#define ABS_DEVPROP_SENSOR_TYPE_FLAG_FIPS201    0x00080000    ///< FIPS-201 certification. 



#define ABS_LED_MODE_MANUAL    0    ///< Manual control of the LEDs.
#define ABS_LED_MODE_AUTO    1    ///< Automatic control of the LEDs.
#define ABS_LED_MODE_MANUAL2    3    ///< Advanced manual control of the LEDs (TCS5D only).
#define ABS_LED_MODE_READER    4    ///< Reader-driven automatic LED control is forced.
#define ABS_LED_MODE_OFF    0xFFFFFFFF    ///< LEDs are turned off.




#define BS_LEDDRV_FLAG_START_ON    0x00000001    ///< If set, state machine will start from the beginning of "ON" period.
#define ABS_LEDDRV_FLAG_STOP_AFTER_OFF    0x00000002    ///< If set, state machine will stop after first "OFF" period finishes.
#define ABS_LEDDRV_FLAG_BR_INVERT    0x00000004    ///< If set, brightness output is inverted.
#define ABS_LEDDRV_FLAG_TABLE_COSEXP    0x00000008    ///< If set, brightness level is defined as CosExp function, otherwise linear function is used.




#define ABS_PARAM_CONSOLIDATION_COUNT    1    ///< Obsolete. Use parameters ABS_PARAM_CONSOLIDATION_COUNT_MIN and ABS_PARAM_CONSOLIDATION_COUNT_MAX instead.
#define ABS_PARAM_CONSOLIDATION_TYPE    2    ///< Determines type of consolidation.
#define ABS_PARAM_MATCH_LEVEL    3    ///< Determines required level of security for comparing two templates with ABSVerifyMatch. 
#define ABS_PARAM_DISABLE_SENSOR_SLEEP    4    ///< Allows to disable sensor sleeping. 
#define ABS_PARAM_DISABLE_SELECTIVE_SUSPEND    5    ///< Allows to disable the selective suspend.
#define ABS_PARAM_POWER_SAVE_MODE    6    ///< Sets default power safe mode, if it is not disabled completely with ABS_PARAM_DISABLE_SENSOR_SLEEP. 
#define ABS_PARAM_POWER_SAVE_TIMEOUT    7    ///< Together with other parameters, it determines how power save works.
#define ABS_PARAM_ANTISPOOFING_POLICY    8    ///< Value is represented as ABS_DATA with 1 byte of length.
#define ABS_PARAM_ANTISPOOFING_LEVEL    9    ///< If antispoofing algorithms are applied, this settings determines trade-off between security and user's convenience.
#define ABS_PARAM_OPEN_TOTAL_TIMEOUT    10    ///< Total open-session timeout.
#define ABS_PARAM_OPEN_RETRY_UI_NOTIFY_TIMEOUT    11    ///< Timeout to user-interface notification about the reopen attempt.
#define ABS_PARAM_OPEN_RETRY_DELAY    12    ///< Delay between two subsequent session reopen attempts.
#define ABS_PARAM_IFACE_VERSION    13    ///< Read-only global parameter which determines version of BSAPI interface.
#define ABS_PARAM_POWER_SAVE_CHECK_KEYBOARD    14    ///< This global parameter determines if keyboard and mouse are treated as an user activity.
#define ABS_PARAM_LATENT_CHECK    16    ///< This global parameter determines whether antilatent checks are performed implicitely.
#define ABS_PARAM_SENSOR_SECURITY    17    ///< This global parameter determines security level of communication between fingerprint device and computer.
#define ABS_PARAM_POWER_SAVE_ACTIVE_TO_SLEEP_TIMEOUT    18    ///< Determines timeout since last user activity to enable sensor sleeping.
#define ABS_PARAM_POWER_SAVE_RESET_ON_OPERATION_START    19    ///< This global parameter specifies whether power save timeouts are reset on operation start.
#define ABS_PARAM_IGNORE_BIOMETRIC_TIMEOUT    20    ///< This global parameter determines whether biometric timeout reported by device is ignore or not.
#define ABS_PARAM_CONSOLIDATION_COUNT_MIN    21    ///< Specifies minimal count of finger swipes for consolidation.
#define ABS_PARAM_CONSOLIDATION_COUNT_MAX    22    ///< Specifies maximal count of finger swipes for consolidation.
#define ABS_PARAM_IMAGE_ENHANCEMENT    23    ///< Enables image enhancement postprocessing.
#define ABS_PARAM_DISABLE_FFE    24    ///< Disables Faint Finger Enhancement.
#define ABS_PARAM_DYNAMIC_GAIN    25    ///< Enables image dynamic gain.

/** 
 * These constants are intended as possible values of parameter 
 * ABS_PARAM_CONSOLIDATION_TYPE.
 */
#define ABS_CONSOLIDATION_NORMAL    0    ///< Normal consolidation algorithm is used.
#define ABS_CONSOLIDATION_CONVENIENT    1    ///< Convenient consolidation algorithm is used.
#define ABS_CONSOLIDATION_STRICT    2    ///< Strict consolidation algorithm is used.

/** 
 * These constants are intended as possible values of parameter 
 * ABS_PARAM_MATCH_LEVEL.
 */
#define ABS_MATCH_MIN_SECURITY    1    ///< Minimal security setting.
#define ABS_MATCH_LOWER_SECURITY    2    ///< Lower security setting.
#define ABS_MATCH_MEDIUM_SECURITY    3    ///< Medium security setting.
#define ABS_MATCH_HIGHER_SECURITY    4    ///< Higher security setting.
#define ABS_MATCH_MAX_SECURITY    5    ///< Maximal security setting.

/** 
 * These constants are intended as possible values of parameter 
 * ABS_PARAM_ANTISPOOFING_POLICY.
 */
#define ABS_ANTISPOOFING_DISABLED    0    ///< Antispoofing checks are explicitly turned off on the fingerprint sensor. This is default value.
#define ABS_ANTISPOOFING_AUTODETECT    1    ///< Antispoofing checks are explicitly turned on on the fingerprint sensor if the device supports it.
#define ABS_ANTISPOOFING_DEVICE_DEFAULT    2    ///< Antispoofing settings are not touched in any way so default settings (device dependent) are used.

/** 
 * These constants are intended as possible values of parameter 
 * ABS_PARAM_SENSOR_SECURITY.
 */
#define ABS_SENSOR_SECURITY_LOW    0    ///< BSAPI always uses lower security of communication with fingerprint device.
#define ABS_SENSOR_SECURITY_NORMAL    1    ///< BSAPI automatically decides what secutritu level to use.
#define ABS_SENSOR_SECURITY_HIGH    2    ///< BSAPI always uses higher security of communication with fingerprint device.



/** 
 * These codes are used as values for dwMsgID parameter of ABS_CALLBACK. 
 */
#define ABS_MSG_PROCESS_BEGIN    0x11000000    ///< New process stage of the interactive operation begun.
#define ABS_MSG_PROCESS_END    0x12000000    ///< Process stage of the interactive operation ended.
#define ABS_MSG_PROCESS_SUSPEND    0x13000000    ///< Execution of the interactive operation has been suspended.
#define ABS_MSG_PROCESS_RESUME    0x14000000    ///< The interactive operation has been resumed.
#define ABS_MSG_PROCESS_PROGRESS    0x15000000    ///< Informs that the operation is in progress.
#define ABS_MSG_PROCESS_SUCCESS    0x16000000    ///< Informs that the process has succeeded.
#define ABS_MSG_PROCESS_FAILURE    0x17000000    ///< Informs that the operation has failed.
#define ABS_MSG_PROMPT_SCAN    0x21000000    ///< Callback should prompt the user to swipe his finger.
#define ABS_MSG_PROMPT_TOUCH    0x22000000    ///< Callback should prompt user to touch the sensor.
#define ABS_MSG_PROMPT_KEEP    0x23000000    ///< Callback should prompt user to keep the finger on the sensor.
#define ABS_MSG_PROMPT_LIFT    0x24000000    ///< Callback should prompt the user to left his finger from the sensor.
#define ABS_MSG_PROMPT_CLEAN    0x25000000    ///< Callback should prompt the user to clean the sensor.
#define ABS_MSG_QUALITY    0x30000000    ///< Swipe quality is low.
#define ABS_MSG_QUALITY_CENTER_HARDER    0x31000000    ///< Swipe quality is low. User should center his finger on the sensor and press harder.
#define ABS_MSG_QUALITY_CENTER    0x31100000    ///< Swipe quality is low. User should center his finger on the sensor.
#define ABS_MSG_QUALITY_TOO_LEFT    0x31110000    ///< Swipe quality is low. The swipe is too left.
#define ABS_MSG_QUALITY_TOO_RIGHT    0x31120000    ///< Swipe quality is low. The swipe is too right.
#define ABS_MSG_QUALITY_TOO_HIGH    0x31130000    ///< Swipe quality is low. The swipe is too high.
#define ABS_MSG_QUALITY_TOO_LOW    0x31140000    ///< Swipe quality is low. The swipe is too low.
#define ABS_MSG_QUALITY_HARDER    0x31200000    ///< User should press harder.
#define ABS_MSG_QUALITY_TOO_LIGHT    0x31210000    ///< Swipe quality is low. The swipe is too light.
#define ABS_MSG_QUALITY_TOO_DRY    0x31220000    ///< Swipe quality is low. The swipe is too dry.
#define ABS_MSG_QUALITY_TOO_SMALL    0x31230000    ///< Swipe quality is low. The swipe is too small.
#define ABS_MSG_QUALITY_TOO_SHORT    0x32000000    ///< Swipe quality is low. The swipe is too short.
#define ABS_MSG_QUALITY_TOO_FAST    0x33000000    ///< Swipe quality is low. The swipe is too fast.
#define ABS_MSG_QUALITY_TOO_SKEWED    0x34000000    ///< Swipe quality is low. The swipe is too skewed.
#define ABS_MSG_QUALITY_TOO_DARK    0x35000000    ///< Swipe quality is low. The swipe is too dark.
#define ABS_MSG_QUALITY_BACKWARD    0x36000000    ///< Swipe quality is low. The swipe is moved backward.
#define ABS_MSG_QUALITY_JOINT    0x37000000    ///< Swipe quality is low. Joint has been detected.
#define ABS_MSG_NAVIGATE_CHANGE    0x41000000    ///< Notifies about navigation change (user has moved his finger, touched the sensor of left the finger). Applies only during navigation operation.
#define ABS_MSG_NAVIGATE_CLICK    0x42000000    ///< Notifies that the user clicked on sensor by his finger. Applies only during navigation operation.
#define ABS_MSG_DLG_SHOW    0x51000000    ///< Notifies that the feedback dialog should be shown.
#define ABS_MSG_DLG_HIDE    0x52000000    ///< Notifies that the feedback dialog should be hidden.
#define ABS_MSG_IDLE    0x0    ///< Special message, which gives the callback a chance to cancel the interactive operation.


#ifdef __cplusplus
}       /* extern "C" */
#endif

#endif  /* bstypes_h */

