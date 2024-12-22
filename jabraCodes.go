package main

import "fmt"

type errorStatusCode int

type ReturnCodeError struct {
	code    int
	message string
}

type JabraErrorStatusCode struct {
	code    errorStatusCode
	message string
}

func (e *JabraErrorStatusCode) Error() string {
	return fmt.Sprintf("Jabra_ErrorStatus %d: %s", e.code, e.message)
}

func (e *ReturnCodeError) Error() string {
	return fmt.Sprintf("Error %d: %s", e.code, e.message)
}

var (
	ErrReturnOk                        = &ReturnCodeError{0, "Success"}
	ErrDeviceUnknown                   = &ReturnCodeError{1, "The device is not known"}
	ErrDeviceInvalid                   = &ReturnCodeError{2, "The device is invalid"}
	ErrNotSupported                    = &ReturnCodeError{3, "The device is not supported"}
	ErrReturnParameterFail             = &ReturnCodeError{4, "One or more parameters are wrong"}
	ErrProtectedSettingWrite           = &ReturnCodeError{5, "The setting you are attempting to write is protected"}
	ErrNoInformation                   = &ReturnCodeError{6, "No info available"}
	ErrNetworkRequestFail              = &ReturnCodeError{7, "Network failure"}
	ErrDeviceWriteFail                 = &ReturnCodeError{8, "Failed writing to the device"}
	ErrDeviceReadFails                 = &ReturnCodeError{9, "Failed reading from the device"}
	ErrNoFactorySupported              = &ReturnCodeError{10, "Factory reset is not supported or allowed"}
	ErrSystemError                     = &ReturnCodeError{11, "System error"}
	ErrDeviceBadState                  = &ReturnCodeError{12, "The device is in a bad state"}
	ErrFileWriteFail                   = &ReturnCodeError{13, "Failed writing to file"}
	ErrFileAlreadyExists               = &ReturnCodeError{14, "The file already exists"}
	ErrFileNotAccessible               = &ReturnCodeError{15, "The file is not accessible"}
	ErrFirmwareUpToDate                = &ReturnCodeError{16, "Firmware is up-to-date"}
	ErrFirmwareAvailable               = &ReturnCodeError{17, "Firmware is available"}
	ErrReturnAsync                     = &ReturnCodeError{18, "Asynch operation has started in the background"}
	ErrInvalidAuthorization            = &ReturnCodeError{19, "Authorization failure"}
	ErrFWUApplicationNotAvailable      = &ReturnCodeError{20, "The FW updater application is unavailable"}
	ErrDeviceAlreadyConnected          = &ReturnCodeError{21, "The device is already connected"}
	ErrDeviceNotConnected              = &ReturnCodeError{22, "The device is not connected"}
	ErrCannotClearDeviceConnected      = &ReturnCodeError{23, "Unable to clear, device is connected"}
	ErrDeviceRebooted                  = &ReturnCodeError{24, "The device rebooted"}
	ErrUploadAlreadyInProgress         = &ReturnCodeError{25, "Upload is already in progress"}
	ErrDownloadAlreadyInProgress       = &ReturnCodeError{26, "Download is already in progress"}
	ErrSdkTooOldForFwUpdate            = &ReturnCodeError{27, "The Jabra SDK is too old to update the selected firmware"}
	ErrNoOtaUpdateSupport              = &ReturnCodeError{28, "Firmware update through OTA is not supported for this device"}
	ErrNonJabraDeviceDetectionDisabled = &ReturnCodeError{29, "Non Jabra device detection is disabled"}
	ErrDeviceLock                      = &ReturnCodeError{30, "Device is locked"}
	ErrDeviceNotLock                   = &ReturnCodeError{31, "Device is not locked"}
	ErrReturnTimeout                   = &ReturnCodeError{32, "Operation timed out"}

	ErrNoError                   = &JabraErrorStatusCode{0, "No Error"}
	ErrSSLError                  = &JabraErrorStatusCode{1, "SSL Handshake failed. Please contact your administrator"}
	ErrCertError                 = &JabraErrorStatusCode{2, "Failed to Authenticate Server Certificate. Please contact your administrator"}
	ErrNetworkError              = &JabraErrorStatusCode{3, "Unable to download the files. Please check Internet connection and reconnect the device"}
	ErrDownloadError             = &JabraErrorStatusCode{4, "Setting files download failed. Please contact your administrator"}
	ErrParseError                = &JabraErrorStatusCode{5, "Unable to retrieve device settings. Please reconnect device"}
	ErrOtherError                = &JabraErrorStatusCode{6, "Unknown error. Please contact your administrator"}
	ErrDeviceInfoError           = &JabraErrorStatusCode{7, "Unable to retrieve device information. Please reconnect device"}
	ErrFileNotAccessibleStatus   = &JabraErrorStatusCode{8, "File is not accessible"}
	ErrFileNotCompatible         = &JabraErrorStatusCode{9, "File is not compatible for the device"}
	ErrDeviceNotFound            = &JabraErrorStatusCode{10, "The specified device is not found"}
	ErrParameterFail             = &JabraErrorStatusCode{11, "Incorrect parameters"}
	ErrAuthorizationFailed       = &JabraErrorStatusCode{12, "Authorization failed"}
	ErrFileNotAvailable          = &JabraErrorStatusCode{13, "Files are not available for the device. Please check internet connection and reconnect the device"}
	ErrConfigParseError          = &JabraErrorStatusCode{14, "Config XML parse error"}
	ErrSetSettingsFail           = &JabraErrorStatusCode{15, "Error in applying settings"}
	ErrDeviceReboot              = &JabraErrorStatusCode{16, "Device will reboot due to change in the settings"}
	ErrDeviceReadFail            = &JabraErrorStatusCode{17, "Unable to read settings from the device"}
	ErrDeviceNotReady            = &JabraErrorStatusCode{18, "The device is not ready"}
	ErrFilePartiallyCompatible   = &JabraErrorStatusCode{19, "Partial Settings loaded"}
	ErrSdkTooOldForFwUpdateError = &JabraErrorStatusCode{20, "The Jabra SDK is too old to update the selected firmware"}
	ErrUpdateIsNotReady          = &JabraErrorStatusCode{21, "The resource is not yet ready to be updated"}
)

func returnCode(code int) error {
	switch code {
	case 0:
		return nil
	case 1:
		return ErrDeviceUnknown
	case 2:
		return ErrDeviceInvalid
	case 3:
		return ErrNotSupported
	case 4:
		return ErrReturnParameterFail
	case 5:
		return ErrProtectedSettingWrite
	case 6:
		return ErrNoInformation
	case 7:
		return ErrNetworkRequestFail
	case 8:
		return ErrDeviceWriteFail
	case 9:
		return ErrDeviceReadFails
	case 10:
		return ErrNoFactorySupported
	case 11:
		return ErrSystemError
	case 12:
		return ErrDeviceBadState
	case 13:
		return ErrFileWriteFail
	case 14:
		return ErrFileAlreadyExists
	case 15:
		return ErrFileNotAccessible
	case 16:
		return ErrFirmwareUpToDate
	case 17:
		return ErrFirmwareAvailable
	case 18:
		return ErrReturnAsync
	case 19:
		return ErrInvalidAuthorization
	case 20:
		return ErrFWUApplicationNotAvailable
	case 21:
		return ErrDeviceAlreadyConnected
	case 22:
		return ErrDeviceNotConnected
	case 23:
		return ErrCannotClearDeviceConnected
	case 24:
		return ErrDeviceRebooted
	case 25:
		return ErrUploadAlreadyInProgress
	case 26:
		return ErrDownloadAlreadyInProgress
	case 27:
		return ErrSdkTooOldForFwUpdate
	case 28:
		return ErrNoOtaUpdateSupport
	case 29:
		return ErrNonJabraDeviceDetectionDisabled
	case 30:
		return ErrDeviceLock
	case 31:
		return ErrDeviceNotLock
	case 32:
		return ErrReturnTimeout
	default:
		return &ReturnCodeError{code, "Unknown return code"}
	}
}

func checkErrorStatus(code errorStatusCode) error {
	switch code {
	case 0:
		return nil
	case 1:
		return ErrSSLError
	case 2:
		return ErrCertError
	case 3:
		return ErrNetworkError
	case 4:
		return ErrDownloadError
	case 5:
		return ErrParseError
	case 6:
		return ErrOtherError
	case 7:
		return ErrDeviceInfoError
	case 8:
		return ErrFileNotAccessible
	case 9:
		return ErrFileNotCompatible
	case 10:
		return ErrDeviceNotFound
	case 11:
		return ErrParameterFail
	case 12:
		return ErrAuthorizationFailed
	case 13:
		return ErrFileNotAvailable
	case 14:
		return ErrConfigParseError
	case 15:
		return ErrSetSettingsFail
	case 16:
		return ErrDeviceReboot
	case 17:
		return ErrDeviceReadFail
	case 18:
		return ErrDeviceNotReady
	case 19:
		return ErrFilePartiallyCompatible
	case 20:
		return ErrSdkTooOldForFwUpdateError
	case 21:
		return ErrUpdateIsNotReady
	default:
		return &JabraErrorStatusCode{code, "Unknown error status"}
	}
}
