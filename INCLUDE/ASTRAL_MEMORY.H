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

// Memory arena
typedef struct _ASTRAL_M_ARENA {
    AS_U0* NEXT_BLOCK;                 // Next free block
    AS_U64 SIZE;                       // Size of the memory arena
    AS_U8 *MEMORY;                     // Pointer to the memory
} ASTRAL_M_ARENA, *PASTRAL_M_ARENA;

/// @brief Allocate memory arena
/// @param SIZE Size of the memory arena
/// @param MEMORY Pointer to the memory
/// @return ASTRAL_M_ARENA
ASTRAL_EXPORT ASTRAL_M_ARENA ASTRAL_M_ARENA_ALLOC(AS_U64 SIZE, AS_U0* MEMORY);

/// @brief Get minimum recommended size for memory arena
/// @return U64, minimum size for memory arena
ASTRAL_EXPORT AS_U64 ASTRAL_M_MIN_SIZE(AS_U0);


#endif // ASTRAL_MEMORY_H