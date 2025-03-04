/*+++
ASTRAL_DEBUG.H
Author: Antonako1
Description: Astral header file
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_DEBUG_H
#define ASTRAL_DEBUG_H

#include <ASTRAL_STDINT.H>
#include <ASTRAL_API.H>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief DEBUG: Print tree containing of element and its children
/// @param ROOT Pointer to the root element
/// @param MAX_LEVEL Maximum level depth to traverse
/// @return BOOLEAN, TRUE if successful, FALSE otherwise
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_D_TREE(AS_U0* ROOT, AS_U64 MAX_LEVEL);

/// @brief Retrieve the last error code
/// @return U64, the last error code
ASTRAL_EXPORT AS_U64 ASTRAL_D_GET_LAST_ERROR();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ASTRAL_DEBUG_H