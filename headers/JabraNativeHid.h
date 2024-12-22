#ifndef JABRANATIVEHID_H
#define JABRANATIVEHID_H

/* --------------------------------------------------------------------
 *
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Audio
 *  G    G  N   N N
 *  GGGGGG  N    NN
 *
 *  Copyright (c) 2018, GN-Audio
 * -------------------------------------------------------------------- */

/**
 * @file JabraNativeHid.h
 * @brief Defines the JabraNativeHid interface.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <stdbool.h>
#include "Common.h"

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

/**
 * @brief Write a single HID command to the telephony usage page.
 * @param[in] deviceID Id for a specific device.
 * @param[in] HID_UsagePage Usage Page.
 * @param[in] HID_Usage Usage.
 * @param[in] value True or false.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @sa @wrap{Jabra_WriteHIDCommand}
 */
LIBRARY_API Jabra_ReturnCode Jabra_WriteHIDCommand(unsigned short deviceID, unsigned short HID_UsagePage, unsigned short HID_Usage, bool value);

/**
 * @brief Set off-hook.
 * @param[in] deviceID Id for a specific device.
 * @param[in] offHook Boolean value to set off-hook/on-hook.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @see Jabra_IsOffHookSupported @wrap{Jabra_SetOffHook}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetOffHook(unsigned short deviceID, bool offHook);

/**
 * @brief Checks for off-hook command support by the device.
 * @param[in] deviceID Id for a specific device.
 * @return Returns True if off-hook is supported for a specific Jabra device.
 * @see Jabra_SetOffHook
 */
LIBRARY_API bool Jabra_IsOffHookSupported(unsigned short deviceID);

/**
 * @brief Set ringer (ringtone in headset) and ringing (ringing LED if available).
 * @param[in] deviceID Id for a specific device.
 * @param[in] ringer Boolean value to set ringer on/off and ringing LED on/off,
 * not all device have a LED for ringing.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @see Jabra_IsRingerSupported @wrap{Jabra_SetRinger}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetRinger(unsigned short deviceID, bool ringer);

/**
 * @brief Check for ringer command support by the device.
 * @param[in] deviceID Id for a specific device.
 * @return Returns True if ringer is supported for a specific Jabra device.
 * @see Jabra_SetRinger @wrap{Jabra_IsRingerSupported}
 */
LIBRARY_API bool Jabra_IsRingerSupported(unsigned short deviceID);

/**
 * @brief Set mute on or off.
 * @param[in] deviceID Id for a specific device.
 * @param[in] mute Boolean value to set mute on/off.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @see Jabra_IsMuteSupported @wrap{Jabra_SetMute}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetMute(unsigned short deviceID, bool mute);

/**
 * @brief Checks for Mute command support by the device.
 * @param[in] deviceID Id for a specific device.
 * @return Returns True if mute is supported for the Jabra device.
 * @see Jabra_SetMute
 */
LIBRARY_API bool Jabra_IsMuteSupported(unsigned short deviceID);

/**
 * @brief Set call on hold/resume.
 * @param[in] deviceID Id for a specific device.
 * @param[in] hold Boolean value to set device on hold/resume.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @see Jabra_IsHoldSupported @wrap{Jabra_SetHold}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetHold(unsigned short deviceID, bool hold);

/**
 * @brief Checks for the hold support by the device.
 * @param[in] deviceID Id for a specific device.
 * @return Returns True if hold is supported for the Jabra device.
 * @see Jabra_SetHold
 */
LIBRARY_API bool Jabra_IsHoldSupported(unsigned short deviceID);

/**
 * @brief Set device online i.e. open radio link between base/dongle and device.
 * @param[in] deviceID Id for a specific device.
 * @param[in] online Boolean value to set online On/Off.
 * @return Return_Ok if success.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Not_Supported if HID is not supported.
 * @see Jabra_IsOnlineSupported @wrap{Jabra_SetOnline}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetOnline(unsigned short deviceID, bool online);

/**
 * @brief Checks for the online mode support by the device.
 * @param[in] deviceID Id for a specific device.
 * @return Returns True if online mode is supported for a specific Jabra device.
 * @see Jabra_SetOnline
 */
LIBRARY_API bool Jabra_IsOnlineSupported(unsigned short deviceID);

/**
 * @brief Enum for setting the HID working state.
 */
typedef enum _Jabra_HidState {
  /** Setting Standard HID or GN HID is not supported */
  NOT_SUPPORTED = 0,
  /** Use standard HID as specified in the HID specification from usb.org. */
  STD_HID = 1,
  /** Use GN HID as specified by GN. */
  GN_HID = 2
} Jabra_HidState;

/**
 * @brief Is the device supporting GN HID and Std HID and are able to switch
 * between them.
 * @param[in] deviceID ID for a specific device.
 * @return True Supports GN HID and Std HID.
 * @see Jabra_SetHidWorkingState
 * @see Jabra_GetHidWorkingState
 * @sa @wrap{Jabra_IsGnHidStdHidSupported}
 */
LIBRARY_API bool Jabra_IsGnHidStdHidSupported(unsigned short deviceID);

/**
 * @brief Gets the HID working state.
 * @param[in] deviceID ID for a specific device.
 * @param[out] state HID working state.
 * @return Return_Ok working state has been set successfully.
 * @return Not_Supported the device does not support remote MMI.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Device_ReadFail if it fails to get the state from the device.
 * @return Return_ParameterFail in case of an incorrect parameter.
 * @see Jabra_IsGnHidStdHidSupported
 * @see Jabra_SetHidWorkingState
 * @sa @wrap{Jabra_GetHidWorkingState}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetHidWorkingState(unsigned short deviceID, Jabra_HidState* state);

/**
 * @brief Sets the HID working state to either standard HID (usb.org HID
 * specification) or GN HID. HID Events will (default) NOT be triggered 
 * for standard HID to avoid conflicts.
 * @param[in] deviceID ID for a specific device.
 * @param[in] state HID working state.
 * @return Return_Ok working state has been set successfully.
 * @return Not_Supported the device does not support remote MMI.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Device_WriteFail if it fails to write to the device.
 * @return Return_ParameterFail in case of an incorrect parameter.
 * @see Jabra_IsGnHidStdHidSupported
 * @see Jabra_GetHidWorkingState
 * @sa @wrap{Jabra_SetHidWorkingState}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetHidWorkingState(unsigned short deviceID, Jabra_HidState state);

#endif /* JABRANATIVEHID_H */
