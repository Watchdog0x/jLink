#ifndef INTERFACE_AMBIENCEMODES_H
#define INTERFACE_AMBIENCEMODES_H

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
 * @file Interface_AmbienceModes.h
 * @brief Defines the ambience mode interfaces for the Jabra SDK.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "Common.h"

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

/**
 * @brief       Enum describing the possible ambience modes
 */
typedef enum _Jabra_AmbienceMode
{
    OFF,            /* No hearthrough or noise cancellation activared */
    HEARTHROUGH,    /* Hearthrough - the user will get audio from their
                       surroundings in the headset */
    ANC             /* Active Noise Cancellation*/
} Jabra_AmbienceMode;

/**
 * @brief       Enum describing extended settings for the ambience modes.
 */
typedef enum _Jabra_AmbienceModeSetting
{
  MIX,  /* When enabled, the user will get a mixture of the ambience mode selected
           and the audio stream (e.g. music playing in the phone). When disabled,
           the user will get only ambience audio (e.g. if listening to music, the music
           will be paused. */
  PERSONALIZATION_COMPLETE /* When enabled, it signals that the personalization
                              for the ambience mode has already been carried out,
                              and there is no need to repeat it. */
} Jabra_AmbienceModeSetting;

/**
 * @brief       This enum represent the fact that something related to ambience
 *              mode changed on the device. It does not convey any information
 *              about the new value after the change.
 */
typedef enum _Jabra_AmbienceModeChangeEvent
{
    MODE,
    ANC_LEVEL,
    HEARTHROUGH_LEVEL,
    ANC_SETTINGS,
    HEARTHROUGH_SETTINGS,
    ANC_BALANCE
} Jabra_AmbienceModeChangeEvent;

/** Listener for Ambience mode change events */
typedef void (*AmbienceModeChangeListener)(unsigned short deviceID, Jabra_AmbienceModeChangeEvent event);

/**
 * @brief       For a device supporting ambience modes, get the current mode.
 * @param[in]   deviceID        ID for the specific device
 * @param[out]  ambienceMode    The current mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceMode(unsigned short deviceID, Jabra_AmbienceMode* ambienceMode);

/**
 * @brief       For a device supporting ambience modes, set the mode.
 * @param[in]   deviceID        ID for the specific device
 * @param[in]   ambienceMode    The mode to be set
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceMode(unsigned short deviceID, Jabra_AmbienceMode ambienceMode);

/**
 * @brief       Returns which ambience modes are supported by the device.
 * @param[in]       deviceID    ID for the specific device
 * @param[out]      modes       Pre-allocated array where the supported modes will be written
 * @param[in,out]   length      The length of the input array. After the API call, it will
 *                              contain the actual size of the returned array (i.e. the
 *                              number of valid elements). This means that it's set to 0 on
 *                              errors, unless it's an invalid pointer.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed or a buffer was too small
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSupportedAmbienceModes(unsigned short deviceID, Jabra_AmbienceMode* modes, size_t* length);

/**
 * For a device supporting ambience modes, get the minimum supported level for a given mode.
 * E.g. if it returns 5, the possible levels are 0,1,2,3,4 and 5 where 0 is the maximum.
 *
 * @brief       For a device supporting ambience modes, get the supported levels for a given mode.
 * @param[in]   deviceID        ID for the specific device
 * @param[in]   ambienceMode    The mode of which we want to know the number of levels
 * @param[out]  levels          The levels available for the given mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail levels is a NULL pointer, or the mode
 * doesn't support levels (e.g. OFF)
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSupportedAmbienceModeLevels(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, uint8_t* levels);

/**
 * @brief       For a device supporting ambience modes, get current level for a given mode.
 * @param[in]   deviceID        ID for the specific device
 * @param[in]   ambienceMode    The mode of which we want to know the level of
 * @param[out]  level           The current level for the given mode, where 0 is the maximum and
 *                              the minimum is what {@link Jabra_GetSupportedAmbienceModeLevels}
 *                              returns. E.g. if it is 5, 5-0 are the levels we can get.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail level is a NULL pointer, or the mode
 * doesn't support levels (e.g. OFF)
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceModeLevel(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, uint8_t* level);

/**
 * @brief       For a device supporting ambience modes, set the level for a given mode.
 * @param[in]   deviceID       ID for the specific device
 * @param[in]   ambienceMode   The mode of which we want to set the level of
 * @param[in]   level          The new level for the given mode, where 0 is the maximum and
 *                             the minimum is what {@link Jabra_GetSupportedAmbienceModeLevels}
 *                             returns. E.g. if it is 5, 5-0 are the levels we can set.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail The mode doesn't support levels (e.g. OFF)
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceModeLevel(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, uint8_t level);

/**
 * For a device supporting ambience modes, get the minimum/maximum supported
 * value for left-right balance. This value is a positive number N, which
 * indicates that the supported left-right balance values are within the range
 * [-N; N] (e.g. if the value of N is 3, the range is [-3; 3]).
 *
 * @brief       For a device supporting ambience modes, get the supported minimum/maximum
 *              right-left balance.
 * @param[in]   deviceID              ID for the specific device
 * @param[in]   ambienceMode          The mode of which we want to know the
 *                                    supported minimum/maximum left-right balance of.
 * @param[out]  balance               The variable filled with the supported
 *                                    minimum/maximum left-right balance from
 *                                    the device. The value is positive and indicates
 *                                    both the positive maximum and the negative
 *                                    minimum (e.g. 3 means that the supported
 *                                    left-right balance range is [-3; 3]).
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail balance is a NULL pointer or the mode
 * doesn't support left-right balance (e.g. OFF).
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSupportedAmbienceModeBalance(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, uint8_t* balance);

/**
 * For a device supporting ambience modes, get the left-right balance of a given
 * ambience mode:
 * - 0 means neutral balance
 * - negative values indicate balance on the left: the lower the number the
 *      more the balance is on the left.
 * - positive values are for balance on the right: the higher the value, the
 *      more the balance is on the right.
 * Returned values are constrained in a range [-N; N], where N is what
 * Jabra_GetSupportedAmbienceModeBalance returns (e.g. if Jabra_GetSupportedAmbienceModeBalance
 * returns 2, then the valid values are in the range [-2; 2]).
 *
 * @brief       For a device supporting ambience modes, get the current right-left balance.
 * @param[in]   deviceID              ID for the specific device
 * @param[in]   ambienceMode          The mode of which we want to know the left-right balance of
 * @param[out]  balance               The variable filled with the left-right balance
 *                                    from the device. 0 is neutral balance, negative
 *                                    values are for balance on the left, positive
 *                                    numbers indicate balance on the right. The values
 *                                    are within a range [-N; N], where N is returned by
 *                                    Jabra_GetSupportedAmbienceModeBalance.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail balance is a NULL pointer or the mode
 * doesn't support left-right balance (e.g. OFF).
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceModeBalance(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, int8_t* balance);

/**
 * For a device supporting ambience modes, set the left-right balance of a given
 * ambience mode:
 * - 0 means neutral balance
 * - negative values indicate balance on the left: the lower the number the
 *      more the balance is on the left
 * - positive values are for balance on the right: the highter the value, the
 *      more the balance is on the right.
 * Valid values are constrained in a range [-N; N], where N is what
 * Jabra_GetSupportedAmbienceModeBalance returns (e.g. if Jabra_GetSupportedAmbienceModeBalance
 * returns 2, then the valid values are in the range [-2; 2]).
 *
 * @brief       For a device supporting ambience modes, set current right-left balance.
 * @param[in]   deviceID              ID for the specific device
 * @param[in]   ambienceMode          The mode for which we want set the left-right balance
 * @param[in]   balance               The left-right balance. 0 is neutral balance
 *                                    negative values are for balance on the left,
 *                                    positive numbers indicate balance on the right.
 *                                    Valid values are within a range [-N; N], where N
 *                                    is returned by Jabra_GetSupportedAmbienceModeBalance.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail The mode doesn't support left-right balance, (e.g. OFF)
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceModeBalance(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, int8_t balance);

/**
 * @brief       For a device supporting ambience modes, get the noise level for the current active mode.
 * @param[in]   deviceID        ID for the specific device
 * @param[out]  noiseLevel      The variable filled with the noise level from
 *                              the device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceModeNoiseLevel(unsigned short deviceID, uint8_t* noiseLevel);

/**
 * @brief       For a device supporting ambience modes, get whether or not a setting is enabled for a given mode.
 * @param[in]   deviceID              ID for the specific device
 * @param[in]   ambienceMode          The mode of which we want to know whether a setting is enabled of
 * @param[in]   ambienceModeSetting   The setting we want to know whether it's enabled or not
 * @param[out]  enabled               Whether the setting is enabled or not for the given mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed or mode does not support setting
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceModeSetting(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, Jabra_AmbienceModeSetting ambienceModeSetting, bool* enabled);

/**
 * @brief       For a device supporting ambience modes, enable or disable a setting for a given mode.
 * @param[in]   deviceID              ID for the specific device
 * @param[in]   ambienceMode          The mode of which we want enable/disable a setting
 * @param[in]   ambienceModeSetting   The setting we want to enabled or disable
 * @param[in]   enabled               Whether we want to enable (true) or disable (false) the setting
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail Mode does not support the setting.
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceModeSetting(unsigned short deviceID, Jabra_AmbienceMode ambienceMode, Jabra_AmbienceModeSetting ambienceModeSetting, bool enabled);

/**
 * @brief       Returns the current ambience mode loop.
 * @param[in]       deviceID    ID for the specific device
 * @param[out]      modes       Pre-allocated array where the modes in the loop will be written
 * @param[in,out]   length      The length of the input array. After the API call, it will
 *                              contain the actual size of the returned array (i.e. the
 *                              number of valid elements). This means that it's set to 0 on
 *                              errors, unless it's an invalid pointer.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed or buffer is too small
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetAmbienceModeLoop(unsigned short deviceID, Jabra_AmbienceMode* modes, size_t* length);

/**
 * @brief       Sets the ambience mode loop.
 * @param[in]   deviceID    ID for the specific device
 * @param[in]   modes       Array containing the ambience mode loop
 *                          It can be empty, which means passing a NULL pointer
 *                          and 0 as `length`
 * @param[in]   length      The length of the input array
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device. Will also happen
 * if loop is too long.
 * @return Return_ParameterFail A NULL pointer was passed when length != 0
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceModeLoop(unsigned short deviceID, const Jabra_AmbienceMode* modes, size_t length);

/**
 * @brief       Register a listener for ambience mode change events.
 * @param[in]   deviceID    ID for the specific device
 * @param[in]   listener    Listener that receives AmbienceModeChange events
 *                          Set to NULL to unsubscribe
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAmbienceModeChangeListener(unsigned short deviceID, AmbienceModeChangeListener listener);

#endif /* INTERFACE_AMBIENCEMODES_H */
