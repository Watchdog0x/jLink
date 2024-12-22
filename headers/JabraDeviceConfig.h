#ifndef JABRADEVICECONFIG_H
#define JABRADEVICECONFIG_H

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
 * @file JabraDeviceConfig.h
 * @brief Defines the dynamic setting interface.
 * Developer information can be found in the universal SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Common.h"

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

/** @brief This enum represents each setting data type */
typedef enum _DataType {
  settingByte = 0,
  settingString
} DataType;

/** @brief This enum represents each setting control type. */
typedef enum _ControlType {
  cntrlRadio = 0,
  cntrlToggle,
  cntrlComboBox,
  cntrlDrpDown,
  cntrlLabel,
  cntrlTextBox,
  cntrlButton,
  cntrlEditButton,
  cntrlHorzRuler,
  cntrlPwdTextBox,
  cntrlUnknown
} ControlType;

/** @brief This structure represents validation rules. */
typedef struct _ValidationRule {
  int minLength;
  int maxLength;
  char* regExp;
  char* errorMessage;
} ValidationRule;

typedef struct _DependencySetting {
  char* GUID;
  bool enableFlag;
} DependencySetting;

/** @brief This structure contains setting values in key value pair. */
typedef struct _ListKeyValue {
  unsigned short key;
  char* value;

  int dependentcount;
  DependencySetting* dependents;
} ListKeyValue;

/** @brief This structure represents each setting info. */
typedef struct _SettingInfo {
  /* Setting GUID */
  char* guid;

  /* Setting Name */
  char* name;

  /* Setting Help Text */
  char* helpText;

  /* Current Device value for this setting */
  void* currValue;

  /* Number of values for this setting */
  int listSize;

  /* Structure for all key-value pairs for this setting */
  ListKeyValue* listKeyValue;

  /* If validation rule is supported or not */
  bool isValidationSupport;

  /* This structure contains the validation rule */
  ValidationRule* validationRule;

  /* If device restart is required for this setting */
  bool isDeviceRestart;

  /* Is setting protected */
  bool isSettingProtected;

  /* Is setting protection enabled */
  bool isSettingProtectionEnabled;

  /* When wireless headset is connected to its base/dongle */
  bool isWirelessConnect;

  /* This represents what type of control for setting */
  ControlType cntrlType;

  /* This represents datatype of setting value */
  DataType settingDataType;

  /* This represents group name of the setting */
  char* groupName;

  /* This represents group help text of the setting */
  char* groupHelpText;

  /* Whether dependency setting is present or not */
  bool isDepedentsetting;

  /* Default dependent value when setting is disabled */
  void* dependentDefaultValue;

  /* PC setting or not */
  /** @deprecated */
  bool isPCsetting; 

  /* Child device setting or not */
  bool isChildDeviceSetting;

} SettingInfo;

/** @brief This structure represents all settings available for the device. */
typedef struct _DeviceSettings {
  /* number of settings for the device */
  unsigned int settingCount;
  /* Setting information of all settings of the device */
  SettingInfo* settingInfo;
  /* manifest file download status */
  Jabra_ErrorStatus errStatus;
} DeviceSettings;

/** @brief This structure represents the product registration info. */
typedef struct _PrdctRegDetails {
  char* userName;
  char* userPassword;
  char* firstName;
  char* lastName;
  char* email;
  bool mktPermission;
} PrdctRegDetails;

/** @brief This structure represents the failed settings info. */
/** @see Jabra_GetFailedSettingNames. */
/** @see Jabra_FreeFailedSettings. */
typedef struct _FailedSettings {
  unsigned int count;
  char** settingNames;
} FailedSettings;

/** @brief This enum represents the settings load mode for the API. */
/** @deprecated */
typedef enum _SettingsLoadMode {
  expressMode = 0,
  retrieveMode
} SettingsLoadMode;

typedef enum _SettingFailType {
  guid = 0,
  value
} SettingFailType;

typedef enum _ValueType {
  success = 0,
  guidfail,
  valuefail
} ValueType;

typedef struct _InvalidInfo {
  char* guid;
  char* settingName;
  char* failMessage;
} InvalidInfo;

/** @brief This structure represents the list of Invalid settings from the file/cloud. */
typedef struct _InvalidList {
  unsigned int invalidCount;
  char* fileDeviceName;
  InvalidInfo* invalidinfo;
  Jabra_ErrorStatus errStatus;
} InvalidList;

/** @brief This structure represents the product registration info. */
typedef struct _ConfigInfo {
  char* configName;
  char* configId;
} ConfigInfo;

/** @brief This structure represents the list of configurations available from the cloud. */
typedef struct _ConfigList {
  /* no of setting for the device */
  unsigned int configCount;
  /*Config Info*/
  ConfigInfo* configinfo;
  /* config file list download status */
  Jabra_ErrorStatus errStatus;
} ConfigList;

/**
 * @brief Metadata for an asset. Read as name->Value pairs, actual values may vary - see developer documentation
 */
typedef struct _CAssetMetadata {
  char* name;
  char* value;
} CAssetMetadata;

/**
 * @brief An asset element (assets may be composed of 1 or or more of these)
 */
typedef struct _CAssetElement {
  char* url;
  char* mime;
} CAssetElement;

/**
 * @brief A named asset, requestable by #Jabra_GetNamedAsset.
 */
typedef struct _CNamedAsset {
  CAssetMetadata* metadata;
  unsigned metadata_count; // number of items in metadata
  CAssetElement* elements;
  unsigned element_count; // number of items in elements
} CNamedAsset;


/**
 * Callback. Used with Jabra_AddSettingsChangeListener.
 * @param deviceID the affected device
 * @param settings the affected settings. Must be freed by Jabra_FreeDeviceSettings
 */
typedef void (*SettingsListener)(unsigned short deviceID, DeviceSettings* settings );


/****************************************************************************/
/*                   EXPORTED DYNAMIC CONFIG - APIs                         */
/****************************************************************************/

/**
 * @brief The proposed design is to have the memory allocated at the SDK level
 * as the user may not aware of how much memory needs to be allocated. Settings
 * vary up on connected devices. So it is good SDK to decide how much memory
 * to allocate for settings.
 */

/**
 * @brief Gets the unique setting identified by a GUID of a device.
 * @param[in] deviceID Device ID of the device to read/get the setting from.
 * @param[in] guid The unique setting identifier, the string must be zero
 * terminated.
 * @return Pointer to the structure containing the requested setting. In case
 * the device is not found or could not be accessed a NULL pointer is returned.
 * @note As memory is allocated through the SDK it needs to be freed by calling
 * #Jabra_FreeDeviceSettings.
 */
LIBRARY_API DeviceSettings* Jabra_GetSetting(unsigned short deviceID, const char* guid);

/**
 * @brief Gets all supported settings details (all groups and its settings) for
 * a device.
 * @param[in] deviceID ID for specific device.
 * @return Pointer to the structure containing all settings for the deviceID.
 * In case device is not found/ could not be access, NULL pointer is returned.
 * @note As memory is allocated through SDK, need to be freed by calling
 * #Jabra_FreeDeviceSettings.
 */
LIBRARY_API DeviceSettings* Jabra_GetSettings(unsigned short deviceID);

/**
 * @brief Sets all the settings( including all groups and its settings) for a
 * device.
 * @param[in] deviceID ID for a specific device.
 * @param[in] setting Dynamic settings for the device.
 * @return Return_Ok if setting is successful.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return Return_ParameterFail if setting parameter is wrong.
 * @return Device_Rebooted if the device rebooted after applying settings that
 * required rebooting.
 * @return Device_WriteFail if it fails to write to the device.
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSettings(unsigned short deviceID, DeviceSettings* setting);

/**
 * @brief Restore factory settings to device. Note that if used on a device
 * connected via dongle (or directly via BT), the pairing list in the device
 * will be cleared, and the connection to the device will be lost.
 * @param[in] deviceID ID for a specific device.
 * @return Return_Ok if successful.
 * @return Device_Unknown if the deviceID specified is not known.
 * @return No_FactorySupported if device does not support factory reset.
 * @return Device_WriteFail if it fails to write to the device.
 * @return ProtectedSetting_Write if a setting is write protected.
 * @sa @wrap{Jabra_FactoryReset}
 */
LIBRARY_API Jabra_ReturnCode Jabra_FactoryReset(unsigned short deviceID);

/**
 * @brief Free #DeviceSettings structure.
 * @param[in] setting #DeviceSettings structure pointer, which needs to be freed.
 */
LIBRARY_API void Jabra_FreeDeviceSettings(DeviceSettings* setting);

/**
 * Free char pointer.
 * @param[in] strPtr Char pointer, which needs to be freed.
 */
LIBRARY_API void Jabra_FreeString(char* strPtr);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @return Not_Supported
 */
LIBRARY_API Jabra_ReturnCode Jabra_SaveSettingsToFile(unsigned short deviceID, const char* filePath);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief Loads the device settings from local file.
 * @param[in] deviceID ID for a specific device.
 * @param[in] filePath Path to local settings file.
 * @param[in] mode Mode to be used for updating the settings.
 * @return Valid pointer but with error status OtherError.
 * @note As memory is allocated through SDK, need to be freed by calling
 * #Jabra_FreeDeviceSettings.
 */
LIBRARY_API DeviceSettings* Jabra_LoadSettingsFromFile(unsigned short deviceID, const char* filePath, SettingsLoadMode mode);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief Saves the device settings to cloud.
 * @param[in] deviceID ID for a specific device.
 * @param[in] authorization Authorisation string for which the configs are needed.
 * @param[in] configName Name of configuration.
 * @return Not_Supported.
 */
LIBRARY_API Jabra_ReturnCode Jabra_SaveSettingsToCloud(unsigned short deviceID, const char* authorization, const char* configName);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief This method gets the list of configs for given authorisations.
 * @param[in] authorization Authorization string for which the configs are needed.
 * @return Valid pointer but with error status OtherError.
 * @note As memory is allocated through SDK, need to be freed by calling #Jabra_FreeConfigList.
 */
LIBRARY_API ConfigList* Jabra_GetCloudListOfConfigs(const char* authorization);

/**
 * @brief This method free the config list info.
 * @param[in] pConfigList Pointer to config list to be cleared.
 */
LIBRARY_API void Jabra_FreeConfigList(ConfigList* pConfigList);

/**
 * @deprecated This API is going to be deleted.
 * @brief This method free the invalid setting list info.
 * @param[in] pInvalidList Pointer to invalid list to be cleared.
 */
LIBRARY_API void Jabra_FreeInvalidList(InvalidList* pInvalidList);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief Loads the device settings from local cloud.
 * @param[in] deviceID ID for a specific device
 * @param[in] authorization Authorization id
 * @param[in] configID ID of the config file that needs to be loaded
 * @param[in] mode Mode to be used for updating the settings
 * @return Valid pointer but with error status OtherError.
 * @note As memory is allocated through SDK, need to be freed by calling #Jabra_FreeDeviceSettings.
  */
LIBRARY_API DeviceSettings* Jabra_LoadSettingsFromCloud(unsigned short deviceID, const char* authorization, const char* configID, SettingsLoadMode mode);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief Updates the settings data of a cloud file already present in cloud.
 * @param[in] deviceID ID of device from which settings needs to be updated.
 * @param[in] authorization Authorization id.
 * @param[in] configID ID of the config file that needs to be updated.
 * @param[in] configName Name of the config file to be used for update.
 * @return Not_Supported this function is deprecated.
 */
LIBRARY_API Jabra_ReturnCode Jabra_UpdateSettingsOfCloud(unsigned short deviceID, const char* authorization, const char* configID, const char* configName);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * @brief Deletes the settings file already present in cloud.
 * @param[in] authorization Authorization id.
 * @param[in] configID ID of the config file that needs to be updated.
 * @return Not_Supported this function is deprecated.
 */
LIBRARY_API Jabra_ReturnCode Jabra_DeleteSettingsOfCloud(const char* authorization, const char* configID);

/**
 * @brief Returns error description for the error code.
 * @param[in] deviceID ID for specific device.
 * @return Pointer to #FailedSettings if one or more settings are failed while
 * writing to device, NULL pointer if all settings are written successfully.
 * @note This API should be called if #Jabra_SetSettings does not return
 * Return_Ok.
 * @note As memory is allocated through SDK, needs to be freed by calling
 * #Jabra_FreeFailedSettings.
 */
LIBRARY_API FailedSettings* Jabra_GetFailedSettingNames(unsigned short deviceID);

/**
 * @brief Free #FailedSettings structure.
 * @param[in] setting #FailedSettings structure pointer, which needs to be
 * freed.
 */
LIBRARY_API void Jabra_FreeFailedSettings(FailedSettings* setting);

/**
 * @brief Checks if supports factory reset.
 * @param[in] deviceID ID for a specific device.
 * @return True if device supports factory reset, false if device does not
 * support factory reset.
 */
LIBRARY_API bool Jabra_IsFactoryResetSupported(unsigned short deviceID);

/**
 * @deprecated This API is going to be deleted - currently it does nothing.
 * Get list of invalid settings.
 * @param[in] deviceID ID for a specific device.
 * @return InvalidList, with errorstatus OtherError.
 */
LIBRARY_API InvalidList* Jabra_GetInvalidSettings(unsigned short deviceID);

/**
 * @brief Request a named asset for the specified device.
 * @param[in] deviceID ID for a specific device.
 * @param[in] name The name of the requested asset, see developer doc for a
 * catalogue of possibly available assets. Note that availability may vary
 * across devices.
 * @param[in,out] asset Address of a pointer to the returned asset. Caller must
 * free the allocated asset by calling #Jabra_FreeAsset.
 * @return Return_Ok if a valid asset was available (is then available through
 * (*asset)->...).
 * @sa @wrap{Jabra_GetNamedAsset}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetNamedAsset(unsigned short deviceID, const char* name, CNamedAsset** asset);

/**
 * @brief Release an asset previously obtained with #Jabra_GetNamedAsset.
 * @param[in] asset The asset to release.
 */
LIBRARY_API void Jabra_FreeAsset(CNamedAsset* asset);

/**
 * @brief Add a listener for changes to the device settings. The listener will
 * be called when a setting is changed in the device, regardless of who
 * changed it (this instance, another instance, or the user through MMI).
 * @param deviceID ID for a specific device.
 * @param listener The function to receive callbacks. Set to null to cancel
 * listening.
 * @param settings The settings which the client is interested in. Remains
 * owned by the caller. Set to null to cancel listening.
 * @return Return_Ok if successful.
 * @return Not_Supported if feature is not supported.
 * @return Device_Unknown if device not known.
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetSettingsChangeListener(unsigned short deviceID, SettingsListener listener, const DeviceSettings* settings);

#endif /* JABRADEVICECONFIG_H */
