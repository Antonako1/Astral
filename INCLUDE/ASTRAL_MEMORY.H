/*+++
ASTRAL_MEMORY.H
Author: Antonako1
Description: Astral memory header file
Licensed under the MIT License
---*/
#pragma once
#ifndef ASTRAL_MEMORY_H
#define ASTRAL_MEMORY_H

#include <ASTRAL_STDINT.H>
#include <ASTRAL_API.H>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_M_ALLOC")
/// @brief Allocates a memory block
/// @param SIZE Size of the memory block
/// @return U0, pointer to the memory block
ASTRAL_EXPORT AS_U0 *ASTRAL_M_ALLOC(AS_U64 SIZE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_M_REALLOC")
/// @brief Reallocates a memory block
/// @param PTR Pointer to the memory block
/// @param SIZE New size of the memory block
/// @return U0, pointer to the new memory block
ASTRAL_EXPORT AS_U0 *ASTRAL_M_REALLOC(AS_U0 *PTR, AS_U64 SIZE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_M_FREE")
/// @brief Frees a memory block
/// @param PTR Pointer to the memory block
/// @return U0
ASTRAL_EXPORT AS_U0 ASTRAL_M_FREE(AS_U0 *PTR);

/// @brief Copies memory from one block to another
/// @param DEST Pointer to the destination block
/// @param SRC Pointer to the source block
/// @param NUM Number of bytes to copy
/// @return AS_U0*, pointer to the destination block
ASTRAL_EXPORT AS_U0 *ASTRAL_M_COPY(AS_U0 *DEST, AS_U0 *SRC, AS_U64 NUM);

/// @brief Sets memory to a value.
/// @param PTR Pointer to the memory block
/// @param VALUE Value to set the memory to
/// @param NUM Number of bytes to set from start of the block.
/// @return AS_U0*, pointer to the memory block
ASTRAL_EXPORT AS_U0 *ASTRAL_M_SET(AS_U0 *PTR, AS_U8 VALUE, AS_U64 NUM);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ASTRAL_MEMORY_H