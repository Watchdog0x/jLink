#ifndef INTERFACE_BLUETOOTH_H
#define INTERFACE_BLUETOOTH_H

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
 * @file Interface_Bluetooth.h
 * @brief Defines the Bluetooth interfaces for the Jabra SDK.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "Common.h"

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef enum _DeviceListType
{
    SearchResult,
    PairedDevices,
    SearchComplete
} Jabra_DeviceListType;

/** @brief Paired devices list struct. */
typedef struct _PairedDevice
{
    /** @brief Name of device, this is end-user editable i.e. it is not
     * necessarily the name of the product. */
    char* deviceName;
    /** @brief Bluetooth MAC address. */
    uint8_t deviceBTAddr[6];
    /** Current connection status. */
    bool isConnected;
} Jabra_PairedDevice;

/** @brief List of paired devices list struct. */
typedef struct _PairingList
{
    /** Number of #Jabra_PairedDevice elements in the list. */
    unsigned short count;
    /** List type identifier. */
    Jabra_DeviceListType listType;
    /** Paired device information. */
    Jabra_PairedDevice* pairedDevice;
} Jabra_PairingList;

/** @brief The secure connection modes */
typedef enum _SecureConnectionMode {
    /** Normal pairing allowed */
    SC_LEGACY_MODE = 0,
    /** Device is allowed to connect a audio gateway eg. a mobile phone */
    SC_SECURE_MODE,
    /** Pairing not allowed */
    SC_RESTRICTED_MODE
} Jabra_SecureConnectionMode;

/**
 * @brief Set the Bluetooth device in pairing mode.
 * @param[in] deviceID          ID for a BT adapter
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_SearchNewDevices
 * @see Jabra_GetSearchDeviceList
 * @see Jabra_StopBTPairing
 * @see Jabra_SetAutoPairing
 * @see Jabra_GetAutoPairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetBTPairing(unsigned short deviceID);

/**
 * @brief Search for available Bluetooth devices which are switched on, within
 * range and ready to connect.
 * @param[in] deviceID          ID for the BT adapter
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_SetBTPairing
 * @see Jabra_GetSearchDeviceList
 * @see Jabra_StopBTPairing
 * @see Jabra_SetAutoPairing
 * @see Jabra_GetAutoPairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_SearchNewDevices(unsigned short deviceID);

/**
 * @brief Gets the list of new devices which are available to pair & connect.
 * @param[in] deviceID ID for specific device
 * @return Pointer to a #Jabra_PairingList struct containing
 * available devices ready to pair
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreePairingList.
 * @see Jabra_SetBTPairing
 * @see Jabra_SearchNewDevices
 * @see Jabra_StopBTPairing
 * @see Jabra_SetAutoPairing
 * @see Jabra_GetAutoPairing
 */
LIBRARY_API Jabra_PairingList* Jabra_GetSearchDeviceList(unsigned short deviceID);

/**
 * @brief Stop search for available Bluetooth devices.
 * @param[in] deviceID ID for a BT adapter.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_SetBTPairing
 * @see Jabra_SearchNewDevices
 * @see Jabra_GetSearchDeviceList
 * @see Jabra_SetAutoPairing
 * @see Jabra_GetAutoPairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_StopBTPairing(unsigned short deviceID);

/**
 * @brief When Bluetooth adapter is plugged into the PC it will attempt to
 * connect with the last connected Bluetooth device. If it cannot connect,
 * it will automatically search for new Bluetooth devices to connect to.
 * @param[in] deviceID          ID for a BT adapter
 * @param[in] value             Enable or disable auto pairing
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_SetBTPairing
 * @see Jabra_SearchNewDevices
 * @see Jabra_GetSearchDeviceList
 * @see Jabra_StopBTPairing
 * @see Jabra_GetAutoPairing
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetAutoPairing(unsigned short deviceID, bool value);

/**
 * @brief Get Auto pairing mode enable or disable.
 * @param[in] deviceID          ID for a Bluetooth adapter
 * @return true                 Auto pairing mode is enabled
 * @return false                Auto pairing mode is not enabled
 * @see Jabra_SetBTPairing
 * @see Jabra_SearchNewDevices
 * @see Jabra_GetSearchDeviceList
 * @see Jabra_StopBTPairing
 * @see Jabra_SetAutoPairing
 */
LIBRARY_API bool Jabra_GetAutoPairing(unsigned short deviceID);

/**
 * @brief Connect/Reconnect Bluetooth device to the Jabra Bluetooth adapter.
 * Ensure the Bluetooth device is switched on and within range.
 * @param[in] deviceID          ID for a BT adapter.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_ConnectNewDevice
 * @see Jabra_DisconnectBTDevice
 * @see Jabra_ConnectPairedDevice
 * @see Jabra_DisConnectPairedDevice
 * @see Jabra_GetConnectedBTDeviceName
 */
LIBRARY_API Jabra_ReturnCode Jabra_ConnectBTDevice(unsigned short deviceID);

/**
 * @brief Connect a new device.
 * @param[in] deviceID              ID for specific device
 * @param[in] device                Pointer to #Jabra_PairedDevice struct
 * @return Return_Ok                Call was successful
 * @return Device_Unknown           deviceID is unknown
 * @return Device_AlreadyConnected  Device is already connected
 * @return Device_WriteFail         Failed while writing to device
 * @see Jabra_ConnectBTDevice
 * @see Jabra_DisconnectBTDevice
 * @see Jabra_ConnectPairedDevice
 * @see Jabra_DisConnectPairedDevice
 * @see Jabra_GetConnectedBTDeviceName
 */
LIBRARY_API Jabra_ReturnCode Jabra_ConnectNewDevice(unsigned short deviceID, Jabra_PairedDevice* device);

/**
 * @brief Disconnect Bluetooth device from Bluetooth adapter.
 * @param[in] deviceID          ID for a BT adapter
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_ConnectBTDevice
 * @see Jabra_ConnectNewDevice
 * @see Jabra_ConnectPairedDevice
 * @see Jabra_DisConnectPairedDevice
 * @see Jabra_GetConnectedBTDeviceName
 */
LIBRARY_API Jabra_ReturnCode Jabra_DisconnectBTDevice(unsigned short deviceID);

/**
 * @brief Connect a device which was already paired.
 * @param[in] deviceID              ID for specific device
 * @param[in] device                Pointer to #Jabra_PairingList struct
 * @return Return_Ok                Call was successful
 * @return Device_Unknown           deviceID is unknown
 * @return Device_AlreadyConnected  Device is already connected
 * @return Device_WriteFail         Failed while writing to device
 * @note After device connection, #Jabra_GetPairingList API has to be called
 * to get updated connection status. In order to connect to a device from the
 * list of paired devices, make sure that there is no paired device currently
 * connected. Any paired device currently connected has to be disconnected by
 * calling #Jabra_DisConnectPairedDevice before using
 * #Jabra_ConnectPairedDevice.
 * @see Jabra_ConnectBTDevice
 * @see Jabra_ConnectNewDevice
 * @see Jabra_DisconnectBTDevice
 * @see Jabra_DisConnectPairedDevice
 * @see Jabra_GetConnectedBTDeviceName
*/
LIBRARY_API Jabra_ReturnCode Jabra_ConnectPairedDevice(unsigned short deviceID, Jabra_PairedDevice* device);

/**
 * @brief Disconnect a paired device.
 * @param[in] deviceID          ID for specific device.
 * @param[in] device            Pointer to #Jabra_PairingList struct
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Device_NotConnected  Device is not connected
 * @return Device_WriteFail     Failed while writing to device
 * @note After device disconnection, #Jabra_GetPairingList API has to be called
 * to get updated connection status.
 * @see Jabra_ConnectBTDevice
 * @see Jabra_ConnectNewDevice
 * @see Jabra_DisconnectBTDevice
 * @see Jabra_ConnectPairedDevice
 * @see Jabra_GetConnectedBTDeviceName
 */
LIBRARY_API Jabra_ReturnCode Jabra_DisConnectPairedDevice(unsigned short deviceID, Jabra_PairedDevice* device);

/**
 * @brief Get name of connected BT device with BT adapter.
 * @param[in] deviceID          ID for a BT adapter
 * @return Pointer to string with name of connected BT device if successful,
 * otherwise returns NULL.
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreeString.
 * @see Jabra_ConnectBTDevice
 * @see Jabra_ConnectNewDevice
 * @see Jabra_DisconnectBTDevice
 * @see Jabra_ConnectPairedDevice
 * @see Jabra_DisConnectPairedDevice
 */
LIBRARY_API char* Jabra_GetConnectedBTDeviceName(unsigned short deviceID);

/**
 * @brief Checks if pairing list is supported by the device.
 * @param[in] deviceID      ID for a device
 * @return true             Pairing list is supported
 * @return false            Pairing list is not supported
 * @see Jabra_GetPairingList
 * @see Jabra_ClearPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_ClearPairedDevice
 * @see Jabra_RegisterPairingListCallback
 */
LIBRARY_API bool Jabra_IsPairingListSupported(unsigned short deviceID);

/**
 * @brief Gets the secure connection mode. The interface is only valid to use for a dongle.
 * @param[in] deviceID          ID for a device
 * @param[out] scMode           Secure connection mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @see Jabra_GetPairingList
 * @see Jabra_ClearPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_ClearPairedDevice
 * @see Jabra_RegisterPairingListCallback
 * @sa @wrap{Jabra_GetSecureConnectionMode}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetSecureConnectionMode(unsigned short deviceID, Jabra_SecureConnectionMode* scMode);

/**
 * @brief Gets the list of devices which are paired previously.
 * @param[in] deviceID      ID for specific device
 * @return Pointer to #Jabra_PairingList struct containing paired device details.
 * @note As memory is allocated through SDK, it must be freed by calling
 * #Jabra_FreePairingList.
 * @see Jabra_IsPairingListSupported
 * @see Jabra_ClearPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_ClearPairedDevice
 * @see Jabra_RegisterPairingListCallback
 */
LIBRARY_API Jabra_PairingList* Jabra_GetPairingList(unsigned short deviceID);

/**
 * @brief Clear list of paired BT devices from BT adaptor.
 * @param[in] deviceID          ID for a BT adapter
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_IsPairingListSupported
 * @see Jabra_GetPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_ClearPairedDevice
 * @see Jabra_RegisterPairingListCallback
 */
LIBRARY_API Jabra_ReturnCode Jabra_ClearPairingList(unsigned short deviceID);

/**
 * @brief Frees the memory allocated for the list of paired devices.
 * @param[in] deviceList    Pointer to #Jabra_PairingList struct to be freed
 * @see Jabra_IsPairingListSupported
 * @see Jabra_GetPairingList
 * @see Jabra_ClearPairingList
 * @see Jabra_ClearPairedDevice
 * @see Jabra_RegisterPairingListCallback
 */
LIBRARY_API void Jabra_FreePairingList(Jabra_PairingList* deviceList);

/**
 * @brief Clear devices from the paired device list.
 * @param[in] deviceID          ID for specific device.
 * @param[in] device            Pointer to #Jabra_PairingList struct
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return CannotClear_DeviceConnected Device has an active connection
 * @return Device_WriteFail     Failed while writing to device
 * @see Jabra_IsPairingListSupported
 * @see Jabra_GetPairingList
 * @see Jabra_ClearPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_RegisterPairingListCallback
 */
LIBRARY_API Jabra_ReturnCode Jabra_ClearPairedDevice(unsigned short deviceID, Jabra_PairedDevice* device);

/**
 * @brief Register callback for Pairing list.
 * @param[in] PairingList   Callback method, will be called when paired devices
 * changed event received from device.
 * @see Jabra_IsPairingListSupported
 * @see Jabra_GetPairingList
 * @see Jabra_ClearPairingList
 * @see Jabra_FreePairingList
 * @see Jabra_ClearPairedDevice
 */
LIBRARY_API void Jabra_RegisterPairingListCallback(void(*PairingList)(unsigned short deviceID, Jabra_PairingList* lst));

typedef enum _LinkQuality
{
    LINKQUALITY_OFF = 0,
    LINKQUALITY_LOW = 1,
    LINKQUALITY_HIGH = 2
} LinkQuality;

/** Listener for Link Quality events */
typedef void (*LinkQualityStatusListener)(unsigned short deviceID, const LinkQuality status);

/**
 * @brief Subscribe/unsubscribe to Link quality change events. Not available on all devices.
 * @param[in] deviceID      ID for specific device
 * @param[in] listener      The callback for LinkQuality events. Set to NULL to unsubscribe. Callback will occur on a separate thread.
 * @return Return_Ok        Call was successful
 * @return Device_Unknown   deviceID is unknown
 * @return Not_Supported    Link quality change events not supported by device
 * @ingroup g-events
 * @ingroup g-dev-status
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetLinkQualityStatusListener(unsigned short deviceID, LinkQualityStatusListener listener);

#endif /* INTERFACE_BLUETOOTH_H */
