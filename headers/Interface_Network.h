#ifndef INTERFACE_NETWORK_H
#define INTERFACE_NETWORK_H

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
 * @file Interface_Network.h
 * @brief Defines the network-related interfaces for the Jabra SDK.
 * Developer information can be found in the SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "Common.h"

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef struct _IPv4Status
{
    bool InterfaceEnabled;
    bool DHCPEnabled;
    bool ConnectionStatus;
    struct _IP
    {
        uint8_t octet1;
        uint8_t octet2;
        uint8_t octet3;
        uint8_t octet4;
    } IP, SubNetMask;
} IPv4Status;

/**
 * @brief     Enables or disables remote management. If enabling and there are no active network interfaces (eth/wlan),
 *            it will automatically enable the Ethernet interface as well since remote mgmnt requires a network.
 *            If a timeout is specified, it will wait for an interface to be IP-configured before returning.
 * @param[in] deviceID  ID for a specific device
 * @param[in] enable    Enable state: true=enabled, false=disabled
 * @param[in] timeout   Time to wait for ethernet interface to become ready. Set to 0 to return immediately.
 * @return Return_Ok            Remote management is enabled
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return NetworkRequest_Fail  Management was enabled, but no working network interface was available at the time of return.
 * @see Jabra_GetEthernetIPv4Status
 */
LIBRARY_API Jabra_ReturnCode Jabra_EnableRemoteManagement(unsigned short deviceID, bool enable, unsigned int timeout);

/**
 * @brief       Get whether remote management is enabled on a networked device.
 * @param[in]   deviceID ID for a specific device
 * @param[out]  enable   Enable state: true=enabled, false=disabled
 *                       Will only be written to if return value == Return_Ok.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_IsRemoteManagementEnabled(unsigned short deviceID, bool* enable);

typedef struct _ProxySettings
{
    enum _ProxyType      // See curl documentation for explanation of proxy types,
    {                    // e.g. https://everything.curl.dev/libcurl/proxies
        PROXY_HTTP = 0,
        PROXY_HTTPS,
        PROXY_SOCKS4,
        PROXY_SOCKS4A,
        PROXY_SOCKS5,
        PROXY_SOCKS5H
    } Type;
    char* URL;           // Pointer to NULL-terminated string containing RFC 3986+ proxy address
    char* Hostname;      // Pointer to NULL-terminated string containing proxy hostname
    unsigned short Port; // Port number
    char* Username;      // Pointer to NULL-terminated string containing the login username for the proxy
    char* Password;      // Pointer to NULL-terminated string containing the login password for the proxy
} ProxySettings;

/**
 * @brief     Configures Xpress management related settings on a network-capable device.
 *            Will enable Ethernet interface if no network interfaces are available.
 *            In case of NetworkRequest_Fail or Return_Timeout return codes, the
 *            proxy configuration and Xpress URL will revert to the previous values.
 * @param[in] deviceID          ID for a specific device
 * @param[in] xpressurl         Pointer to NULL-terminated string containing the URL for the Xpress management backend.
 *                              Protocol is always assumed to be HTTPS no matter the prefix of the URL.
                                Setting URL pointer to NULL will disable management.
 * @param[in] proxy             Pointer to proxy settings - set to NULL if not using proxy (default)
 * @param[in] timeout           Maximum allowed execution time for the entire operation.
 *                              In the worst cast the flow is:
 *                              1. Enabling network interface
 *                              2. Waiting for DHCP resolution
 *                              3. Startup of management service
 *                              4. DNS resolution of specified URL
 *                              5. HTTPS request and parsing the response
 *                              The recommended value is 30'000 ms.
 *                              Setting timeout=0 will configure the device and return immediately without checking the validity of the xpressurl.
 * @return Return_Ok            Device was successfully configured for stand-alone remote management
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A parameter was missing or incorrect
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @return NetworkRequest_Fail  URL was unreachable - see Jabra_GetXpressManagementNetworkStatus
 * @return Return_Timeout       URL validation did not complete before timeout (when timeout>0)
 * @see Jabra_GetXpressManagementNetworkStatus
 */
LIBRARY_API Jabra_ReturnCode Jabra_ConfigureXpressManagement(unsigned short deviceID, const char* xpressurl, const ProxySettings* proxy, unsigned int timeout);

/**
 * @brief     Gets the resulting libcurl errorcode and message from the last call to
 *            Jabra_ConfigureXpressManagement() if it returned NetworkRequest_Fail.
 * @param[in]  deviceID         ID for a specific device
 * @param[out] errorcode        Pointer to int that will receive libcurl error code. If NULL, no error code will be returned.
 * @param[out] message          Pointer to buffer that will receive libcurl error message. If NULL, no error message will be returned.
 * @param[in]  buffersize       Size of buffer pointed to by 'message' (including NULL terminator). Ignored if errormessage==NULL.
 * @return false                Last call to Jabra_ConfigureXpressManagement() did not produce an errorcode/message.
 * @return true                 An error code/message is available. In case of errorcode==0 it means the last request was successful
 *                              and the message will be empty.
 *                              If 'errorcode' or 'message' pointers are non-NULL, they will receive the information.
 * @see Jabra_ConfigureXpressManagement
 */
LIBRARY_API bool Jabra_GetXpressManagementNetworkStatus(unsigned short deviceID, unsigned short* errorcode, char* message, int buffersize);

/**
 * @brief     Set Xpress server URL. Will block until URL has been validated or timeout reached.
 *            In case of NetworkRequest_Fail or Return_Timeout return codes, URL will still be set,
 *            so if this is not wanted, clear the URL by setting url to an empty string.
 * @param[in] deviceID  ID for a specific device
 * @param[in] url       Pointer to char buffer containing NULL-terminated URL
 * @param[in] timeout   Time to wait for URL validation in ms. Set to 0 to return immediately.
 * @return Return_Ok            URL was changed and verified successfully
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_WriteFail     Failed while writing to device
 * @return System_Error         Some unspecified system error occurred
 * @return NetworkRequest_Fail  URL was evaluated to be incorrect or unreachable
 * @return Return_Timeout       URL validation did not complete before timeout
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetXpressUrl(unsigned short deviceID, const char* url, unsigned int timeout);

/**
 * @brief       Get Xpress server URL.
 * @param[in]   deviceID    ID for a specific device
 * @param[out]  url         Pointer to a buffer where the URL string will be written
 *                          Must be preallocated by the caller
 * @param[in]   size        Size of preallocated buffer 'url'. Max limit 2kB
 * @return Return_Ok            Call was successful. Will also return Return_Ok if url is not set
 * or device does not support xpress features, however output string will be "".
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed or buffer is too small
 * @return Device_ReadFails     Failed while reading from device
  */
LIBRARY_API Jabra_ReturnCode Jabra_GetXpressUrl(unsigned short deviceID, char* url, int size);

/**
 * @brief       Set password for password provisioning.
 * @param[in]   deviceID    ID for a specific device
 * @param[in]   password    Pointer to char buffer containing NULL-terminated password
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetPasswordProvisioning(unsigned short deviceID, const char* password);

/**
 * @brief       Get the password for provisioning.
 * @param[in]   deviceID    ID for a specific device
 * @param[out]  password    Pointer to a buffer where the password string will be written
 *                          Must be preallocated by the caller
 * @param[in]   size        Size of preallocated buffer 'password'. Max limit 2kB
 * @return Return_Ok            Call was successful. Will also return Return_Ok if password is not set
 * or device does not support password provisioning, however output string will be "".
 * @return Device_Unknown       deviceID is unknown
 * @return Return_ParameterFail A NULL pointer was passed or buffer is too small
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetPasswordProvisioning(unsigned short deviceID, char* password, int size);

/**
 * @brief       Notify the app connected to an Xpress capable device whether device is being remotely managed.
 * @param[in]   deviceID    ID for a specific device
 * @param[in]   isConnected true=connection to the backend is established, false=is not established
 * @return Return_Ok            Call was successful. Unsupported devices will silently
 * ignore this, so Return_Ok does not imply that the feature is supported.
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_NotifyXpressConnectionStatus(unsigned short deviceID, bool isConnected);

/**
 * @brief       Notify the app connected to an Xpress capable device whether device is being remotely managed.
 * @param[in]   deviceID    ID for a specific device
 * @param[in]   isConnected true=connection to the backend is established, false=is not established
 * @param[in]   errorcode   libcurl error code
 * @param[in]   errorstring error message in case of error. Can be NULL if no message.
 * @return Return_Ok            Call was successful. Unsupported devices will silently
 * ignore this, so Return_Ok does not imply that the feature is supported.
 * @return Device_Unknown       deviceID is unknown
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_NotifyXpressConnectionStatusExtended(unsigned short deviceID, bool isConnected, unsigned short errorcode, const char* errorstring);

/**
 * @brief Registration for Xpress connection status change callback.
 * Parameters are identical to those of Jabra_NotifyXpressConnectionStatus*
 * @param[in] xpressConnectionStatus Callback method to be called when the Xpress connection status is changed
 */
LIBRARY_API void Jabra_RegisterXpressConnectionStatusCallback(void(*xpressConnectionStatus)(unsigned short, bool));
/**
 * @brief Registration for Xpress connection status change callback.
 * Parameters are identical to those of Jabra_NotifyXpressConnectionStatus*
 * @param[in] xpressConnectionExtendedStatus Callback method to be called when the Xpress connection status is changed
 */
LIBRARY_API void Jabra_RegisterXpressConnectionStatusExtendedCallback(void(*xpressConnectionExtendedStatus)(unsigned short, bool, unsigned short, char*));

/**
 * @brief Gets the status of the Ethernet connection; Enable, DHCP, Connected states and IP + subnet mask.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[out] ethernetStatus   Pointer to an IPv4Status struct that will be filled with the details of the Ethernet connection.
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
*/
LIBRARY_API Jabra_ReturnCode Jabra_GetEthernetIPv4Status(const unsigned short deviceID, IPv4Status* ethernetStatus);

/**
 * @brief Gets the status of the WLAN connection; Enable, DHCP, Connected states and IP + subnet mask.
 *
 * @param[in] deviceID          ID for a specific device
 * @param[out] wlanStatus       Pointer to an IPv4Status struct that will be filled with the details of the WLAN connection.
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
*/
LIBRARY_API Jabra_ReturnCode Jabra_GetWLANIPv4Status(const unsigned short deviceID, IPv4Status* wlanStatus);

typedef enum _NetworkInterface {
    Interface_Ethernet = 0,
    Interface_WLAN = 1,
    Interface_Bluetooth = 2
} NetworkInterface;

typedef enum _NetworkInterfaceStatus {
    NETWORK_LINK_DOWN = 0,
    NETWORK_LINK_UP = 1,
    NETWORK_IPADDRESS_SET = 2,
    NETWORK_IPADDRESS_REMOVED = 3
} NetworkInterfaceStatus;

/**
 * @brief Registration for network interface status change callback.
 * @param[in] networkStatus Pointer to callback method to be called when the status of a network interface changes.
 *                          Set to NULL to remove callback.
 * Parameters of callback are:
 * deviceID         ID for a specific device
 * ifc              Interface where the change happened
 * status           New status
 */
LIBRARY_API void Jabra_RegisterNetworkStatusChangedCallback(void(*networkStatus)(unsigned short, NetworkInterface, NetworkInterfaceStatus));

/**
 * @brief Gets the MAC address of an interface.
 *
 * @param[in]  deviceID         ID for a specific device
 * @param[in]  netIF            Selected interface
 * @param[out] MACaddr          Pointer to a buffer that will receive the MAC address.
 *                              The size of the buffer needs to be at least 6 bytes as this is the amount of data that will be written.
 *
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
*/
LIBRARY_API Jabra_ReturnCode Jabra_GetMACAddress(const unsigned short deviceID, NetworkInterface netIF, uint8_t* MACaddr);

/**
 * @brief Gets the diagnostic log file and writes it to a file on local file system
 * For PanaCast 50, this requires prior call to #Jabra_TriggerDiagnosticLogGeneration()
 * in order to prepare the file for download
 * 
 * @param[in] deviceID          ID for a specific device
 * @param[in] FileName          Destination file name on local file system
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return File_Not_Accessible  File is not ready on device
 * @return FileWrite_Fail       Destination file writing failed
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetDiagnosticLogFile(const unsigned short deviceID, const char* const FileName);

/**
 * @brief Type definition of function pointer to use for
 * #Jabra_TriggerDiagnosticLogGeneration.
 */
typedef void(*DiagnosticLogReadyEventHandler)(const unsigned short deviceID);

/**
 * @brief Trigger generation of diagnostic log.
 * @param[in] deviceID          ID for a specific device
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_TriggerDiagnosticLogGeneration(const unsigned short deviceID);

/**
 * @brief Registration for diagnostic log event.
 * @param[in] callback          Callback method, called when diagnosticLog event is
 * received from device. Set to NULL to disable
 * @see Jabra_TriggerDiagnosticLogGeneration
 * @see Jabra_GetDiagnosticLogFile
 */
LIBRARY_API void Jabra_RegisterDiagnosticLogCallback(DiagnosticLogReadyEventHandler const callback);

typedef enum _NetworkAuthMode
{
    AUTH_NONE = 0,
    AUTH_MSCHAPv2 = 1,
    AUTH_CERT = 2
} NetworkAuthMode;

/**
 * @brief Configure IEEE 802.1X network authentication mode for network interface.
 * @param[in] deviceID          ID for a specific device
 * @param[in] interf            Interface to be configured (Ethernet or WLAN)
 * @param[in] auth              Authentication mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetNetworkAuthenticationMode(const unsigned short deviceID, NetworkInterface interf, NetworkAuthMode auth);

/**
 * @brief Get current IEEE 802.1X network authentication mode for network interface.
 * @param[in] deviceID          ID for a specific device
 * @param[in] interf            Interface to be queried (Ethernet or WLAN)
 * @param[out] auth             Pointer to NetworkAuthMode that will receive current auth mode
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetNetworkAuthenticationMode(const unsigned short deviceID, NetworkInterface interf, NetworkAuthMode* auth);

/**
 * @brief Configure IEEE 802.1X identity for a network interface.
 * @param[in] deviceID          ID for a specific device
 * @param[in] interf            Interface to be configured (Ethernet or WLAN)
 * @param[in] username          Pointer to NULL-terminated string containing the user name or NULL pointer to clear value
 *                              Maximum length 55 characters
 * @param[in] password          Pointer to NULL-terminated string containing the password or NULL pointer to clear value
 *                              Maximum length 55 characters
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail Username or password too long
 * @return Device_WriteFail     Failed while writing to device
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetNetworkAuthenticationIdentity(const unsigned short deviceID, NetworkInterface interf, const char* username, const char* password);

#endif /* INTERFACE_NETWORK_H */
