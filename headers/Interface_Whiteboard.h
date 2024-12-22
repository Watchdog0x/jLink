#ifndef INTERFACE_WHITEBOARD_H
#define INTERFACE_WHITEBOARD_H

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
 * @file Interface_Whiteboard.h
 * @brief Defines the whiteboard interfaces for the Jabra SDK.
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
 * Whiteboard position represented by the X and Y pixel coordinates of each corner.
 */
typedef struct _WhiteboardPosition
{
    uint16_t  lowerLeftCornerX;
    uint16_t  lowerLeftCornerY;
    uint16_t  lowerRightCornerX;
    uint16_t  lowerRightCornerY;
    uint16_t  upperRightCornerX;
    uint16_t  upperRightCornerY;
    uint16_t  upperLeftCornerX;
    uint16_t  upperLeftCornerY;
} Jabra_WhiteboardPosition;

/**
 * @brief       For a video device that supports whiteboard, sets the positions in pixels of a whiteboard's corners. 
 * @param[in]   deviceID ID for the specific device
 * @param[in]   whiteboardNumber    The whiteboard 'index'. Currently only one whiteboard supported,
                                    so this should be 0.
 * @param[in]   whiteboardPosition  Pointer to a struct containing the X and Y coordinates for each corner in
                                    pixels. The coordinates must be valid, which means that they should
                                    meet these conditions: lowerLeftCornerX < lowerRightCornerX,
                                    upperLeftCornerX < upperRightCornerX, upperLeftCornerY < lowerLeftCornerY
                                    and upperRightCornerY < lowerRightCornerY. Bounds are TBD. Cannot be NULL.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_WriteFail     Failed while writing to device
 * @sa @wrap{Jabra_SetWhiteboardPosition}
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetWhiteboardPosition(unsigned short deviceID, uint8_t whiteboardNumber, const Jabra_WhiteboardPosition* whiteboardPosition);

/**
 * @brief       For a video device that supports whiteboard, gets the positions in pixels of a whiteboard's corners.
 * @param[in]   deviceID ID for the specific device
 * @param[in]   whiteboardNumber    The whiteboard 'index' for multiple whiteboards support. Currently only
                                    one whiteboard is supported, so this should be 0.
 * @param[out]  whiteboardPosition  Pointer to a struct that will be filled with the X and Y
                                    coordinates for each corner in pixels. Bounds are TBD. Cannot be NULL.
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Return_ParameterFail A NULL pointer was passed
 * @return Device_ReadFails     Failed while reading from device
 * @sa @wrap{Jabra_GetWhiteboardPosition}
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetWhiteboardPosition(unsigned short deviceID, uint8_t whiteboardNumber, Jabra_WhiteboardPosition* whiteboardPosition);

/**
 * @brief       For a video device, set whether the main stream shows the whiteboard.
 * @param[in]   deviceID ID for the specific device
 * @param[in]   enable Enable status
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_WriteFail     Failed while writing to device
 * @see    Jabra_GetWhiteboardOnMainStream
 */
LIBRARY_API Jabra_ReturnCode Jabra_SetWhiteboardOnMainStream(unsigned short deviceID, bool enable);

/**
 * @brief       For a video device, get whether the main stream shows the whiteboard.
 * @param[in]   deviceID ID for the specific device
 * @param[out]  enable Enable status
 * @return Return_Ok            Call was successful
 * @return Device_Unknown       deviceID is unknown
 * @return Not_Supported        Functionality is not supported on this device
 * @return Device_ReadFails     Failed while reading from device
 * @return Return_ParameterFail A NULL pointer was passed
 * @see    Jabra_SetWhiteboardOnMainStream
 */
LIBRARY_API Jabra_ReturnCode Jabra_GetWhiteboardOnMainStream(unsigned short deviceID, bool* enable);

#endif /* INTERFACE_WHITEBOARD_H */
