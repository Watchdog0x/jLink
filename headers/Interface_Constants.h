#ifndef INTERFACE_CONSTANTS_H
#define INTERFACE_CONSTANTS_H

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
 * @file Interface_Constants.h
 * @brief Defines the interface for querying constants defined for a specific
 * device.
 *
 * The constants can be of different types: integers, booleans, strings, as
 * well as composed types: structs and lists.
 *
 * The purpose of the constants are to supply values that are handy for
 * applications, but not directly required--and hence not available--by the
 * devices. The constants are accessed by keys, which are simply strings, and
 * these are obtained from the documentation.
 *
 * @note A key will never be reused for a constant of a different type, and the
 * key will mean the same for all devices where it is defined.
 */

/**
 * @defgroup group_jaxon Device Constants
 *
 * The basic element of jabra constants are the Jabra_Const type, which is
 * either null or a handle to a value of some type.
 *
 * The Jabra_Const type can be used directly in a bool-context and will be
 * false only if it is the null value.
 *
 * In an attempt to keep memory management to a minimum, the life cycle of a
 * Jabra_Const object is controlled by the root. The root is the object
 * returned by Jabra_GetConst(). The root objects must be released by invoking
 * Jabra_ReleaseConst(), and this invalidates all Jabra_Const references to
 * substructures, as well as any const char* returned from any of those
 * objects.
 *
 */

/// @addtogroup group_jaxon
/// @{

/** @brief A handle for a Jabra constant. */
typedef void* Jabra_Const;

/**
 * @brief A base type for the collection of Jabra constants associated with a
 * device.
 *
 * Jabra_Constants are only used for defining a pointer.
 */
typedef void Jabra_Constants;

/**
 * @brief       Get the constants defined for a device
 * @param[in]   deviceID ID for the specific device
 * @return a pointer that can be queried for values by key, or null if the
 * device can not be found.
 *
 *
 * In case the constant has no value for the device, or even if the device is
 * not found, Jabra_GetConst will return a Jabra_Const with the value null.
 * This can then be checked by using one of the type verification operations.
 *
 * The returned value must be released, once data has been extracted, see
 * @ref Jabra_ReleaseConst. If the pointer is null it is still perfectly ok to
 * release it.
 *
 * The safe way to use a Jabra_Constants collection is:
 *   -# Obtain the Jabra_Constants by calling Jabra_GetConstants().
 *   -# Obtain the Jabra_Const by calling Jabra_GetConst().
 *   -# Extract data, anything that needs to be kept should be copied to your
 *   own constructs.
 *   -# Extract and use more constants, any number of iterations.
 *   -# Allow the release of the internal data by invoking Jabra_ReleaseConst().
 *
 * @sa @ref group_jaxon
 * @sa @wrap{Jabra_GetConstants}
 */
LIBRARY_API Jabra_Constants* Jabra_GetConstants(unsigned short deviceID);

/**
 * @brief       Get a Jabra_Const value from the Jabra_Constants collection.
 * @param[in]   constants the colloctions to find the value in
 * @param[in]   key       the key for the constant
 * @return the value of the constant, possible the null value
 *
 * In case the constant has no value for the device, Jabra_GetConst will return
 * a Jabra_Const with the value null.
 *
 * See also: @ref group_jaxon
 */
LIBRARY_API Jabra_Const Jabra_GetConst(Jabra_Constants* constants, const char* key);

/**
 * @brief Release the data inside a Jabra_Const. This will invalidate any
 * pointers to embedded strings and Jabra_Const subelement.
 * @param[in] constants The collection to release
 * 
 * @note After the release of a collection, all references to elements inside
 * the collection is invalidated, and should not be used.
 */
LIBRARY_API void Jabra_ReleaseConst(Jabra_Constants* constants);

/** @brief Returns true if argument is an integer. */
LIBRARY_API bool Jabra_IsInt(Jabra_Const);
/** @brief Returns true if argument is a boolean. */
LIBRARY_API bool Jabra_IsBool(Jabra_Const);
/** @brief Returns true if argument is a string. */
LIBRARY_API bool Jabra_IsString(Jabra_Const);
/** @brief Returns true if argument is a struct. */
LIBRARY_API bool Jabra_IsStruct(Jabra_Const);
/** @brief Returns true if argument is a list. */
LIBRARY_API bool Jabra_IsList(Jabra_Const);

/**
 * @brief Interprets a Jabra_Const as an integer.
 * @return the integer interpretation.
 *
 * Depending on the content of the Jabra_Const the interpretation is:
 * - integer: the value of the integer
 * - boolean: 0 for false, 1 for true
 * - list: the length of the list
 * - string: the length of the string
 * - null: 0
 * - struct: 0
 */
LIBRARY_API int Jabra_AsInt(Jabra_Const);

/**
 * @brief Interprets a Jabra_Const as a boolean.
 * @return the boolean interpretation.
 *
 * Depending on the content of the Jabra_Const the interpretation is:
 * - integer: false for 0, true otherwise.
 * - boolean: the value of the boolean.
 * - list: false if list is empty, true otherwise.
 * - string: false if length of string is 0, true otherwise.
 * - null: false.
 * - struct: false.
 */
LIBRARY_API bool Jabra_AsBool(Jabra_Const);

/**
 * @brief Gets the string content of a Jabra_Const
 * @return the value if the content is a string, null otherwise.
 */
LIBRARY_API const char* Jabra_AsString(Jabra_Const);

/**
 * @brief Get a field from a Jabra_Const struct.
 * @return the element if jstruct is a struct object and has a field registered
 * under id, null otherwise.
 *
 */
LIBRARY_API Jabra_Const Jabra_GetField(Jabra_Const jstruct, const char* id);

/**
 * @brief Get an element by index from a Jabra_Const list.
 * @return the element if list is a list object and idx is in range, null
 * otherwise.
 *
 */
LIBRARY_API Jabra_Const Jabra_ListElement(Jabra_Const list, int idx);

/// @}
#endif
