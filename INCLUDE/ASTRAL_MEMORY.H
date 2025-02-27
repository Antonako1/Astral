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

#endif // ASTRAL_MEMORY_H