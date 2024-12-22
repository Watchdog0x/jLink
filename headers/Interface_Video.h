#ifndef INTERFACE_VIDEO_H
#define INTERFACE_VIDEO_H

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
 * @file Interface_Video.h
 * @brief Defines the video interfaces for the Jabra SDK.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "Common.h"

/**
 * @brief       For a video device sets the current pan and tilt positions in arc second units.
 * @param[in]   deviceID ID for the specific device
 * @param[in]   pan the pan in the range [-180*3600; +180*3600].
 * @param[in]   tilt the tilt in the range [-180*3600; +180*3600].
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 *
 * pan and tilt are given in arc seconds.  1 arc second is 1/3600 of a degree,
 * so values will range from -648000(-180*3600) to 648000(180*3600). Positive
 * values are clockwise from the origin.
 * @sa @wrap{Jabra_SetPanTilt}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetPanTilt(unsigned short deviceID, int32_t pan, int32_t tilt);

/**
 * @brief       For a video device gets the current pan and tilt positions.
 * @param[in]   deviceID ID for the specific device
 * @param[out]  pan pointer to an int32_t that will be filled with the current pan value.
 * @param[out]  tilt pointer to an int32_t that will be filled with the current tilt value.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 *
 * pan and tilt are given in degrees. Positive values are clockwise from the
 * origin.
 *
 * @sa @wrap{Jabra_GetPanTilt}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPanTilt(unsigned short deviceID, int32_t* pan, int32_t* tilt);

/**
 * This struct represents a device camera's pan or tilt limits.
 */
typedef struct _PanTiltLimits
{
    /** @brief The minimum value the pan or tilt level can be set to. */
    int32_t min;
    /** @brief The maximum value the pan or tilt level can be set to. */
    int32_t max;
    /** @brief The minimum amount that the value needs to change for it to have any effect. */
    uint16_t stepSize;
} Jabra_PanTiltLimits;

/**
 * @brief       For a video device gets the pan and tilt limits
 * @param[in]   deviceID ID for the specific device
 * @param[out]  pan the pan limits for the device
 * @param[out]  tilt the tilt limits for the device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 *
 * @sa @wrap{Jabra_GetPanTiltLimits}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPanTiltLimits(unsigned short deviceID, Jabra_PanTiltLimits* pan, Jabra_PanTiltLimits* tilt);

/**
 * This struct is used to specify the relative pan/tilt action of the camera lens.
 */
typedef enum _enumPanDirection { panStop = 0, panClockWise = 1, panCounterClockwise = 0xFF } enumPanDirection;
typedef enum _enumTiltDirection { tiltStop = 0, tiltUp = 1, tiltDown = 0xFF } enumTiltDirection;
typedef struct _PanTiltRelative
{
    enumPanDirection PanDirection;
    uint8_t PanSpeed;               // Currently only a speed of 1 is supported
    enumTiltDirection TiltDirection;
    uint8_t TiltSpeed;              // Currently only a speed of 1 is supported
} Jabra_PanTiltRelative;

/**
 * This struct is used to specify the relative zoom action of the camera lens.
 */
typedef enum _enumZoomDirection { zoomStop = 0, zoomTelephoto = 1, zoomWideAngle = 0xFF } enumZoomDirection;
typedef struct _ZoomRelative
{
    enumZoomDirection ZoomDirection;
    uint8_t ZoomSpeed;              // Currently only a speed of 1 is supported
} Jabra_ZoomRelative;

/**
 * @brief       For a video device, starts or stops the relative pan/tilt action of the camera lens.
 * @param[in]   deviceID ID for the specific device
 * @param[in]   action Controls the direction of the pan/tilt action or if it should be stopped.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 *
 * This action is the same as what is used by the remote control. Button down will start the action,
 * and button up stops the action. Note that after starting the action, it will continue until a stop
 * command is sent (or the lens reaches the limit).
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetPanTiltRelativeAction(unsigned short deviceID, Jabra_PanTiltRelative action);

/**
 * @brief       For a video device, starts or stops the relative zoom action of the camera lens.
 * @param[in]   deviceID ID for the specific device
 * @param[in]   action Controls the direction of the zoom action or if it should be stopped.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 *
 * This action is the same as what is used by the remote control. Button down will start the action,
 * and button up stops the action. Note that after starting the action, it will continue until a stop
 * command is sent (or the lens reaches the limit).
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetZoomRelativeAction(unsigned short deviceID, Jabra_ZoomRelative action);

/**
 * @brief       For a video device, sets the zoom level.
 * @param[in]   deviceID ID for the specific device
 * @param[out]  zoomLevel Zoom level (objective lens focal length).
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetZoom }
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetZoom(unsigned short deviceID, uint16_t zoomLevel);

/**
 * @brief       For a video device, gets the zoom level.
 * @param[in]   deviceID ID for the specific device
 * @param[out]  zoomLevel  Pointer to a uint16_t that will be filled with the zoom
 *                         level (objective lens focal length).
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @sa @wrap{Jabra_GetZoom}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetZoom(unsigned short deviceID, uint16_t* zoomLevel);

/**
 * This struct represent a device camera's zoom limits.
 */
typedef struct _ZoomLimits
{
    /** @brief The minimum value the zoom level can be set to. */
    uint16_t min;
    /** @brief The maximum value the zoom level can be set to. */
    uint16_t max;
    /** @brief The minimum amount that the value needs to change for it to have any effect. */
    uint16_t stepSize;
} Jabra_ZoomLimits;

/**
 * @brief       For a video device, gets the zoom limit values.
 * @param[in]   deviceID    ID for the specific device
 * @param[out]  limits      The zoom limits for the device.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @sa @wrap{Jabra_GetZoomLimits}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetZoomLimits(unsigned short deviceID, Jabra_ZoomLimits* limits);

/**
 * @brief       Controls how often the camera is allowed to change speaker focus.
 * @param[in]   deviceID        ID for the specific device
 * @param[in]   latency         The minimum time in seconds to stay with a participant before being
 *                              allowed to change zoom/direction. Valid range: 0-30 seconds.
 *                              Typical value is ~3 seconds.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_GetIntelligentZoomLatency
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetIntelligentZoomLatency(unsigned short deviceID, int latency);

/**
 * @brief       Gets how often the camera is allowed to change speaker focus.
 * @param[in]   deviceID        ID for the specific device
 * @param[out]  latency         The minimum time in seconds to stay with a participant before being
 *                              allowed to change zoom/direction.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @see Jabra_SetIntelligentZoomLatency
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetIntelligentZoomLatency(unsigned short deviceID, int* latency);

/**
 * @brief       Switches to the next intelligent zoom mode
 * @param[in]   deviceID        ID for the specific device
 * @return Return_Ok            Call was successful
 * @return Not_Supported        Video functionality is not supported on this device
 * @return Device_Unknown       deviceID is unknown
 */
LIBRARY_API Jabra_ReturnCode Jabra_NextIntelligentZoomMode(unsigned short deviceID);

typedef enum _SecondaryStreamContent
{
    Disabled = 0,
    Whiteboard1 = 1,
    Whiteboard2 = 2,
    AIFullscreen = 3
} SecondaryStreamContent;

/**
 * @brief       For a video device, controls what is shown on the secondary video stream.
 * @param[in]   deviceID        ID for the specific device
 * @param[in]   content         What to display on the content stream
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_GetSecondVideoStream
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSecondVideoStream(unsigned short deviceID, SecondaryStreamContent content);

/**
 * @brief       For a video device, gets what is shown on the secondary video stream.
 * @param[in]   deviceID        ID for the specific device
 * @param[out]  content         Pointer to SecondaryStreamContent that receives the current setting
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @see Jabra_SetSecondVideoStream
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSecondVideoStream(unsigned short deviceID, SecondaryStreamContent* content);

/**
 * @brief       For a video device, enables or disables the default HDR mode.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   enable true = HDR enabled, false = HDR disabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetVideoHDRDefault(unsigned short deviceID, bool enable);

/**
 * @brief       For a video device, gets the default HDR enable state.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  enable true = HDR enabled, false = HDR disabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetVideoHDRDefault(unsigned short deviceID, bool* enable);

/**
 * @brief       For a video device, enables or disables the active HDR mode.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   enable true = HDR enabled, false = HDR disabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetVideoHDR(unsigned short deviceID, bool enable);

/**
 * @brief       For a video device, gets the active HDR enable state.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  enable true = HDR enabled, false = HDR disabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetVideoHDR(unsigned short deviceID, bool* enable);

/**
 * @brief       For a video device, resets the video controls like when a new call is started.
 * @param[in]   deviceID ID for the specific device.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_RestoreVideoRoomDefaults(unsigned short deviceID);

/**
 * @brief       Choices for automatic white balance.
 * @sa @wrap{Jabra_AutoWhiteBalance}
 */
typedef enum _Jabra_AutoWhiteBalance
{
    USE_WB_TEMP_VALUE = 0,        /*< @brief Use manual WB setting */
    AUTO_ADJUSTMENT = 1           /*< @brief Automatic white balance */
} Jabra_AutoWhiteBalance;

/**
 * @brief       For a video device, sets the contrast level.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   contrast Contrast level: 0=softest, 191=hardest.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail Contrast value is invalid
 * @sa @wrap{Jabra_SetContrastLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetContrastLevel(unsigned short deviceID, int contrast);

/**
 * @brief       For a video device, sets the sharpness level.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   sharpness Sharpness level: 0=least sharp, 255=sharpest.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail Sharpness value is invalid
 * @sa @wrap{Jabra_SetSharpnessLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSharpnessLevel(unsigned short deviceID, int sharpness);

/**
 * @brief       For a video device, sets the brightness level.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   brightness Brightness level: 0=darkest, 255=brightest.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail Brightness value is invalid
 * @sa @wrap{Jabra_SetBrightnessLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetBrightnessLevel(unsigned short deviceID, int brightness);

/**
 * @brief       For a video device, sets the saturation level.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   saturation Saturation level: 128=least saturated, 176=most saturated.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail Saturation value is invalid
 * @sa @wrap{Jabra_SetSaturationLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSaturationLevel(unsigned short deviceID, int saturation);

/**
 * @brief       For a video device, sets the white balance.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   whiteBalance White balance [K]: 0 (red) - 6500 (blue).
 * @param[in]   autoWB Use automatic or manual white balance.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return Return_ParameterFail White balance is invalid
 * @sa @wrap{Jabra_SetWhiteBalance}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetWhiteBalance(unsigned short deviceID, int whiteBalance, Jabra_AutoWhiteBalance autoWB);

/**
 * @brief       For a video device, gets the contrast level.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  contrast Pointer to int that will receive the contrast level setting.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetContrastLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetContrastLevel(unsigned short deviceID, int* contrast);

/**
 * @brief       For a video device, gets the sharpness level.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  sharpness Pointer to int that will receive the sharpness level setting.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetSharpnessLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSharpnessLevel(unsigned short deviceID, int* sharpness);

/**
 * @brief       For a video device, gets the brightness level.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  brightness Pointer to int that will receive the brightness level setting.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetBrightnessLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetBrightnessLevel(unsigned short deviceID, int* brightness);

/**
 * @brief       For a video device, gets the saturation level.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  saturation Pointer to int that will receive the saturation level setting.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetSaturationLevel}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSaturationLevel(unsigned short deviceID, int* saturation);

/**
 * @brief       For a video device, gets the white balance.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  whiteBalance Pointer to int that will receive the white balance setting.
 * @param[out]  autoWB Use automatic or manual white balance.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @sa @wrap{Jabra_GetWhiteBalance}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetWhiteBalance(unsigned short deviceID, int* whiteBalance, Jabra_AutoWhiteBalance* autoWB);

/**
 * @brief       For a video device, gets the limits of the contrast setting.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  min Pointer to int that will receive the minimum accepted value.
 * @param[out]  max Pointer to int that will receive the maximum accepted value.
 * @param[out]  stepsize Pointer to int that will receive the step size/resolution of values.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_GetContrastLevel
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetContrastLimits(unsigned short deviceID, int* min, int* max, int* stepsize);

/**
 * @brief       For a video device, gets the limits of the sharpness setting.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  min Pointer to int that will receive the minimum accepted value.
 * @param[out]  max Pointer to int that will receive the maximum accepted value.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_GetSharpnesstLevel
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSharpnessLimits(unsigned short deviceID, int* min, int* max);

/**
 * @brief       For a video device, gets the limits of the white balance setting.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  min Pointer to int that will receive the minimum accepted value.
 * @param[out]  max Pointer to int that will receive the maximum accepted value.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_GetWhiteBalance
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetWhiteBalanceLimits(unsigned short deviceID, int* min, int* max);

/**
 * @brief       For a video device, gets the limits of the saturation setting.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  min Pointer to int that will receive the minimum accepted value.
 * @param[out]  max Pointer to int that will receive the maximum accepted value.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_GetSaturationLevel
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSaturationLimits(unsigned short deviceID, int* min, int* max);

/**
 * @brief       For a video device, gets the limits of the brightness setting.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  min Pointer to int that will receive the minimum accepted value.
 * @param[out]  max Pointer to int that will receive the maximum accepted value.
 * @param[out]  stepsize Pointer to int that will receive the step size/resolution of values.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_GetBrightnessLevel
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetBrightnessLimits(unsigned short deviceID, int* min, int* max, int* stepsize);

/**
 * @brief       Enum describing the video transition styles when
 *              using Intelligent Zoom.
 */
typedef enum _Jabra_VideoTransitionStyle
{
    IMMEDIATE = 0,
    SMOOTH = 1
} Jabra_VideoTransitionStyle;

/**
 * @brief       For a video device, sets the active video transition style
 *              when using Intelligent Zoom.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   style How to switch between participants.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetVideoTransitionStyle(unsigned short deviceID, Jabra_VideoTransitionStyle style);

/**
 * @brief       For a video device, gets the active video transition style
 *              when using Intelligent Zoom.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  style How to switch between participants.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see Jabra_SetVideoTransitionStyle
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetVideoTransitionStyle(unsigned short deviceID, Jabra_VideoTransitionStyle* style);

/**
 * @brief       Enum describing the choices of notification styles when
 *              warning the users that the allowed people count is being
 *              exceeded.
 * @sa @wrap{Jabra_NotificationStyle}
 */
typedef enum _Jabra_NotificationStyle
{
    LED = 0,                //< @brief Use only LED(s)
    LED_AND_TONES = 1,      //< @brief Use LED and tones
    LED_TONES_AND_VOICE = 2 //< @brief Use LED, tones and voice warning
} Jabra_NotificationStyle;

/**
 * @brief       Enum describing when notifications are enabled on video
 *              capable devices.
 * @sa @wrap{Jabra_NotificationUsage}
 */
typedef enum _Jabra_NotificationUsage
{
    WHEN_VIDEO_IS_ENABLED = 0, //< @brief Only enable during video calls
    ALWAYS = 1                 //< @brief Always enable
} Jabra_NotificationUsage;

/**
 * @brief       Enum for how the device should control the video.
 */
typedef enum _Jabra_VideoMode
{
    FULL_SCREEN = 0,        //< @brief No automatic control
    INTELLIGENT_ZOOM = 1,   //< @brief Zoom to where the action is detected
    ACTIVE_SPEAKER = 2      //< @brief Zoom to the active speaker
} Jabra_VideoMode;

/**
 * @brief       For a video device, sets the room capacity.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   capacity Set room capacity. If notifications are enabled,
 *              the user(s) will be notified when the people count
 *              exceeds this number.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetRoomCapacity}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetRoomCapacity(unsigned short deviceID, int16_t capacity);

/**
 * @brief       For a video device, gets the room capacity.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  capacity Room capacity.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetRoomCapacity
 * @sa @wrap{Jabra_GetRoomCapacity}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetRoomCapacity(unsigned short deviceID, int16_t* capacity);

/**
 * @brief       For a video device, enables/disables room capacity
 *              notifications.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   enable true = enabled, false = disabled.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetRoomCapacityNotificationEnabled}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetRoomCapacityNotificationEnabled(unsigned short deviceID, bool enable);

/**
 * @brief       For a video device, gets whether room capacity
 *              notifications are enabled.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  enable true = enabled, false = disabled.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetRoomCapacityNotificationEnabled
 * @sa @wrap{Jabra_GetRoomCapacityNotificationEnabled}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetRoomCapacityNotificationEnabled(unsigned short deviceID, bool* enable);

/**
 * @brief       For a video device, gets the current people count.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  people the number of people currently detected
 * @return Return_Ok            Operation was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @sa @wrap{Jabra_GetPeopleCount}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPeopleCount(unsigned short deviceID, int16_t* people);

/**
 * @brief       For a video device, gets the current mode for people count and people count notifications.
 * @param[in]   deviceID   ID for the specific device.
 * @param[out]  enabled    pointer to a bool that will be set to whether People Count is enabled
 * @param[out]  interval_s pointer to a value that will be set to the interval between people count events, of 0 if no events are emitted
 * @return Return_Ok            Operation was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetPeopleCountSettings
 * @sa @wrap{Jabra_GetPeopleCountSettings}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPeopleCountSettings(unsigned short deviceID, bool* enabled, int16_t* interval_s);

/**
 * @brief       For a video device, sets mode for people count and people count notifications.
 * @param[in]   deviceID     ID for the specific device.
 * @param[in]   enabled      whether people count should be enabled
 * @param[in]   interval_s   0 means no events (get only), >0 means seconds between events, ignored if disabled
 * @return Return_Ok            Operation was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see    Jabra_GetPeopleCountSettings
 * @sa @wrap{Jabra_SetPeopleCountSettings}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetPeopleCountSettings(unsigned short deviceID, bool enabled, int16_t interval_s);

/**
 * @brief       For a video device, sets the notification style.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   style Choice how the user will receive notifications
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetNotificationStyle}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetNotificationStyle(unsigned short deviceID, Jabra_NotificationStyle style);

/**
 * @brief       For a video device, gets the notification style.
 * @param[in]   deviceID ID for the specific device.
 * @param[out]  style Choice how the user will receive notifications
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetNotificationStyle
 * @sa @wrap{Jabra_GetNotificationStyle}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetNotificationStyle(unsigned short deviceID, Jabra_NotificationStyle* style);

/**
 * @brief       For a video device, sets when notifications are enabled.
 * @param[in]   deviceID ID for the specific device.
 * @param[in]   enable setting for when notifications are enabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetNotificationUsage}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetNotificationUsage(unsigned short deviceID, Jabra_NotificationUsage enable);

/**
 * @brief       For a video device, gets when notifications are enabled.
 * @param[in]   deviceID ID for the specific device
 * @param[out]  enable setting for when notifications are enabled
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetNotificationUsage
 * @sa @wrap{Jabra_GetNotificationUsage}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetNotificationUsage(unsigned short deviceID, Jabra_NotificationUsage* enable);

/**
 * @brief       For a video device, select how the video viewport is managed (runtime).
 * @param[in]   deviceID ID for the specific device
 * @param[in]   mode Selected video mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetVideoMode(unsigned short deviceID, Jabra_VideoMode mode);

/**
 * @brief       For a video device, gets how the video viewport is managed (runtime).
 * @param[in]   deviceID ID for the specific device
 * @param[out]  mode Current video mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetVideoMode
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetVideoMode(unsigned short deviceID, Jabra_VideoMode* mode);

/**
 * @brief       For a video device, get whether the camera is actively streaming.
 * @param[in]   deviceID ID for a specific device
 * @param[out]  enable   Streaming state
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_IsCameraStreaming(unsigned short deviceID, bool* enable);

/**
 * @brief       For a video device, get whether the device is currently streaming video or audio.
 * @param[in]   deviceID ID for a specific device
 * @param[out]  activeVideoStream   Video streaming state
 * @param[out]  activeAudioStream   Audio streaming state (may be implied if video streaming state is true)
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_IsVideoDeviceStreaming(unsigned short deviceID, bool* activeVideoStream, bool* activeAudioStream);

/** Represents a PTZ preset slot on the device.
 * @sa @wrap{Jabra_PTZPreset}
 */
typedef enum _PTZPreset
{
    PTZPreset1 = 0,
    PTZPreset2 = 1,
    PTZPreset3 = 2
} Jabra_PTZPreset;

/**
 * @brief To store a PTZ (Pan, Tilt and Zoom) preset to the designated slot on the device.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[in] presetSlot        A predefined Jabra_PTZPreset slot for PTZ preset
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_StorePTZPreset}
*/
LIBRARY_API Jabra_ReturnCode Jabra_StorePTZPreset(unsigned short deviceID, Jabra_PTZPreset presetSlot);

/**
 * @brief To apply the PTZ preset from the designated slot on the device.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[in] presetSlot        A predefined Jabra_PTZPreset slot for PTZ preset
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_ApplyPTZPreset}
*/
LIBRARY_API Jabra_ReturnCode Jabra_ApplyPTZPreset(unsigned short deviceID, Jabra_PTZPreset presetSlot);

/** Represents a color control  preset slot on the device.
 * @sa @wrap{Jabra_ColorControlPreset}
 */
typedef enum _ColorControlPreset
{
    ColorControlPreset1 = 0
} Jabra_ColorControlPreset;

/**
 * @brief To store  the color control preset on the device.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[in] presetSlot        A predefined Jabra_ColorControlPreset slot for color control preset
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa Jabra_StoreColorControlPreset(), @wrap{Jabra_StoreColorControlPreset}
*/
LIBRARY_API Jabra_ReturnCode Jabra_StoreColorControlPreset(unsigned short deviceID, Jabra_ColorControlPreset presetSlot);

/**
 * @brief To apply the color control preset from the device.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[in] presetSlot        A predefined Jabra_ColorControlPreset slot for color control preset
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @sa Jabra_StoreColorControlPreset(), @wrap{Jabra_ApplyColorControlPreset}
*/
LIBRARY_API Jabra_ReturnCode Jabra_ApplyColorControlPreset(unsigned short deviceID, Jabra_ColorControlPreset presetSlot);

/**
 * @brief       For a video device, gets the Picture-In-Picture enable state (runtime).
 * @param[in]   deviceID ID for the specific device
 * @param[out]  enable Enable state
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetPictureInPicture
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPictureInPicture(unsigned short deviceID, bool* enable);

/**
 * @brief       For a video device, sets the Picture-In-Picture enable state (runtime).
 * @param[in]   deviceID ID for the specific device
 * @param[in]   enable Enable state
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see    Jabra_GetPictureInPicture
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetPictureInPicture(unsigned short deviceID, bool enable);

/**
 * @brief Resets the color controls (brightness, contrast, sharpness, saturation and white balance).
 *
 * @param[in] deviceID          ID for a specific device
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
*/
LIBRARY_API Jabra_ReturnCode Jabra_ResetImageQualityControls(unsigned short deviceID);

/**
 * @brief Resets the values for pan, tilt and zoom.
 *
 * @param[in] deviceID          ID for a specific device
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
*/
LIBRARY_API Jabra_ReturnCode Jabra_ResetPanTiltZoom(unsigned short deviceID);



/**
 * This struct represent the sensor regions of a device
 * Coordinates start at 0,0 at top left corner
 */
typedef struct _SensorRegions
{
    /** @brief Start x position of 1st sensor. (From user view sensors start from left to right) */
    uint16_t start0;
    /** @brief End x position of 1st sensor. (From user view sensors start from left to right) */
    uint16_t end0;
    /** @brief Start x position of 2nd sensor. (From user view sensors start from left to right) */
    uint16_t start1;
    /** @brief End x position of 2nd sensor. (From user view sensors start from left to right) */
    uint16_t end1;
    /** @brief Start x position of 3rd sensor. (From user view sensors start from left to right) */
    uint16_t start2;
    /** @brief End x position of 3rd sensor. (From user view sensors start from left to right) */
    uint16_t end2;

} Jabra_SensorRegions;

/**
 * @brief For a video device, gets the sensor regions
 * @param[in]   deviceID        ID for the specific device
 * @param[out]  regions         The sensor regions for the device.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @sa @wrap{Jabra_GetSensorRegions}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSensorRegions(unsigned short deviceID, Jabra_SensorRegions* regions);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_RegisterCameraStatusCallback.
 */
typedef void(*CameraStatusEventHandler)(const unsigned short deviceID, const bool status);

/**
 * @brief Registration for camera status event callback.
 * @param[in] callback          Callback method, called when camera status changes
 *                              Set to NULL to disable
 */
LIBRARY_API void Jabra_RegisterCameraStatusCallback(CameraStatusEventHandler const callback);

typedef enum _USB_CONNECTION_SPEED
{
    USB_CONNECTION_UNPLUGGED = 0,
    USB_CONNECTION_ERROR = 1,
    USB_HIGH_SPEED = 2,      // USB 2.0
    USB_SUPER_SPEED = 3,     // USB 3.0
    USB_32_GEN2 = 4          // USB 3.2 Gen2
} USB_CONNECTION_SPEED;

/**
 * @brief Gets USB connection state for video device.
 *
 * @param[in]   deviceID ID for the specific device
 * @param[out]  USBSpeed USB connection state
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
*/
LIBRARY_API Jabra_ReturnCode Jabra_GetUSBState(unsigned short deviceID, USB_CONNECTION_SPEED* USBSpeed);

#endif /* INTERFACE_VIDEO_H */
