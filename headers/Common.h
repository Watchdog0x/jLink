#ifndef COMMON_H
#define COMMON_H

/* --------------------------------------------------------------------
 *
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Audio
 *  G    G  N   N N
 *  GGGGGG  N    NN
 *
 *  Copyright (c) 2021, GN-Audio
 * -------------------------------------------------------------------- */

/**
 * @file Common.h
 * @brief Defines the public common interface for the Jabra SDK.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <stdint.h>
#include <wchar.h>

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/
#if defined _WIN32 || defined __CYGWIN___
#define LIBRARY_API extern "C" __declspec(dllexport)
#else
#ifdef __APPLE__
#ifdef __cplusplus
#define LIBRARY_API extern "C" __attribute__ ((visibility ("default")))
#else
#define LIBRARY_API __attribute__ ((visibility ("default")))
#endif
#include <stdbool.h>
#elif __linux__
#ifdef __cplusplus
#define LIBRARY_API extern "C" __attribute__ ((visibility ("default")))
#else
#define LIBRARY_API __attribute__ ((visibility ("default")))
#include <stdbool.h>
#endif
#endif
#endif

#if defined _WIN32 || defined __CYGWIN___
#define LIBRARY_VAR extern "C" __declspec(dllexport)
#else
#ifdef __cplusplus
#define LIBRARY_VAR extern "C" __attribute__ ((visibility ("default")))
#else
#define LIBRARY_VAR extern __attribute__ ((visibility ("default")))
#endif
#endif

#define DEFINE_CODE(a,b) a,
/**
 * @brief This enum is used for the return values from API.
 */
typedef enum _ReturnCode
{
#include "returncodes.inc"
    NUMBER_OF_JABRA_RETURNCODES
} Jabra_ReturnCode;
#undef DEFINE_CODE

#define DEFINE_CODE(a,b) a,
typedef enum _ErrorStatus
{
#include "errorcodes.inc"
    NUMBER_OF_JABRA_ERRORCODES
} Jabra_ErrorStatus;
#undef DEFINE_CODE

typedef enum _DeviceConnectionType
{
    USB = 0,
    BT,
    DECT
} DeviceConnectionType;

/** @brief Device description struct, identifies attached devices. */
typedef struct _DeviceInfo
{
    /** @brief Device identifier, used for most API calls to identify the device
     * to operate on. */
    unsigned short deviceID;
    /** @brief Product identifier, used for identifying the type of product. */
    unsigned short productID;
    /** @brief Vendor identifier, used for identifying the vendor. Jabra vendor
     * ID is 0x0B0E. */
    unsigned short vendorID;
    char* deviceName;
    char* usbDevicePath;
    char* parentInstanceId;
    Jabra_ErrorStatus errStatus;
    bool isDongle;
    char* dongleName;
    char* variant;
    char* serialNumber;
    bool isInFirmwareUpdateMode;
    DeviceConnectionType deviceconnection;
    unsigned long connectionId; // Not currently used
    unsigned short parentDeviceId;
} Jabra_DeviceInfo;

/**
 * This struct represents each button event type info. For example: Tap
 * (00), Press(01), Double Tap(02) etc. */
typedef struct _ButtonEventType
{
    /** Hex value for button event. Key can be 00 for Tap, 01 for Press, 02
     * for double tap etc. */
    unsigned short key;
    /** Description of button event. For example: value can be "Tap" or
     * "Press" or "Double tap". */
    char* value;
} ButtonEventType;

/**
 * This struct represents each Remote MMI info. For example Volume up/down
 * button is supported by Tap, MFB button is supported by Tap/Press/Double Tap.
 */
typedef struct _ButtonEventInfo
{
    /** Hex value for button type. For example: Volume up(01), Volume down(02)
     * etc. */
    unsigned short buttonTypeKey;
    /** Description of button type. For example: buttonTypeValue can be
     * "Volume Up" or "Volume Down" or "MFB". */
    char* buttonTypeValue;
    /** Number of button events under a button type. Ex. If MFB is supported by
     * "Tap", "Press", "Double Tap", then buttonEventTypeSize is 3. */
    int buttonEventTypeSize;
    /** Button event information of all button event types of the device. */
    ButtonEventType* buttonEventType;
} ButtonEventInfo;

/** This struct represents Remote MMI's available for the device. */
typedef struct _ButtonEvent
{
    /** Number of Remote MMI's available for the device. If device supports
     * "Volume Up", "Volume Down" and "MFB" as remote MMI, buttonEventCount
     * is 3. */
    int buttonEventCount;
    /** Remote MMI information of all button events of the device. */
    ButtonEventInfo* buttonEventInfo;
} ButtonEvent;

/** Predefined inputs enum. */
typedef enum Jabra_HidInput
{
    Undefined,
    OffHook,
    Mute,
    Flash,
    Redial,
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeyStar,
    KeyPound,
    KeyClear,
    Online,
    SpeedDial,
    VoiceMail,
    LineBusy,
    RejectCall,
    OutOfRange,
    PseudoOffHook,
    Button1,
    Button2,
    Button3,
    VolumeUp,
    VolumeDown,
    FireAlarm,
    JackConnection,
    QDConnection,
    HeadsetConnection,
} Jabra_HidInput;

/** Equalizer. */
typedef struct _EqualizerBand
{
    /** The gain (or attenuation) range in dB which the device can handle. Only
     * the positive value (gain) is given, the max attenuation is the
     * corresponding negative value. Read-only. */
    float max_gain;
    /** Band center frequency in Hz. Read-only. */
    int centerFrequency;
    /** The current gain setting [dB] for the band. Must be numerically <=
     * max_gain. Read-only. */
    float currentGain;
} Jabra_EqualizerBand;

/** Logging Flags. */
typedef enum _Logging
{
    Local = 0,
    Cloud,
    All
} Jabra_Logging;

typedef enum _UploadEventStatus
{
    Upload_InProgress = 0,
    Upload_Completed,
    Upload_Error,
} Jabra_UploadEventStatus;

/** Features that may be supported by devices. @see Jabra_IsFeatureSupported */
typedef enum _DeviceFeature
{
    BusyLight = 1000,
    FactoryReset = 1001,
    PairingList = 1002,
    RemoteMMI = 1003,
    MusicEqualizer = 1004,
    EarbudInterconnectionStatus = 1005,
    StepRate = 1006,
    HeartRate = 1007,
    RRInterval = 1008,
    RingtoneUpload = 1009,
    ImageUpload = 1010,
    NeedsExplicitRebootAfterOta = 1011,
    NeedsToBePutIncCradleToCompleteFwu = 1012,
    RemoteMMIv2 = 1013,
    Logging = 1014,
    PreferredSoftphoneListInDevice = 1015,
    VoiceAssistant = 1016,
    PlayRingtone = 1017,
    SetDateTime = 1018,
    FullWizardMode = 1019,
    LimitedWizardMode = 1020,
    OnHeadDetection = 1021,
    SettingsChangeNotification = 1022,
    AudioStreaming = 1023,
    CustomerSupport = 1024,
    MySound = 1025,
    UIConfigurableButtons = 1026,
    ManualBusyLight = 1027,
    Whiteboard = 1028,
    Video = 1029,
    AmbienceModes = 1030,
    SealingTest = 1031,
    AMASupport = 1032,
    AmbienceModesLoop = 1033,
    FFANC = 1034,
    GoogleBisto = 1035,
    VirtualDirector = 1036,
    PictureInPicture = 1037,
    DateTimeIsUTC = 1038,       // Time in device is UTC
    RemoteControl = 1039,       // Device has physical remote control
    UserConfigurableHDR = 1040, // User is allowed to change brightness, contrast etc. while HDR is enabled
    DECTBasicPairing = 1041,    // Regular pairing without any key exchange
    DECTSecurePairing = 1042,   // Device supports secure pairing using key exchange over USB
    DECTOTAFWUSupported = 1043, // Device supports DECT OTA firmware updating
    XpressURL = 1044,           // Device can be configured with an Xpress URL for stand-alone management
    PasswordProvisioning = 1045,// Device can store a password for settings protection
    Ethernet = 1046,            // Ethernet connectivity
    WLAN = 1047,                // WLAN connectivity
    EthernetAuthenticationCertificate = 1048, // Certificate-based Ethernet authentication
    EthernetAuthenticationMSCHAPv2 = 1049,    // User/pass-based Ethernet authentication (MS-CHAPv2)
    WLANAuthenticationCertificate = 1050,     // Certificate-based WLAN authentication
    WLANAuthenticationMSCHAPv2 = 1051         // User/pass-based WLAN authentication (MS-CHAPv2)
} DeviceFeature;

/** @brief This struct represents the product registration info. */
typedef struct _ProductRegistration
{
    const char* firstName;
    const char* lastName;
    const char* email;
    const char* country;
    const char* appVersion;
    const char* osName;
    const char* osVersion;
    const char* locale;
    bool marketingConsent;
} ProductRegInfo;

typedef enum _AVRCPCommand
{
    AVRCPPlay = 0,
    AVRCPPause,
    AVRCPStop,
    AVRCPToggle,
    AVRCPPrevious,
    AVRCPNext
} AVRCPCommand;

typedef enum _SystemComponentID
{
    PRIMARY_HEADSET,
    SECONDARY_HEADSET,
    CRADLE,
    OTHER
} SystemComponentID;

typedef struct _MapEntry_Int_String
{
    int key;            // Refers to SystemComponentID
    char* value;
} MapEntry_Int_String;

typedef struct _Map_Int_String
{
    int length;
    MapEntry_Int_String* entries;
} Map_Int_String;

/** Structure used with #Jabra_SetDateTime and #Jabra_GetDateTime. */
typedef struct _timedate_t
{
    /** Seconds, range is [0-59]. */
    int sec;
    /** Minutes, range is [0-59]. */
    int min;
    /** Hours, range is [0-23]. */
    int hour;
    /** Day of month, range is [1-31]. */
    int mday;
    /** Month, range is [0-11]. */
    int mon;
    /** Year, range is [0-n], where 0 is 1900CE. */
    int year;
    /** Day of week, range is [0-6] where 0 is Sunday. */
    int wday;
} timedate_t;

/** Bitmasks for use with #Jabra_SetSubscribedDeviceEvents and
 * #Jabra_GetSupportedDeviceEvents. */
LIBRARY_VAR const uint32_t DEVICE_EVENT_AUDIO_READY;

typedef enum _AUDIO_FILE_FORMAT
{
    AUDIO_FILE_FORMAT_NOT_USED = 0,
    AUDIO_FILE_FORMAT_WAV_UNCOMPRESSED,
    AUDIO_FILE_FORMAT_ULAW_COMPRESSED,
    AUDIO_FILE_FORMAT_SBC_COMPRESSED,
    AUDIO_FILE_FORMAT_G72_COMPRESSED,
} AUDIO_FILE_FORMAT;

/** Structure represents the parameters for uploading audio file to device. */
typedef struct _audioFileParams
{
    /** Audio file format allowed. */
    AUDIO_FILE_FORMAT audioFileType;
    /** Number of channels present. */
    unsigned int numChannels;
    /** Bits per sample. */
    unsigned int bitsPerSample;
    /** Sample rate of the audio. */
    unsigned int sampleRate;
    /** Maximum file size allowed. */
    unsigned int maxFileSize;
} Jabra_AudioFileParams;

/**
 * Types of remote MMIs, use #Jabra_GetRemoteMmiTypes to determine the types
 * supported for the device in question.
 * @note RemoteMMIv2 only.
 */
typedef enum _RemoteMmiType
{
    MMI_TYPE_MFB = 0,
    MMI_TYPE_VOLUP = 1,
    MMI_TYPE_VOLDOWN = 2,
    MMI_TYPE_VCB = 3,
    MMI_TYPE_APP = 4,
    MMI_TYPE_TR_FORW = 5,
    MMI_TYPE_TR_BACK = 6,
    MMI_TYPE_PLAY = 7,
    MMI_TYPE_MUTE = 8,
    MMI_TYPE_HOOK_OFF = 9,
    MMI_TYPE_HOOK_ON = 10,
    MMI_TYPE_BLUETOOTH = 11,
    MMI_TYPE_JABRA = 12,
    MMI_TYPE_BATTERY = 13,
    MMI_TYPE_PROG = 14,
    MMI_TYPE_LINK = 15,
    MMI_TYPE_ANC = 16,
    MMI_TYPE_LISTEN_IN = 17,
    MMI_TYPE_DOT3 = 18,
    MMI_TYPE_DOT4 = 19,
    MMI_TYPE_MEDIA = 20,
    SEPERATOR_FOR_MMI_TYPE = 128, /* not to be used */
    MMI_TYPE_BUSYLIGHT = SEPERATOR_FOR_MMI_TYPE,
    MMI_TYPE_LED_BUSYLIGHT = SEPERATOR_FOR_MMI_TYPE,
    MMI_TYPE_LED_MULTIFUNCTIONAL = SEPERATOR_FOR_MMI_TYPE + 1,
    MMI_TYPE_LED_MUTE = SEPERATOR_FOR_MMI_TYPE + 2
} RemoteMmiType;

/**
 * Remote MMI sequences, used to identify supported output LEDs (as a bitmask)
 * and for setting the output LEDs (single bit).
 * @note RemoteMMIv2 only.
 */
typedef enum _RemoteMmiSequence
{
    MMI_LED_SEQUENCE_OFF    = 0x01,
    MMI_LED_SEQUENCE_ON     = 0x02,
    MMI_LED_SEQUENCE_SLOW   = 0x04,
    MMI_LED_SEQUENCE_FAST   = 0x08
} RemoteMmiSequence;

/**
 * Remote MMI priorities.
 * @note RemoteMMIv2 only.
 */
typedef enum _RemoteMmiPriority
{
    /**
     * Used for remote MMIs that does not support priority.
     */
    MMI_PRIORITY_NONE = 0x00,
    /**
     * Get remote MMI focus if device doesn't use it or no function is assigned
     * to the button.
     */
     MMI_PRIORITY_LOW = 0x01,
     /**
      * Get remote MMI focus unconditionally, this can remove important
      * functionality from the device.
      */
      MMI_PRIORITY_HIGH = 0x02
} RemoteMmiPriority;

/**
 * Remote MMI action to use in #Jabra_SetRemoteMmiAction for setting the MMI
 * output LED(s). Only single bit value of RemoteMmiSequence can be specified
 * as parameter RemoteMmiActionOutput to #Jabra_SetRemoteMmiAction.
 * @note RemoteMMIv2 only.
 */
typedef struct _RemoteMmiActionOutput
{
    /** Red LED output component to set. */
    uint8_t red;
    /** Green LED output component to set. */
    uint8_t green;
    /** Blue LED output component to set. */
    uint8_t blue;
    /** Output sequence to set. */
    RemoteMmiSequence sequence;
} RemoteMmiActionOutput;

/**
 * Supported remote MMI output LED colours.
 * @note RemoteMMIv2 only.
 */
typedef struct _RemoteMmiOutput
{
    /** Red LED supported. */
    bool red;
    /** Green LED supported. */
    bool green;
    /** Blue LED supported. */
    bool blue;
} RemoteMmiOutput;

/**
 * Remote MMI input actions.
 * Remote MMI input, used to identify supported input actions (as a bitmask)
 * and for reporting input events via the RemoteMmiCallback callback
 * (as single bit).
 * @note RemoteMMIv2 only.
 */
typedef enum _RemoteMmiInput
{
    MMI_ACTION_NONE          = 0x00,
    MMI_ACTION_UP            = 0x01,
    MMI_ACTION_DOWN          = 0x02,
    MMI_ACTION_TAP           = 0x04,
    MMI_ACTION_DOUBLE_TAP    = 0x08,
    MMI_ACTION_PRESS         = 0x10,
    MMI_ACTION_LONG_PRESS    = 0x20,
    MMI_ACTION_X_LONG_PRESS  = 0x40
} RemoteMmiInput;

/**
 * Remote MMI definitions for the supported MMIs.
 * @note RemoteMMIv2 only.
 */
typedef struct _RemoteMmiDefinition
{
    /** Supported type. */
    RemoteMmiType type;
    /** Mask of supported priorities. */
    RemoteMmiPriority priorityMask;
    /** Mask of supported output LED sequences. */
    RemoteMmiSequence sequenceMask;
    /** Mask of supported inputs. */
    RemoteMmiInput inputMask;
    /** Supported output LED colours. */
    RemoteMmiOutput output;
} RemoteMmiDefinition;

typedef struct _PanicListDevType
{
    uint8_t panicCode[25];
} Jabra_PanicListDevType;

typedef struct _PanicListType
{
    unsigned int entriesNo;
    /** Array with dynamic length 1..x. */
    Jabra_PanicListDevType* panicList;
} Jabra_PanicListType;

typedef struct _PanicCodes
{
    //the size of the panic codes array returned from the device.
    uint8_t size;
    //the array to hold the panic codes. As for how many panic codes in the array, please reference the above `size` of the struct.
    uint16_t codes[20];
} Jabra_PanicCodes;

/**
 * WizardModes to be used in #Jabra_SetWizardMode and #Jabra_GetWizardMode.
 */
typedef enum _WizardModes
{
    FULL_WIZARD = 0x00,
    LIMITED_WIZARD = 0x01,
    NO_WIZARD = 0x02
} WizardModes;

/** @brief Definition of behavior of the internal DeviceCatalogue. */
typedef struct
{
    /** Full path of zip file to preload (same as #Jabra_PreloadDeviceInfo, which
     * will be deprecated, may be NULL. */
    const char* preloadZipFile;
    /** When refreshing data for existing devices, wait this time before going
     * online to reduce the risk of cache locks and reduce the CPU load at
     * startup. Default: 30s. */
    unsigned delayInSecondsBeforeStartingRefresh;
    /** When a device is connected, update device data in the background (using
     * delayInSecondsBeforeStartingRefresh). Default: true. */
    bool refreshAtConnect;
    /** At SDK startup, update data for all previously connected devices in the
     * background (using  delayInSecondsBeforeStartingRefresh). Default: true. */
    bool refreshAtStartup;
    /** When refreshing, what should be in scope:  0: nothing (= block
     * refreshes), 1:all previously connected devices. Default: 1. */
    int refreshScope;
    /** If true: when an unknown device connects, data is updated in the
     * background (ignoring the delay in delayInSecondsBeforeStartingRefresh),
     * and an update notification is delivered to the onDeviceDataUpdated
     * callback. If false: device data is fetched synchronously (as before).
     * Default: false. */
    bool fetchDataForUnknownDevicesInTheBackground;
    /** If not NULL: called when data for a connected device is (partially or
     * fully) updated. */
    void (*onDeviceDataUpdated)(unsigned short deviceID);
    /** Only update device data if data is older than this (seconds)
     * Default: 24 hours (24 * 60 * 60). */
    unsigned minimumAgeBeforeUpdate;
} DeviceCatalogue_params;

/** For use with ConfigParams.cloudConfig_params */
typedef struct _ConfigParams_cloud
{
    /** if true, all network access is blocked. */
    bool blockAllNetworkAccess;

    /**
     * @brief optional. The host and path (up to, but excluding the '?') of the
     * source for capability files. The responding host is responsible for
     * parsing the entire URL with parameters delivered and produce a response
     * that is equivalent to the response from the default Jabra endpoints.
     * see https://devicecapabilities.jabra.com/swagger/ui/index (note: v4)
     * Special cases: NULL or "": use the default.
     */
    const char* baseUrl_capabilities;

    /**
     * @brief optional. The host and partial path of the source for FW files.
     * The responding host is responsible for parsing the entire URL with
     * parameters delivered and produce a response that is equivalent to the
     * response from the Jabra endpoints.
     * example: https://firmware.jabra.com/v4
     * See https://firmware.jabra.com/swagger/#/v3 for full URL and parameters
     * Special cases: NULL or "": use the default.
     */
    const char* baseUrl_fw;

    /**
     * @brief optional. Specify the proxy to use. NULL or "" if a proxy should
     * not be used. Example: "https://myproxyhost:8042". Supported proxy types,
     * https://curl.haxx.se/libcurl/c/CURLOPT_PROXY.html
     */
    const char* proxy;
} ConfigParams_cloud;

/** Parameters for configuring the SDK at initialization. */
typedef struct _Config_params
{
    /** Optional config for the device catalogue. May be NULL. */
    DeviceCatalogue_params* deviceCatalogue_params;
    /** Optional configuration of cloud access. May be NULL. */
    ConfigParams_cloud* cloudConfig_params;
    /** For internal Jabra use. */
    void* reserved2;
} Config_params;

/** The connection status of the audio jack connector on the device (not supported by all devices) */
typedef struct _JackStatus
{
    bool inserted;
} JackStatus;

/** The link connection status component */
typedef enum _LinkStatusComponent
{
    RIGHT_EARBUD = 0,
    LEFT_EARBUD  = 1
} LinkStatusComponent;

/** The connection status of the link e.g. left earbud connected or not (not supported by all devices) */
typedef struct _LinkConnectStatus
{
    bool open;
    LinkStatusComponent component;
} LinkConnectStatus;

/** The status of the on-head detection of the device (not supported by all devices) */
typedef struct _HeadDetectionStatus
{
    bool leftOn; /** true: left earcup is on head (false: off) */
    bool rightOn; /** true: right earcup is on head (false: off) */
} HeadDetectionStatus;

/** The values BusyLightStatus can be set to. */
typedef enum _BusyLightValue
{
    BUSYLIGHT_ON,       /** Busy */
    BUSYLIGHT_OFF,      /** Not busy */
    BUSYLIGHT_TOGGLE    /** Busy if current is not busy, not busy if current is busy */
} BusyLightValue;

/** Listener for JackStatus events */
typedef void (*JackConnectorStatusListener)(unsigned short deviceID, const JackStatus status);

/** Listener for HeadDetectionStatus events */
typedef void (*HeadDetectionStatusListener)(unsigned short deviceID, const HeadDetectionStatus status);

/** Listener for link connection status events */
typedef void (*LinkConnectionStatusListener)(unsigned short deviceID, const LinkConnectStatus status);

/** Listener for Manual Busylight change events */
typedef void (*BusylightChangeListener)(unsigned short deviceID, bool isOn);

/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

/**
 * @brief Get the SDK version.
 * @param[in,out] version Pointer to buffer used to hold the SDK version. The
 * buffer must be allocated by the caller prior to calling this function.
 * @param[in,out] count Character count, at time of call count must the size
 * of the version buffer, at return count hols the count of the actual
 * characters written to the version buffer.
 * @return Return_Ok            Call was successful
 * @return Return_ParameterFail version is NULL or buffer too small
 * @note This function can be called without #Jabra_Initialize being called.
 * @ingroup g-sdk
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetVersion(char* const version, int count);

/**
 * @brief Sets the Application ID. The application ID must be set before
 * #Jabra_Initialize is called. The application ID can requested via the
 * Jabra Developer Zone https://developer.jabra.com
 * @param[in] inAppID ID for the application.
 * @ingroup g-sdk
 */
LIBRARY_API void Jabra_SetAppID(const char* inAppID);

/**
 * @brief Library initialization - only intended to be called once.
 * @param[in] FirstScanForDevicesDoneFunc Callback method, called when USB scan
 * is done. Can be NULL if not used.
 * @param[in] DeviceAttachedFunc Callback method, called when a device is
 * attached. Can be NULL if not used. Callee must call #Jabra_FreeDeviceInfo to
 * free memory.
 * @param[in] DeviceRemovedFunc Callback method, called when a device is
 * removed. Can be NULL if not used.
 * @param[in] ButtonInDataRawHidFunc Callback method, called on new input data.
 * HID Events will (default) NOT be triggered for standard HID to avoid conflicts
 * Raw HID. Low-level. Can be NULL if not used. 
 * @param[in] ButtonInDataTranslatedFunc Callback method, called on new input
 * data. High-level. Can be NULL if not used.
 * @param[in] nonJabraDeviceDectection true non Jabra and Jabra devices will be detected,
 * false only Jabra devices will be detected. Non Jabra device detection is not supported on Linux
 * @param[in] configParams Optional configuration of various SDK library
 * behavior. Can be NULL if not used.
 * @return true if library initialization is successful.
 * @return false if library initialization is not successful. One reason could
 * be that the library is already initialized or that #Jabra_SetAppID has not
 * been called prior to calling this function.
 * @note AppID must be set using #Jabra_SetAppID before the library
 * initialization is called. If not the initialization fails.
 * @ingroup g-events
 * @ingroup g-sdk
 */
LIBRARY_API bool Jabra_InitializeV2(
    void(*FirstScanForDevicesDoneFunc)(void),
    void(*DeviceAttachedFunc)(Jabra_DeviceInfo deviceInfo),
    void(*DeviceRemovedFunc)(unsigned short deviceID),
    void(*ButtonInDataRawHidFunc)(unsigned short deviceID, unsigned short usagePage, unsigned short usage, bool buttonInData),
    void(*ButtonInDataTranslatedFunc)(unsigned short deviceID, Jabra_HidInput translatedInData, bool buttonInData),
    bool nonJabraDeviceDectection,
    Config_params* configParams
);

/**
 * @deprecated This API is going to be deprecated, consider using Jabra_InitializeV2 instead
 * @brief Library initialization - only intended to be called once.
 * @param[in] FirstScanForDevicesDoneFunc Callback method, called when USB scan
 * is done. Can be NULL if not used.
 * @param[in] DeviceAttachedFunc Callback method, called when a device is
 * attached. Can be NULL if not used. Callee must call #Jabra_FreeDeviceInfo to
 * free memory.
 * @param[in] DeviceRemovedFunc Callback method, called when a device is
 * removed. Can be NULL if not used.
 * @param[in] ButtonInDataRawHidFunc Callback method, called on new input data.
 * HID Events will (default) NOT be triggered for standard HID to avoid conflicts
 * Raw HID. Low-level. Can be NULL if not used.
 * @param[in] ButtonInDataTranslatedFunc Callback method, called on new input
 * data. High-level. Can be NULL if not used.
 * @param[in] instance Optional instance number. Can be 0 if not used.
 * @param[in] configParams Optional configuration of various SDK library
 * behavior. Can be NULL if not used.
 * @return true if library initialization is successful.
 * @return false if library initialization is not successful. One reason could
 * be that the library is already initialized or that #Jabra_SetAppID has not
 * been called prior to calling this function.
 * @note AppID must be set using #Jabra_SetAppID before the library
 * initialization is called. If not the initialization fails.
 */
LIBRARY_API bool Jabra_Initialize(
    void(*FirstScanForDevicesDoneFunc)(void),
    void(*DeviceAttachedFunc)(Jabra_DeviceInfo deviceInfo),
    void(*DeviceRemovedFunc)(unsigned short deviceID),
    void(*ButtonInDataRawHidFunc)(unsigned short deviceID, unsigned short usagePage, unsigned short usage, bool buttonInData),
    void(*ButtonInDataTranslatedFunc)(unsigned short deviceID, Jabra_HidInput translatedInData, bool buttonInData),
    unsigned int instance,
    Config_params* configParams
);

/**
 * @brief Library uninitialize
 * @return true             Library uninitialization was successful
 * @return false            Library uninitialization was unsuccessful
 * (for example if called when not initialized).
 * @ingroup g-sdk
 */
LIBRARY_API bool Jabra_Uninitialize(void);

/**
 * @brief Enable HID events from non Jabra devices
 * @param[in] hidEvents true = HID events are send to app, false = HID events are discarded
 * @return Return_Ok            Call was successful
 * @return Non_Jabra_Device_Detection_disabled Non-jabra device detection is disabled
 * @return System_Error         Device manager instance is not available
 * @ingroup g-events
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetHidEventsFromNonJabraDevices(bool hidEvents);

/**
 * @brief Are HID events from non Jabra devices enabled
 * @return true             HID events are enabled
 * @return false            HID events are not enabled
 * @ingroup g-events
 */
LIBRARY_API bool Jabra_IsHidEventsFromNonJabraDevicesEnabled(void);

/**
 * @brief Enable HID events from Jabra devices
 * @param[in] hidEvents true = HID events are send to app, false = HID events are discarded
 * @ingroup g-events
 */
LIBRARY_API void Jabra_SetStdHidEventsFromJabraDevices(bool hidEvents);

/**
 * @brief Are HID events from Jabra devices enabled
 * @return true             HID events are enabled
 * @return false            HID events are not enabled
 * @ingroup g-events
 */
LIBRARY_API bool Jabra_IsStdHidEventsFromJabraDevicesEnabled(void);

/**
 * @brief Check if device scan is done
 * @return true             USB device scan is done
 * @return false            USB device scan is not done
 * @note Library initialization must be performed before calling this function.
 * @ingroup g-dev-scan
 */
LIBRARY_API bool Jabra_IsFirstScanForDevicesDone(void);

/**
 * @brief Check if a device is attached
 * @param[in] deviceID ID for specific device.
 * @return true             Device is attached
 * @return false            Device is not attached
 * @ingroup g-dev-scan
 */
LIBRARY_API bool Jabra_IsDeviceAttached(unsigned short deviceID);

/**
 * @brief Get information of all attached devices
 * @param[in] count Pointer to an integer that has the number of
 * #Jabra_DeviceInfo structures allocated before calling this function.
 * On return this pointer has the value of how many devices that was added.
 * @param[in] deviceInfoList Pointer to an array of #Jabra_DeviceInfo to be
 * populated.
 * @note call #Jabra_FreeDeviceInfo on each object in the list when done do
 * avoid a memory leak.
 * @see Jabra_FreeDeviceInfo
 * @ingroup g-dev-scan
 */
LIBRARY_API void Jabra_GetAttachedJabraDevices(int* count, Jabra_DeviceInfo* deviceInfoList);

/**
 * @brief Frees the #Jabra_DeviceInfo struct members
 * @param[in] info      #Jabra_DeviceInfo struct to be freed.
 * @see Jabra_GetAttachedJabraDevices
 * @ingroup g-dev-scan
 */
LIBRARY_API void Jabra_FreeDeviceInfo(Jabra_DeviceInfo info);

/**
* @deprecated This API has been deprecated, consider using Jabra_GetESN instead
 * @brief Get device        serial number
 * @param[in] deviceID      ID for a specific device
 * @param[in] serialNumber  Pointer to location where the serial number is
 * written. Must be allocated by the caller.
 * @param[in] count         Maximum number of characters to copy to serialNumber.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail serialNumber is NULL or buffer too small
 * @return No_Information       There is no information in the cloud regarding
 * the serial number.
 * @return NetworkRequest_Fail  The server is down or there was an error
 * during parsing.
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSerialNumber(unsigned short deviceID, char* const serialNumber, int count);

/**
 * @brief Get device ESN (electronic serial number).
 * @param[in] deviceID      ID for a specific device
 * @param[in] esn           Pointer to buffer location where the ESN is written. The
 * buffer must be allocated by the caller
 * @param[in] count         Maximum number of characters to copy to serialNumber
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail esn is NULL or buffer too small
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_GetESN}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetESN( unsigned short deviceID, char* const esn, int count);

/**
 * @brief Get device SKU (stock keeping unit).
 * @param[in] deviceID      ID for a specific device
 * @param[in] sku           Pointer to buffer location where the SKU is written. The
 * buffer must be allocated by the caller
 * @param[in] count         Maximum number of characters to copy to sku
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail sku is NULL or buffer too small
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSku(unsigned short deviceID, char* const sku, unsigned int count);

/**
 * @brief Get the hardware and config version of the device.
 * @param[in] deviceID          ID for a specific device
 * @param[in] HwVersion         Pointer to buffer where hardware version is saved
 * @param[in] configVersion     Pointer to buffer where config version is saved
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetHwAndConfigVersion(unsigned short deviceID, unsigned short *HwVersion, unsigned short *configVersion);

/**
 * @brief Get ESN for all device components. Some devices may be a system of
 * multiple devices, e.g., a TW headset (left earbud, right earbud, cradle).
 * @param[in] deviceID          ID for a specific device
 * @return Pointer to a map with the requested info (NULL on failure). Caller
 * is responsible for calling #Jabra_FreeMap to release the allocated memory
 * after use.
 * @see Jabra_FreeMap
 * @sa @wrap{Jabra_GetMultiESN}
 * @ingroup g-dev-info
 */
LIBRARY_API Map_Int_String* Jabra_GetMultiESN(unsigned short deviceID);

/**
 * @brief Release memory allocated by functions returning a Map_Int_String*
 * @param[in] map map to release.
 * @see Jabra_GetMultiESN
 * @ingroup g-dev-info
 */
LIBRARY_API void Jabra_FreeMap(Map_Int_String* map);

/**
 * @brief Get the language code for the current language of the device.
 * @param[in] deviceID          ID for a specific device
 * @param[out] languageCode     The code of the current language
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetCurrentLanguageCode}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetCurrentLanguageCode(unsigned short deviceID, unsigned short* languageCode);

/**
 * @brief Gets the device image path.
 * @param[in] deviceID          ID for a specific device.
 * @return The path of the device image.
 * @note As memory is allocated through SDK, needs to be freed by calling
 * #Jabra_FreeString.
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_GetDeviceImagePath}
 */
LIBRARY_API char* Jabra_GetDeviceImagePath(unsigned short deviceID);

/**
 * @brief Gets the device hires (1280x1280 px) image path.
 * @param[in] deviceID          ID for a specific device.
 * @return The path of the device image. Will return NULL if file does not exist.
 * @note As memory is allocated through SDK, needs to be freed by calling
 * #Jabra_FreeString.
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_GetDeviceHiresImagePath}
 */
LIBRARY_API char* Jabra_GetDeviceHiresImagePath(unsigned short deviceID);

/**
 * @brief Gets the device image thumbnail path.
 * @param[in] deviceID          ID for a specific device.
 * @return The path of the device image thumbnail.
 * @note As memory is allocated through SDK, need to be freed by calling
 * #Jabra_FreeString.
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_GetDeviceImageThumbnailPath}
 */
LIBRARY_API char* Jabra_GetDeviceImageThumbnailPath(unsigned short deviceID);


typedef enum _BatteryComponent
{
    UNKNOWN, /*!< Unable to determine the component. Try updating the SDK. */
    MAIN, /*!< Generally applies to headsets with headband that only contains one battery. */
    COMBINED, /*!< For headsets that contains multiple batteries but is not capable of sending each individual state. */
    RIGHT, /*!< The battery in the right unit */
    LEFT, /*!< The battery in the left unit */
    CRADLE_BATTERY, /*!< The battery in the cradle */
    REMOTE_CONTROL /*!< The battery in the remote control */
} BatteryComponent;

typedef struct _BatteryStatusUnitType
{
    /*Level in percent*/
    uint8_t levelInPercent;
    /*The component for which the level corresponds to. @see BatteryComponent*/
    BatteryComponent component;
} Jabra_BatteryStatusUnit;

typedef struct _BatteryStatusType
{
    /*Level in percent*/
    uint8_t levelInPercent;
    /*Indicates if the battery is charging or not*/
    bool charging;
    /*Indicates if the battery is low. The logic depends on the device and differs*/
    bool batteryLow;
    /*The component for which the level corresponds to. @see BatteryComponent*/
    BatteryComponent component;
    /*Count of extra units*/
    size_t extraUnitsCount;
    /*Contains additional information about other units in the headset - @see Jabra_BatteryStatusUnit.*/
    Jabra_BatteryStatusUnit* extraUnits;
} Jabra_BatteryStatus;

/**
 * @brief Get battery status, if supported by device.
 * @param[in] deviceID          ID for a specific device
 * @param[out] batteryStatus    Struct containing battery status
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_BadState      Failed while reading from device
 * @return Not_Supported        Functionality is not supported on this device
 * @note Since dongle does not have battery, SDK returns Not_Supported when
 * battery status is requested for dongle device.
 * @note As memory is allocated through SDK, need to be freed by calling
 * #Jabra_FreeBatteryStatus.
 * @see Jabra_RegisterBatteryStatusUpdateCallback
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetBatteryStatusV2(unsigned short deviceID, Jabra_BatteryStatus** batteryStatus);

/**
 * @brief Copy the content of a Jabra_BatteryStatus struct. See #Jabra_BatteryStatus.
 * @param[in] from          Pointer to source struct
 * @param[out] to           Pointer to destination struct. Must be preallocated by the caller.
*/
LIBRARY_API void Jabra_CopyJabraBatteryStatus(const Jabra_BatteryStatus* from, Jabra_BatteryStatus* to);

/**
 * @brief Frees the #Jabra_BatteryStatus
 * @param[in] batteryStatus     #Jabra_BatteryStatus struct to be freed
 */
LIBRARY_API void Jabra_FreeBatteryStatus(Jabra_BatteryStatus* batteryStatus);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_RegisterBatteryStatusUpdateCallbackV2.
 */
typedef void(*BatteryStatusUpdateCallbackV2)(unsigned short deviceID, Jabra_BatteryStatus* batteryStatus);

/**
 * @deprecated This API has been deprecated, use #Jabra_GetBatteryStatusV2
 * @brief Get battery status, if supported by device.
 * @param[in] deviceID          ID for a specific device
 * @param[out] levelInPercent   Battery level in percent (0 - 100)
 * @param[out] charging         Indicates if battery is being charged
 * @param[out] batteryLow       Indicates if battery level is low
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_BadState      Failed while reading from device
 * @return Not_Supported        Functionality is not supported on this device
 * @note Since dongle does not have battery, SDK returns Not_Supported when
 * battery status is requested for dongle device.
 * @see Jabra_RegisterBatteryStatusUpdateCallback
 * @sa @wrap{Jabra_GetBatteryStatus}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetBatteryStatus(unsigned short deviceID, int *levelInPercent, bool *charging, bool *batteryLow);

/**
 * @brief Get remote control battery status, if supported by device.
 * @param[in] deviceID          ID for a specific device
 * @param[out] levelInPercent   Battery level in percent (0 - 100)
 * @param[out] charging         Indicates if battery is being charged
 * @param[out] batteryLow       Indicates if battery level is low
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_BadState      Failed while reading from device
 * @return Not_Supported        Functionality is not supported on this device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetRemoteControlBatteryStatus(unsigned short deviceID, int* levelInPercent, bool* charging, bool* batteryLow);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_RegisterBatteryStatusUpdateCallback.
 */
typedef void(*BatteryStatusUpdateCallback)(unsigned short deviceID, int levelInPercent, bool charging, bool batteryLow);

/**
 * @brief Register for battery status update callback.
 * @param[in] callback      Callback method called when the battery status changes
 * @see Jabra_GetBatteryStatus
 * @note As memory is allocated through SDK, need to be freed by calling #Jabra_FreeBatteryStatus.
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_RegisterBatteryStatusUpdateCallbackV2(BatteryStatusUpdateCallbackV2 const callback);

/**
 * @deprecated This API has been deprecated, use #Jabra_RegisterBatteryStatusUpdateCallbackV2
 * @brief Register for battery status update callback.
 * @param[in] callback      Callback method called when the battery status change
 * @see Jabra_GetBatteryStatus
 */
LIBRARY_API void Jabra_RegisterBatteryStatusUpdateCallback(BatteryStatusUpdateCallback const callback);

/**
 * @deprecated This API has been deprecated.
 * @brief Get the warranty end date of the device
 * @param[in]       deviceID ID for a device
 * @return Pointer to string with warranty end date of the device.
 * If device is NOT in warranty, it returns NULL.
 * @note As memory is allocated through SDK for returned warranty end date,
 * needs to be freed by calling #Jabra_FreeString.
 */
LIBRARY_API char* Jabra_GetWarrantyEndDate(unsigned short deviceID);

/**
 * @brief Integrates softphone app to Jabra applications like Jabra Direct(JD)
 * and Jabra Suite for Mac(JMS).
 * @param[in] guid          Client unique ID
 * @param[in] softphoneName Name of the application to be shown in JD or JMS
 * @return true             Softphone app was integrated to Jabra application
 * @return false            It failed to integrate or is already connected
 * @see Jabra_DisconnectFromJabraApplication
 * @ingroup g-phone
 */
LIBRARY_API bool Jabra_ConnectToJabraApplication(const char* guid, const char* softphoneName);

/**
 * @brief Disconnects connected from Jabra applications.
 * @see Jabra_ConnectToJabraApplication
 * @ingroup g-phone
 */
LIBRARY_API void Jabra_DisconnectFromJabraApplication(void);

/**
 * @brief Sets the softphone to Ready. Currently applicable for only Jabra
 * Direct.
 * Will be available in later versions of JMS.
 * @param[in] isReady       Sets the softphone readiness state
 * @see Jabra_IsSoftphoneInFocus
 * @ingroup g-phone
 */
LIBRARY_API void Jabra_SetSoftphoneReady(bool isReady);

/**
 * @brief Indicates whether the softphone is in focus.
 * @return true         Softphone is in focus
 * @return false        Softphone is not in focus
 * @see Jabra_SetSoftphoneReady
 * @ingroup g-phone
 */
LIBRARY_API bool Jabra_IsSoftphoneInFocus(void);

/**
 * @brief Get error string from the error status.
 * @param[in] errStatus     Status of the error from the Jabra Device
 * @return Corresponding error text.
 * @ingroup g-sdk
 * @sa @wrap{Jabra_GetErrorString}
 */
LIBRARY_API const char* Jabra_GetErrorString(Jabra_ErrorStatus errStatus);

/**
 * @brief Get descriptive string from the return code.
 * @param[in] code      Return code to get description of
 * @return Corresponding text.
 * @ingroup g-sdk
 */
LIBRARY_API const char* Jabra_GetReturnCodeString(Jabra_ReturnCode code);

/**
 * @brief Get lock for a particular device.
 * @param[in] deviceID          ID for a device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_Lock          Lock was acquired by other process
 * @ingroup g-phone
 * @sa @wrap{Jabra_GetLock}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetLock(unsigned short deviceID);

/**
 * @brief Release the lock for a particular device.
 * @param[in] deviceID          ID for a device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_NotLock       Lock was acquired by other process
 * @ingroup g-phone
 * @sa @wrap{Jabra_ReleaseLock}
 */
LIBRARY_API Jabra_ReturnCode Jabra_ReleaseLock(unsigned short deviceID);

/**
 * @brief Check if we have lock on device.
 * @param[in] deviceID          ID for a device
 * @return true                 Device is locked
 * @return false                Device is not locked
 * @ingroup g-phone
 * @sa @wrap{Jabra_IsLocked}
 */
LIBRARY_API bool Jabra_IsLocked(unsigned short deviceID);

/**
 * @brief Checks if busylight is supported by the device.
 * @param[in] deviceID          ID for a device
 * @return true                 Busylight is supported
 * @return false                Busylight is not supported
 * @see Jabra_GetBusylightStatus
 * @see Jabra_SetBusylightStatus
 * @see Jabra_RegisterBusylightEvent
 * @ingroup g-indicators
 */
LIBRARY_API bool Jabra_IsBusylightSupported(unsigned short deviceID);

/**
 * @brief Checks the status of busylight.
 * @param[in] deviceID      ID for specific device
 * @return true             Busylight is on
 * @return false            Busylight is off or not supported
 * @see Jabra_IsBusylightSupported
 * @see Jabra_SetBusylightStatus
 * @see Jabra_RegisterBusylightEvent
 * @ingroup g-indicators
 */
LIBRARY_API bool Jabra_GetBusylightStatus(unsigned short deviceID);

/**
 * @brief Enable/Disable the busylight status.
 * @param[in] deviceID      ID for specific device
 * @param[in] value         Enable or disable busylight
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_IsBusylightSupported
 * @see Jabra_GetBusylightStatus
 * @see Jabra_RegisterBusylightEvent
 * @sa @wrap{Jabra_SetBusylightStatus}
 * @ingroup g-indicators
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetBusylightStatus(unsigned short deviceID, bool value);

/**
 * @brief Registration for busylight event.
 * @param[in] BusylightFunc Callback method, called when busylight event is
 * received from device. Can be NULL if not used.
 * @see Jabra_IsBusylightSupported
 * @see Jabra_GetBusylightStatus
 * @see Jabra_SetBusylightStatus
 * @ingroup g-events
 * @ingroup g-indicators
 */
LIBRARY_API void Jabra_RegisterBusylightEvent(void(*BusylightFunc)(unsigned short deviceID, bool busylightValue));

/**
 * @brief Checks if manual busylight is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Manual busylight is supported
 * @return false            Manual busylight is not supported
 * @see Jabra_GetManualBusylightStatus
 * @see Jabra_SetManualBusylightStatus
 * @see Jabra_RegisterManualBusylightEvent
 * @ingroup g-indicators
 */
LIBRARY_API bool Jabra_IsManualBusylightSupported(unsigned short deviceID);

/**
 * @brief Checks the status of busylight.
 * @param[in] deviceID      ID for specific device
 * @return true             Busylight is on
 * @return false            Busylight is off or not supported
 * @see Jabra_IsManualBusylightSupported
 * @see Jabra_SetManualBusylightStatus
 * @see Jabra_RegisterManualBusylightEvent
 * @ingroup g-indicators
 */
LIBRARY_API bool Jabra_GetManualBusylightStatus(unsigned short deviceID);

/**
 * @brief Change the manual busylight status.
 * @param[in] deviceID          ID for specific device
 * @param[in] value             New value for manual busylight
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_IsManualBusylightSupported
 * @see Jabra_GetManualBusylightStatus
 * @see Jabra_RegisterManualBusylightEvent
 * @ingroup g-indicators
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetManualBusylightStatus(unsigned short deviceID, BusyLightValue value);

/**
 * @brief Registration for busylight change event.
 * @param[in] deviceID      ID for specific device
 * @param[in] listener Callback method. Invoked when busylight change event
 *                     are received from the device. Set to NULL to
 *                     unregister.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_IsManualBusylightSupported
 * @see Jabra_GetManualBusylightStatus
 * @see Jabra_SetManualBusylightStatus
 * @ingroup g-events
 * @ingroup g-indicators
 */
LIBRARY_API Jabra_ReturnCode Jabra_RegisterManualBusylightEvent(unsigned short deviceID, BusylightChangeListener listener);

/**
 * @brief Is left earbud status supported.
 * @param[in] deviceID      ID for specific device
 * @return true             Left earbud supports connection status
 * @return false            Left earbud does not support connection status
 * @see Jabra_GetLeftEarbudStatus
 * @see Jabra_RegisterLeftEarbudStatus
 * @see Jabra_RegisterHearThroughSettingChangeHandler
 * @sa @wrap{Jabra_IsLeftEarbudStatusSupported}
 * @ingroup g-dev-status
 */
LIBRARY_API bool Jabra_IsLeftEarbudStatusSupported(unsigned short deviceID);

/**
 * @brief Get left earbud connection status.
 * @param[in] deviceID      ID for specific device
 * @return true             Left earbud is connected
 * @return false            Left earbud is not connected
 * @see Jabra_IsLeftEarbudStatusSupported
 * @see Jabra_RegisterLeftEarbudStatus
 * @see Jabra_RegisterHearThroughSettingChangeHandler
 * @sa @wrap{Jabra_GetLeftEarbudStatus}
 * @ingroup g-dev-status
 */
LIBRARY_API bool Jabra_GetLeftEarbudStatus(unsigned short deviceID);

/**
 * @brief Registration for left earbud connection status event. Can only be
 * called when a device is attached.
 * @param[in] deviceID          ID for specific device
 * @param[in] LeftEarbudFunc    Callback method, called when left earbud status
 * event is received from device. Can be NULL if not used
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_IsLeftEarbudStatusSupported
 * @see Jabra_GetLeftEarbudStatus
 * @see Jabra_RegisterHearThroughSettingChangeHandler
 * @sa @wrap{Jabra_RegisterLeftEarbudStatus}
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_RegisterLeftEarbudStatus(unsigned short deviceID, void(*LeftEarbudFunc)(unsigned short deviceID, bool connected));

/**
 * @brief Registration for HearThrough setting change event.
 * @param[in] HearThroughSettingChangeFunc Callback method, called when
 * HearThrough setting is changed on device. Can be NULL if not used.
 * @see Jabra_IsLeftEarbudStatusSupported
 * @see Jabra_GetLeftEarbudStatus
 * @see Jabra_RegisterLeftEarbudStatus
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_RegisterHearThroughSettingChangeHandler(void(*HearThroughSettingChangeFunc)(unsigned short deviceID, bool enabled));

/**
 * @brief Checks if equalizer is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Equalizer is supported
 * @return false            Equalizer is not supported
 * @see Jabra_IsEqualizerEnabled
 * @see Jabra_EnableEqualizer
 * @see Jabra_GetEqualizerParameters
 * @see Jabra_SetEqualizerParameters
 * @sa @wrap{Jabra_IsEqualizerSupported}
 * @ingroup g-equalizer
 */
LIBRARY_API bool Jabra_IsEqualizerSupported(unsigned short deviceID);

/**
 * @brief Checks if equalizer is enabled.
 * @param[in] deviceID      ID for specific device
 * @return true             Equalizer is enabled
 * @return false            Equalizer is disabled or not supported
 * @see Jabra_IsEqualizerSupported
 * @see Jabra_EnableEqualizer
 * @see Jabra_GetEqualizerParameters
 * @see Jabra_SetEqualizerParameters
 * @sa @wrap{Jabra_IsEqualizerEnabled}
 * @ingroup g-equalizer
*/
LIBRARY_API bool Jabra_IsEqualizerEnabled(unsigned short deviceID);

/**
 * @brief Enable/disable equalizer.
 * @param[in] deviceID          ID for specific device
 * @param[in] value             Enable or disable equalizer
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_IsEqualizerSupported
 * @see Jabra_IsEqualizerEnabled
 * @see Jabra_GetEqualizerParameters
 * @see Jabra_SetEqualizerParameters
 * @sa @wrap{Jabra_EnableEqualizer}
 * @ingroup g-equalizer
 */
LIBRARY_API Jabra_ReturnCode Jabra_EnableEqualizer(unsigned short deviceID, bool value);

/**
 * @brief Get equalizer parameters.
 * @param[in] deviceID      ID for specific device
 * @param[in,out] bands     Caller allocated / owned array for the parameters
 * Allocate at least the number of bands you expect the device to have (could vary, but 5 is a good bet).
*  On input: empty, on successful return: holds the equalizer parameters.
 * @param[in,out] nbands    in: The size of the bands array,
 * out (if successful): the actual number of bands. bands[0..*nbands-1] are then valid.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed or a buffer was too small
 * @see Jabra_IsEqualizerSupported
 * @see Jabra_IsEqualizerEnabled
 * @see Jabra_EnableEqualizer
 * @see Jabra_SetEqualizerParameters
 * @sa @wrap{Jabra_GetEqualizerParameters}
 * @ingroup g-equalizer
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetEqualizerParameters(unsigned short deviceID, Jabra_EqualizerBand * bands, unsigned int * nbands);

/**
 * @brief Set equalizer parameters.
 * @param[in] deviceID      ID for specific device
 * @param[in] bands         Caller-owned array containing the band gains to set in dB
 * (must be within range of +/- #Jabra_EqualizerBand.max_gain)
 * @param[in] nbands        Number of bands to set
 * Use the nbands value obtained from a successful call to Jabra_GetEqualizerParameters()
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return System_Error         Unable to communicate with device
 * @return Return_ParameterFail bands is NULL or buffer is too small
 * @return No_Information       Invalid response received from device
 * @see Jabra_IsEqualizerSupported
 * @see Jabra_IsEqualizerEnabled
 * @see Jabra_EnableEqualizer
 * @see Jabra_GetEqualizerParameters
 * @sa @wrap{Jabra_SetEqualizerParameters}
 * @ingroup g-equalizer
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetEqualizerParameters(unsigned short deviceID, float * bands, unsigned int nbands);

/**
 * @deprecated This API has been deprecated, use #Jabra_IsFeatureSupported with
 * parameter #DeviceFeature RemoteMMI instead.
 * @brief Checks if remote MMI feature is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Remote MMI feature is supported
 * @return false            Remote MMI feature is not supported
 */
LIBRARY_API bool Jabra_IsRemoteMMISupported(unsigned short deviceID);

/**
 * @brief Configures the remote MMI events for a device.
 * @param[in] deviceID          ID for specific device
 * @param[in] buttonEvent       Button events to be set in device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetButtonFocus(unsigned short deviceID, ButtonEvent *buttonEvent);

/**
 * @brief Releases the remote MMI events configured in the device.
 * @param[in] deviceID          ID for specific device
 * @param[in] buttonEvent       Button events to be released in device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_ReleaseButtonFocus(unsigned short deviceID, ButtonEvent *buttonEvent);

/**
 * @brief Gets the supported remote MMI for a device.
 * @param[in] deviceID      ID for specific device
 * @return Pointer to ButtonEvent struct containing all button events
 * for that device. In case of error, a NULL pointer is returned.
 * @ingroup g-remote-mmi
 */
LIBRARY_API ButtonEvent* Jabra_GetSupportedButtonEvents(unsigned short deviceID);

/**
 * @brief Free the memory allocated for the button events.
 * @param[in] eventsSupported Pointer to #ButtonEvent struct to be freed
 * @ingroup g-remote-mmi
 */
LIBRARY_API void Jabra_FreeButtonEvents(ButtonEvent *eventsSupported);

/**
 * @brief Registration for GNP button events i.e remote MMI.
 * @param[in] ButtonGNPEventFunc Callback method to receive GNP Button events
 * /remote MMI events. Can be NULL if not used.
 * @ingroup g-events
 * @ingroup g-remote-mmi
 */
LIBRARY_API void Jabra_RegisterForGNPButtonEvent(void(*ButtonGNPEventFunc)(unsigned short deviceID, ButtonEvent *buttonEvent));

/**
 * @brief Checks if setting protection is enabled.
 * @param[in] deviceID      ID for specific device
 * @return true if setting protection is enabled otherwise false.
 * @sa @wrap{Jabra_IsSettingProtectionEnabled}
 */
LIBRARY_API bool Jabra_IsSettingProtectionEnabled(unsigned short deviceID);

/**
 * @brief Get the URL for contacting Jabra customer support.
 * @param[in] deviceID      ID for specific device
 * @param[in] appName       Name of the application
 * @param[in] appVersion    Version of the application
 * @param[in] deviceBrand   Name of the phone vendor (e.g., "Apple"). May be empty or NULL
 * @param[in] deviceModel   Device model name (e.g. "IPhone 8"). May be empty or NULL
 * @return NPS URL or NULL pointer if it is not available. If no customer support is available this way for the device, NULL is returned.
 * @note As memory is allocated through SDK for the Url, it needs to be freed
 * by calling #Jabra_FreeString.
 * @ingroup g-dev-info
 */
LIBRARY_API char* Jabra_GetCustomerSupportUrl(unsigned short deviceID, const char* appName, const char* appVersion, const char* deviceBrand, const char* deviceModel );

/**
 * @brief Get the NPS URL for the application only.
 * @param[in] appName       Name of the application
 * @param[in] appVersion    Version of the application
 * @return NPS URL or NULL pointer if it is not available.
 * @note As memory is allocated through SDK for NPS Url, it needs to be freed
 * by calling #Jabra_FreeString.
 * @ingroup g-dev-info
 */
LIBRARY_API char* Jabra_GetNpsUrlForApplication(const char* appName, const char* appVersion);

/**
 * @brief Get the NPS URL.
 * @param[in] deviceID          ID for specific device
 * @param[in] appName           Name of the app
 * @param[in] appVersion        Version of the app
 * @return NPS URL or NULL pointer if it is not available.
 * @note As memory is allocated through SDK for NPS Url, it needs to be freed
 * by calling #Jabra_FreeString.
 * @sa @wrap{Jabra_GetNpsUrl}
 * @ingroup g-dev-info
 */
LIBRARY_API char* Jabra_GetNpsUrl(unsigned short deviceID, const char* appName, const char* appVersion);

/**
 * @brief Register a product.
 * @param[in] deviceID          ID of device from which settings needs to be updated
 * @param[in] prodReg           Product registration information
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return NetworkRequest_Fail  There was a network problem
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_ProductRegistration}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_ProductRegistration(unsigned short deviceID, const ProductRegInfo* prodReg);

/**
 * @brief Tells the device to execute a AVRCP command. This interface is only supported by iOS.
 * @param[in] deviceID          ID for specific device
 * @param[in] command           The command to execute
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_ExecuteAVRCPCommand(unsigned short deviceID, AVRCPCommand command);

/**
 * @brief To configure logging of device events.
 * @param[in] logFlag   Specifies the location of logs saved. Local logs are
 * saved only on local machine. Cloud logs are saved in cloud. All logs are
 * saved in both local and cloud.
 * @param[in] flag      Enable or disable logging for the specified location
 * @see Jabra_RegisterDevLogCallback
 * @see Jabra_EnableDevLog
 * @see Jabra_IsDevLogEnabled
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_ConfigureLogging(Jabra_Logging logFlag, bool flag);

/**
 * @deprecated This API has been deprecated, use #Jabra_RegisterDevLogCallback
 * instead to register callback for Logging.
 * @param[in] LogDeviceEvent Callback method, will be called when events
 * are received from the device.
 * eventStr: Is a Json message for the event to be logged of below format.
 *            {
 *                "AppID" : "",
 *                "Device Name" : "",
 *                "ESN" : "",
 *                "EventName" : "",
 *                "FW" : "",
 *                "LocalTimeStamp" : "",
 *                "Pid" : ,
 *                "Seq.No" : ,
 *                "Value" : "",
 *                "Variant" : ""
 *            }
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreeString.
 * @see Jabra_ConfigureLogging
 * @see Jabra_RegisterDevLogCallback
 * @see Jabra_EnableDevLog
 * @see Jabra_IsDevLogEnabled
 */
LIBRARY_API void Jabra_RegisterLoggingCallback(void(*LogDeviceEvent)(char* eventStr));

/**
 * @brief Registration for device logging events.
 * @param[in] LogDeviceEvent    Callback method, will be called when log events
 * are received from the device.
 * eventStr: Is a Json message for the event to be logged of below format.
 *            {
 *                "AppID" : "",
 *                "Device Name" : "",
 *                "ESN" : "",
 *                "EventName" : "",
 *                "FW" : "",
 *                "LocalTimeStamp" : "",
 *                "Pid" : ,
 *                "Seq.No" : ,
 *                "Value" : "",
 *                "Variant" : ""
 *            }
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreeString.
 * @see Jabra_ConfigureLogging
 * @see Jabra_EnableDevLog
 * @see Jabra_IsDevLogEnabled
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_RegisterDevLogCallback(void(*LogDeviceEvent)(unsigned short deviceID, char* eventStr));

/**
 * @brief Enable/disable logging for a device.
 * @param[in] deviceID      ID for specific device
 * @param[in] enable        true = enable logging in device, otherwise disable
 * eventStr Is a Json message for the event to be logged of below format.
 *          {
 *              "AppID" : "",
 *              "Device Name" : "",
 *              "ESN" : "",
 *              "EventName" : "",
 *              "FW" : "",
 *              "LocalTimeStamp" : "",
 *              "Pid" : ,
 *              "Seq.No" : ,
 *              "Value" : "",
 *              "Variant" : ""
 *          }
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_ConfigureLogging
 * @see Jabra_RegisterDevLogCallback
 * @see Jabra_IsDevLogEnabled
 * @sa @wrap{Jabra_EnableDevLog}
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_EnableDevLog(unsigned short deviceID, bool enable);

/**
 * @brief Is logging enabled on device.
 * @param[in] deviceID      ID for specific device
 * @return true             Logging is enabled
 * @return false            Logging is disabled
 * @see Jabra_ConfigureLogging
 * @see Jabra_RegisterDevLogCallback
 * @see Jabra_EnableDevLog
 * @sa @wrap{Jabra_IsDevLogEnabled}
 * @ingroup g-dev-status
 */
LIBRARY_API bool Jabra_IsDevLogEnabled(unsigned short deviceID);

/**
 * @brief Recreates the session, input and output streams for all devices which
 * are connected to the phone and not to the application.
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_Reconnect(void);

/**
 * @brief Check if a feature is supported by a device.
 * @param[in] deviceID      ID for specific device
 * @param[in] feature       The feature to check
 * @return true             Feature is supported
 * @return false            Feature is not supported
 * @see Jabra_GetSupportedFeatures
 * @see Jabra_FreeSupportedFeatures
 * @sa @wrap{Jabra_IsFeatureSupported}
 * @ingroup g-dev-status
 */
LIBRARY_API bool Jabra_IsFeatureSupported(unsigned short deviceID, DeviceFeature feature);

/**
 * @brief Get array of features supported by a device.
 * @param[in] deviceID      ID for specific device
 * @param[out] count Number of items in result.
 * @return Array of supported features, may be NULL. Shall be freed by calling
 * #Jabra_FreeSupportedFeatures.
 * @see Jabra_IsFeatureSupported
 * @see Jabra_FreeSupportedFeatures
 * @sa @wrap{Jabra_GetSupportedFeatures}
 * @ingroup g-dev-status
 */
LIBRARY_API const DeviceFeature* Jabra_GetSupportedFeatures(unsigned short deviceID, unsigned int* count);

/**
 * @brief Free a list of features obtained by calling
 * #Jabra_GetSupportedFeatures.
 * @param[in] features List to delete.
 * @see Jabra_GetSupportedFeatures
 * @see Jabra_FreeSupportedFeatures
 * @ingroup g-dev-status
 */
LIBRARY_API void Jabra_FreeSupportedFeatures(const DeviceFeature* features);

/**
 * @brief Request that the headset does not play its 'end of call' tone when
 * the SCO closes next time. Precondition SCO is open. No checks - best effort.
 * @param[in] deviceID      ID for specific device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_RequestNoHangupToneNextTime}
 * @ingroup g-phone
 */
LIBRARY_API Jabra_ReturnCode Jabra_RequestNoHangupToneNextTime(unsigned short deviceID);

/**
 * @brief Indicates whether the device is certified for Skype for Business.
 * @param[in] deviceID      ID for specific device
 * @return true             Device is certified for Skype for Business
 * @return false            Device is not certified for Skype for Business
 * @sa @wrap{Jabra_IsCertifiedForSkypeForBusiness}
 * @ingroup g-dev-info
 */
LIBRARY_API bool Jabra_IsCertifiedForSkypeForBusiness(unsigned short deviceID);

/**
 * @brief Free a char array.
 * @param[in] arrPtr Array to delete.
 * @ingroup g-sdk
 */
LIBRARY_API void Jabra_FreeCharArray(const char** arrPtr);

/**
 * @brief Checks if ringtone upload is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Upload ringtone is supported
 * @return false            Upload ringtone is not supported
 * @see Jabra_UploadRingtone
 * @see Jabra_UploadWavRingtone
 * @see Jabra_GetAudioFileParametersForUpload
 * @see Jabra_RegisterUploadProgress
 * @sa @wrap{Jabra_IsUploadRingtoneSupported}
 * @ingroup g-ringtone
 */
LIBRARY_API bool Jabra_IsUploadRingtoneSupported(unsigned short deviceID);

/**
 * @brief Upload ringtone to device. For Mac and Linux only (for Windows use
 * #Jabra_UploadWavRingtone).
 * @param[in] deviceID      ID for specific device
 * @param[in] fileName Audio file name to be uploaded. The format supported is
 * wav 16kHz in uncompressed format.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail fileName is NULL or audio file has wrong type
 * @return FileWrite_Fail       Could not write file
 * @return Upload_AlreadyInProgress Upload is currently ongoing
 * @return Not_Supported        Device does not support ringtone uploads
 * @see Jabra_IsUploadRingtoneSupported
 * @see Jabra_UploadWavRingtone
 * @see Jabra_GetAudioFileParametersForUpload
 * @see Jabra_RegisterUploadProgress
 * @ingroup g-ringtone
 */
LIBRARY_API Jabra_ReturnCode Jabra_UploadRingtone(unsigned short deviceID, const char* fileName);

/**
 * @brief Upload ringtone to device in wav format.
 * @param[in] deviceID      ID for specific device
 * @param[in] fileName Audio file name to be uploaded. The format supported can
 * be obtained from #Jabra_GetAudioFileParametersForUpload.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail fileName is NULL or audio file has wrong type
 * @return Upload_AlreadyInProgress Upload is currently ongoing
 * @return Not_Supported        Device does not support ringtone uploads
 * @see Jabra_IsUploadRingtoneSupported
 * @see Jabra_UploadRingtone
 * @see Jabra_GetAudioFileParametersForUpload
 * @see Jabra_RegisterUploadProgress
 * @ingroup g-ringtone
 * @sa @wrap{Jabra_UploadWavRingtone}
 */
LIBRARY_API Jabra_ReturnCode Jabra_UploadWavRingtone(unsigned short deviceID, const char* fileName);

/**
 * @brief Get details of audio file for uploading to device.
 * @param[in] deviceID      ID for specific device
 * @return #Jabra_AudioFileParams struct with details of audio file
 * @see Jabra_IsUploadRingtoneSupported
 * @see Jabra_UploadRingtone
 * @see Jabra_UploadWavRingtone
 * @see Jabra_RegisterUploadProgress
 * @ingroup g-ringtone
 * @sa @wrap{Jabra_GetAudioFileParametersForUpload}
 */
LIBRARY_API Jabra_AudioFileParams Jabra_GetAudioFileParametersForUpload(unsigned short deviceID);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_RegisterUploadProgress.
 */
typedef void(*UploadProgress)(unsigned short deviceID, Jabra_UploadEventStatus status, unsigned short percentage);

/**
 * @brief Registration for ringtone upload progress event.
 * @param[in] callback Callback method, called during the upload process.
 * @see Jabra_IsUploadRingtoneSupported
 * @see Jabra_IsUploadImageSupported
 * @see Jabra_UploadRingtone
 * @see Jabra_UploadImage
 * @ingroup g-events
 * @ingroup g-ringtone
 */
LIBRARY_API void Jabra_RegisterUploadProgress(UploadProgress const callback);

/**
 * @brief Checks if image upload is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Image upload supported
 * @return false            Image upload not supported
 * @see Jabra_RegisterUploadProgress
 * @see Jabra_UploadImage
 * @ingroup g-ringtone
 * @sa @wrap{Jabra_IsUploadImageSupported}
 */
LIBRARY_API bool Jabra_IsUploadImageSupported(unsigned short deviceID);

/**
 * @brief Upload image to device.
 * @param[in] deviceID      ID for specific device
 * @param[in] fileName Name of image file to be uploaded.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail fileName is NULL or wrong type
 * @return FileWrite_Fail       Could not write file
 * @return Upload_AlreadyInProgress Upload is currently ongoing
 * @return File_Not_Accessible  Unable to access source file
 * @return Not_Supported        Device does not support image uploads
 * @see Jabra_IsUploadImageSupported
 * @see Jabra_RegisterUploadProgress
 * @ingroup g-ringtone
 * @sa @wrap{Jabra_UploadImage}
 */
LIBRARY_API Jabra_ReturnCode Jabra_UploadImage(unsigned short deviceID, const char* fileName);

/**
 * @brief Sets the wizard mode (whether a full setup wizard, a limited setup
 * wizard or none will run on next power-on). Use #Jabra_IsFeatureSupported
 * to query feature support #DeviceFeature FullWizardMode or
 * LimitedWizardMode.
 * @param[in] deviceID      ID for specific device
 * @param[in] wizardMode Wizard mode to be set (one of WizardModes).
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail wizardMode is invalid
 * @see Jabra_IsFeatureSupported
 * @see Jabra_GetWizardMode
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_SetWizardMode}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetWizardMode(unsigned short deviceID, WizardModes wizardMode);

/**
 * @brief Reads the current wizard mode (whether a full setup wizard, a limited
 * setup wizard or none will run on next power-on). Use
 * #Jabra_IsFeatureSupported to query feature support
 * #DeviceFeature FullWizardMode or LimitedWizardMode.
 * @param[in] deviceID      ID for specific device
 * @param[out] wizardMode Current wizard mode (one of WizardModes).
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_IsFeatureSupported
 * @see Jabra_SetWizardMode
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_GetWizardMode}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetWizardMode(unsigned short deviceID, WizardModes* wizardMode);

/**
 * @brief Checks if date and time synchronization is supported by the device.
 * @param[in] deviceID      ID for specific device
 * @return true             Date and time synchronization is supported
 * @return false            Date and time synchronization is not supported
 * @see Jabra_SetDateTime
 * @ingroup g-dev-info
 * @sa @wrap{Jabra_IsSetDateTimeSupported}
 */
LIBRARY_API bool Jabra_IsSetDateTimeSupported(unsigned short deviceID);

/**
 * @brief Sets (synchronizes) the date and time in the device.
 * @param[in] deviceID      ID for specific device
 * @param[in] dateTime Date and time to set. If this parameter is set to NULL
 * the date and time is set to the current time of the platform.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail Invalid value(s) found in dateTime
 * @see Jabra_IsSetDateTimeSupported
 * @sa @wrap{Jabra_SetDateTime}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetDateTime(unsigned short deviceID, const timedate_t* const dateTime);

/**
 * @brief Gets the UTC date and time from the device.
 * @param[in] deviceID      ID for specific device
 * @param[out] dateTime Pointer to struct which will receive the result.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @see Jabra_SetDateTime
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetDateTime(unsigned short deviceID, timedate_t* const dateTime);

/**
 * @brief Request info on supported device events.
 * @param[in] deviceID      ID for specific device
 * @return event mask (0 if nothing supported, or on any error).
 * @see Jabra_SetSubscribedDeviceEvents
 * @sa @wrap{Jabra_GetSupportedDeviceEvents}
 * @deprecated
 */
LIBRARY_API uint32_t Jabra_GetSupportedDeviceEvents(unsigned short deviceID);

/**
 * @brief Set device events to subscribe to. Event callbacks are received
 * through the event listener mechanism for each platform.
 * @param[in] deviceID      ID for specific device
 * @param[in] eventMask The bitmask representing supported device events
 * (one of DEVICE_EVENTS_* ) 0 = none
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_GetSupportedDeviceEvents
 * @deprecated
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSubscribedDeviceEvents(unsigned short deviceID, uint32_t eventMask);

/**
 * @brief Gets a list of supported remote MMIs.
 * @param[in] deviceID      ID for specific device
 * @param[in,out] types Pointer to allocated memory area containing count of
 * structures of #RemoteMmiDefinition. The memory area must be freed by calling
 * #Jabra_FreeRemoteMmiTypes.
 * @param[out] count Number of items passed via types.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed or buffer is too small
 * @return Not_Supported        Functionality is not supported on this device
 * @note RemoteMMIv2 only.
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetRemoteMmiTypes(unsigned short deviceID, RemoteMmiDefinition** const types, int* count);

/**
 * @brief Frees the memory area allocated by #Jabra_GetRemoteMmiTypes.
 * @param[in] types Pointer to the memory area to free.
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
*/
LIBRARY_API void Jabra_FreeRemoteMmiTypes(RemoteMmiDefinition* types);

/**
 * @brief Gets the status of the remote MMI focus.
 * @param[in] deviceID      ID for specific device
 * @param[in] type Type of remote MMI to get focus status of.
 * @param[out] isInFocus true if in focus, false if not.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed or type is invalid
 * @return Not_Supported        Functionality is not supported on this device
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_IsRemoteMmiInFocus(unsigned short deviceID, RemoteMmiType type, bool* isInFocus);

/**
 * @brief Gets the focus of the remote MMI specified. Once a remote MMI has
 * focus, the normal functionality of the MMI (button/LED) is suppressed until
 * Jabra_ReleaseRemoteMmiFocus or Jabra_ReleaseRemoteMmiFocusAll is called.
 * If only the LED output MMI functionality is required, action can be
 * specified as MMI_ACTION_NONE.
 * @param[in] deviceID      ID for specific device
 * @param[in] type Type of remote MMI to get focus of.
 * @param[in] action Action to get focus of, acts as a filter/mask for the
 * actions on the RemoteMmiCallback callback. Note that several actions can be
 * OR'ed together e.g. (RemoteMmiInput)(MMI_ACTION_TAP | MMI_ACTION_DOWN).
 * @param[in] priority Priority of focus.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetRemoteMmiFocus(unsigned short deviceID, RemoteMmiType type, RemoteMmiInput action, RemoteMmiPriority priority);

/**
 * @brief Releases the focus of the remote MMI specified. Note that focus on
 * all actions are removed.
 * @param[in] deviceID      ID for specific device
 * @param[in] type Type of remote MMI to release focus of.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_ReleaseRemoteMmiFocus(unsigned short deviceID, RemoteMmiType type);

/**
 * @brief Sets an output action on the remote MMI. Note that
 * #Jabra_GetRemoteMmiFocus must be called once for the RemoteMmiType in
 * question prior to setting the output action, else Return_ParameterFail is
 * returned.
 * @param[in] deviceID      ID for specific device
 * @param[in] type Type of remote MMI to set action of.
 * @param[in] outputAction Output LED action to set.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device e.g. if
 * #Jabra_GetRemoteMmiFocus has not called prior to calling.
 * #Jabra_SetRemoteMmiAction.
 * @return Return_ParameterFail An incorrect/unsupported parameter has been
 * passed or #Jabra_GetRemoteMmiFocus has not been called for the
 * #RemoteMmiType in question.
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_RegisterRemoteMmiCallback
 * @ingroup g-remote-mmi
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetRemoteMmiAction(unsigned short deviceID, RemoteMmiType type, RemoteMmiActionOutput outputAction);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_RegisterRemoteMmiCallback.
 * @note RemoteMMIv2 only.
 */
typedef void(*RemoteMmiCallback)(unsigned short deviceID, RemoteMmiType type, RemoteMmiInput action);

/**
 * @brief Register for remote MMI event callback.
 * @param[in] callback RemoteMmiCallback callback method, called when a remote
 * MMI input event is generated.
 * @note RemoteMMIv2 only.
 * @see Jabra_GetRemoteMmiTypes
 * @see Jabra_FreeRemoteMmiTypes
 * @see Jabra_IsRemoteMmiInFocus
 * @see Jabra_GetRemoteMmiFocus
 * @see Jabra_ReleaseRemoteMmiFocus
 * @see Jabra_SetRemoteMmiAction
 * @ingroup g-events
 * @ingroup g-remote-mmi
 */
LIBRARY_API void Jabra_RegisterRemoteMmiCallback(RemoteMmiCallback const callback);

/**
 * @brief Get the panic list.
 * @param[in] deviceID      ID for specific device
 * @return Pointer to panic list or NULL if not available.
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreePanicListType.
 * @see Jabra_FreePanicListType
 * @sa @wrap{Jabra_GetPanics}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_PanicListType* Jabra_GetPanics(unsigned short deviceID);

/**
 * @brief Frees the #Jabra_PanicListType struct.
 * @param[in] panicList #Jabra_PanicListType struct to be freed.
 * @see Jabra_GetPanics
 * @ingroup g-dev-info
 */
LIBRARY_API void Jabra_FreePanicListType(Jabra_PanicListType *panicList);

/**
 * @brief Sets a static timestamp in the device. Can be used for later
 * referencing using #Jabra_GetTimestamp.
 * @param[in] deviceID      ID for specific device
 * @param[in] newTime Timestamp to be set. Unix epoch.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_GetTimestamp
 * @sa @wrap{Jabra_SetTimestamp}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetTimestamp(unsigned short deviceID, const uint32_t newTime);

/**
 * @brief Gets the static timestamp in the device.
 * @param[in] deviceID      ID for specific device
 * @param[out] result Timestamp from device. Unix epoch.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @see Jabra_SetTimestamp
 * @sa @wrap{Jabra_GetTimestamp}
 * @ingroup g-dev-info
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetTimestamp(unsigned short deviceID, uint32_t* const result);

/**
 * @brief Preloads the resources with the content of the specified archive.
 * The content preloaded will take effect in the next attach device event.
 * To get the full benefit, this should happen before calling
 * #Jabra_Initialize, as that enables device connections and may initiate
 * background updates of device data. No existing data will be overwritten.
 * @param[in] zipFileName Full path name of the ZIP archive to preload from.
 * @return true if preloading succeeds, false otherwise.
 */
LIBRARY_API bool Jabra_PreloadDeviceInfo(const char* zipFileName);

/**
 * @brief Preloads the resources with the contents of the specified archive for
 * a specific connected device. Will always overwrite existing resources.
 * @param[in] deviceID           ID of specific device
 * @param[in] zipFileName        Full path name of the ZIP archive which contains the resources
 * @return Return_Ok             Call was successful
 * @return Device_Unknown        deviceID is unknown
 * @return Return_ParameterFail  The zipFileName parameter is incorrect or the
 *                               resources were not loaded correctly
 * @return No_Information        The resources are empty
 */
LIBRARY_API Jabra_ReturnCode Jabra_PreloadAttachedDeviceInfo(unsigned short deviceID, const char* zipFileName);

/**
 * @brief Gets the Manifest Files' version that are locally
 * in the Resources folder regarding a given device.
 * @param[in] deviceID      ID for specific device
 * @return returns a string with the value "0.0" if there is no Manifest Files locally
 * or a string with a higher version if there is, or null if any errors occur in the process.
 */
LIBRARY_API char* Jabra_GetLocalManifestVersion(unsigned short deviceID);

/**
 * @brief Play ringtone in device.
 * @param[in] deviceID      ID for specific device
 * @param[in] level Level to Play.
 * @param[in] type Type of ringtone to Play.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * parameters are wrong.
 * @ingroup g-phone
 * @sa @wrap{Jabra_PlayRingtone}
 */
LIBRARY_API Jabra_ReturnCode Jabra_PlayRingtone(unsigned short deviceID, const uint8_t level, const uint8_t type);

/**
 * @brief Subscribe/unsubscribe to JackStatus events. Not available on all devices. If not available, the client will get no events.
 * @param[in] deviceID      ID for specific device
 * @param[in] listener The callback for JackStatus events. Set to NULL to unsubscribe. Callback will occur on a separate thread.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetJackConnectorStatusListener(unsigned short deviceID, JackConnectorStatusListener listener);

/**
 * @brief Subscribe/unsubscribe to HeadDetectionStatus events. Not available on all devices. If not available, the client will get no events.
 * @param[in] deviceID      ID for specific device
 * @param[in] listener The callback for HeadDetectionStatus events. Set to NULL to unsubscribe. Callback will occur on a separate thread.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device or an error occured while communicating with device
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetHeadDetectionStatusListener(unsigned short deviceID, HeadDetectionStatusListener listener);

/**
 * @brief Subscribe/unsubscribe to LinkConnectionStatus events. Not available on all devices. If not available, the client will get no events.
 * @param[in] deviceID      ID for specific device
 * @param[in] listener The callback for LinkConnectiontatus events. Set to NULL to unsubscribe. Callback will occur on a separate thread.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device or an error occured while communicating with device
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetLinkConnectionStatusListener(unsigned short deviceID, LinkConnectionStatusListener listener);

/**
 * @brief Reboot the device.
 * @param[in] deviceID      ID for specific device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_RebootDevice(unsigned short deviceID);

/** Dect information about density and error counts */

/** It is possible to calculate a “percentage density” like this:
 *   (100 * MaximumReferenceRSSI * NumberMeasuredSlots) / SumMeasuredRSSI. If this percentage number is high,
 *    and there is a large number of errors, then the problem is most likely too high density.
 */

typedef struct _DectInfoDensity
{
    uint16_t SumMeasuredRSSI;       /* This is the sum of RSSI measured for all slots. */
    uint8_t  MaximumReferenceRSSI;  /* This is the maximum RSSI expected to be measured from 1 slot. */
    uint8_t  NumberMeasuredSlots;   /* Number of slots measured in current communication mode. */
    uint16_t DataAgeSeconds;        /* Time since measurement was taken. */
} Jabra_DectInfoDensity;

/** The most interesting counter is the handoversCount, which states how many times the connection has
 *  moved to a different slot position. Moving doesn’t necessarily give any effect on the audio, but there is a risk that it is hearable.
 *  When you reach a level of 5 or above in multiple consecutive readings it will definitely be noticeable.
 *  The other counters describe what is the reason the a handover has occurred, there may be multiple errors resulting in a single handover.
 */
typedef struct _DectInfoErrorCount
{
    uint16_t syncErrors;        /* Number of errors in SYNC field.*/
    uint16_t aErrors;           /* Number of errors in A field.*/
    uint16_t xErrors;           /* Number of errors in X field.*/
    uint16_t zErrors;           /* Number of errors in Z field.*/
    uint16_t hubSyncErrors;     /* Number of errors in HUB Sync field.*/
    uint16_t hubAErrors;        /* Number of errors in HUB A field.*/
    uint16_t handoversCount;    /* Handover count.*/
} Jabra_DectErrorCount;

typedef enum _DectInfoType
{
    DectDensity = 0x00,
    DectErrorCount = 0x01,
} Jabra_DectInfoType;

typedef struct _DectInfo
{
    Jabra_DectInfoType DectType;
    union {
        Jabra_DectInfoDensity DectDensity;
        Jabra_DectErrorCount  DectErrorCount;
    };
    unsigned int RawDataLen;
    uint8_t RawData[57];
} Jabra_DectInfo;

/**
 * @brief Registration for dect density and error count events.
 * @param[in] DectInfoFunc Callback method, called when
 * a dect device sends a dect density or dect error count event
 * The #Jabra_DectInfo struct must be freed using #Jabra_FreeDectInfoStr
 * @ingroup g-events
 */
LIBRARY_API void Jabra_RegisterDectInfoHandler(void(*DectInfoFunc)(unsigned short deviceID, Jabra_DectInfo *dectInfo));

/**
 * @brief Frees the #Jabra_DectInfo
 * @param[in] dectInfo      #Jabra_DectInfo struct to be freed
 */
LIBRARY_API void Jabra_FreeDectInfoStr(Jabra_DectInfo *dectInfo);

/**
 * @brief Headset selection for DECT pairing
 */
typedef enum _DectHeadset { PRIMARY_HS, SECONDARY_HS } DectHeadset;

/**
 * @brief Start DECT pairing
 * Start insecure pairing mode, equivalent to pushing the pair button on the DECT base.
 * When using this method, the headset will connect to any base in pairing mode. It is
 * recommended to use the secure version Jabra_DectPairSecure.
 * @param deviceID              ID for the specific device
 * @param[in] headset           Role of paired headset (primary/secondary)
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_DectPairSecure
 * @ingroup g-pairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_DectPair(unsigned short deviceID, DectHeadset headset);

/**
 * @brief Start DECT secure pairing using USB connected headset
 * Prior to starting the secure pairing, it is required to call Jabra_GetDectPairKey on the
 * dongle to get a pairing key and then use Jabra_SetDectPairKey to set the pairing key in
 * the USB connected headset.
 * @param deviceID              ID for the specific device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_GetDectPairKey
 * @see Jabra_SetDectPairKey
 * @ingroup g-pairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_DectPairSecure(unsigned short deviceID);

/**
 * @brief Read the secure pairing key from a DECT base/dongle.
 * @param deviceID              ID for the specific device
 * @param[out] acCode           Pairing key
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_DectPairSecure
 * @see Jabra_SetDectPairKey
 * @ingroup g-pairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetDectPairKey(unsigned short deviceID, uint32_t* acCode);

/**
 * @brief Write the secure DECT pairing key to a USB connected headset.
 * @param deviceID              ID for the specific device
 * @param[in] acCode            Pairing key
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_DectPairSecure
 * @see Jabra_GetDectPairKey
 * @ingroup g-pairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetDectPairKey(unsigned short deviceID, uint32_t  acCode);

/**
 * @brief Reads the device name(s) of connected BT or DECT headsets. If a requested name returns NULL, it means it was not possible to read from that device.
 * @param deviceID              ID for the specific device
 * @param[in]  deviceMask       Bitmask indicating which paired headsets to read: bit 0=primary (DECT/BT), bit 1=1st sec. (DECT), bit 2=2nd sec. (DECT), bit 3=3rd sec. (DECT)
 * @param[in]  getAssetTag      If true, reads user-configurable device asset tag. If false, reads product name.
 * @param[out] priName          Pointer to name of primary DECT or BT headset
 * @param[out] sec1Name         Pointer to name of 1st secondary headset
 * @param[out] sec2Name         Pointer to name of 2nd secondary headset
 * @param[out] sec3Name         Pointer to name of 3rd secondary headset
 * @note As memory is allocated through SDK, any returned non-NULL pointer needs to be freed by calling
 * #Jabra_FreeString. This also applies for return codes other than Return_Ok.
 * @return Return_Ok            Call was successful - all requested names were read
 * @return Device_Unknown       deviceID is unknown
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail No names were requested or a NULL pointer was passed for a requested value
 * @return Not_Supported        Unable to read requested names - one or more names may still be returned, so check returned pointers
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetConnectedHeadsetNames(unsigned short deviceID, unsigned int deviceMask, bool getAssetTag, char** priName, char** sec1Name, char** sec2Name, char** sec3Name);

/**
 * @brief Gets the user-defined device name.
 * @param deviceID ID for the specific device
 * @param[out] deviceName Pointer to device name if it exists in device, otherwise unchanged
 * @note As memory is allocated through SDK, any returned non-NULL pointer needs to be freed by calling
 * #Jabra_FreeString.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @return Not_Supported        Unable to read requested name
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetUserDefinedDeviceName(unsigned short deviceID, char** deviceName);

/**
 * @brief To get a list of panic codes from the device.
 * @note It is primarily for mobile/consumer products.
 * @param deviceID ID for the specific device
 * @param[in,out] codes A #Jabra_PanicCodes struct containing an array of panic codes and size of the array
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPanicCodes(unsigned short deviceID, Jabra_PanicCodes *codes);

/**
 * @brief To clear the panic codes on the device
 * @param deviceID ID for the specific device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_ClearPanicCodes(unsigned short deviceID);

typedef enum _SubDeviceID
{
    SUBDEVICE_BASE = 0,             // Primary base or controller, e.g. Link 380 dongle
    SUBDEVICE_BASE_2,               // 2nd base or controller
    SUBDEVICE_DESKSTAND,            // Basic desk stand
    SUBDEVICE_CRADLE,               // Headset cradle, e.g. Engage 65 base
    SUBDEVICE_PRIMARY_HEADSET,      // BT or DECT headset connected through base/dongle
    SUBDEVICE_SECONDARY_HEADSET,    // 1st DECT conference headset
    SUBDEVICE_SECONDARY_2_HEADSET,  // 2nd DECT conference headset
    SUBDEVICE_SECONDARY_3_HEADSET,  // 3rd DECT conference headset
    SUBDEVICE_DOCKED_HEADSET,       // Headset when docked in cradle
    SUBDEVICE_USB_HEADSET,          // Also applies to BT headsets when using a cabled connection
    SUBDEVICE_HUB,
    SUBDEVICE_BLE_DEVICE,           // First BLE device
    SUBDEVICE_BLE_2_DEVICE          // Second BLE device, e.g. PanaCast 50 remote control
} SubDeviceID;

typedef enum _DeviceProperty
{
    DEVPROPERTY_NAME_DEVICE = 0,        // Device name
    DEVPROPERTY_NAME_USB,               // USB device name, may be different from device name
    DEVPROPERTY_NAME_BLUETOOTH,         // BT device name, may be different from device name
    DEVPROPERTY_NAME_CONNECTED_HEADSET, // Name of headset connected to this device
    DEVPROPERTY_ASSET_TAG,              // User-defined device name
    DEVPROPERTY_PID,                    // Product ID (returned in decimal representation)
    DEVPROPERTY_PID_DFU,                // Product ID when in device firmware update mode
    DEVPROPERTY_FWVERSION,              // Firmware version
    DEVPROPERTY_ESN                     // Serial number
} DeviceProperty;

/**
 * @brief Gets a specific property from the device or a sub device (i.e. a connected headset)
 * @note It is primarily usable for reading the properties of individual sub devices when they are only
 * presented as compound devices in the SDK, for example DECT cradles+headsets which will appear as a
 * single device.
 * It can also be used for reading properties of the PanaCast 50 remote control.
 * Specifiying SUBDEVICE_PRIMARY_HEADSET will provice the same results when used directly
 * with a BT dongle or the connected headset device.
 * @param[in] deviceID ID for the specific device
 * @param[in] subdevice The sub device to access
 * @param[in] property The property to read
 * @param[out] value Pointer to property if it exists, NULL otherwise
 * @note As memory is allocated through SDK, any returned non-NULL pointer needs to be freed by calling
 * #Jabra_FreeString.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Not_Supported        Unable to read requested value
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSubDeviceProperty(unsigned short deviceID, SubDeviceID subdevice, DeviceProperty property, char** value);

#include "Interface_AmbienceModes.h"
#include "Interface_Bluetooth.h"
#include "Interface_Constants.h"
#include "Interface_Firmware.h"
#include "Interface_Network.h"
#include "Interface_Video.h"
#include "Interface_Whiteboard.h"

#endif /* COMMON_H */
