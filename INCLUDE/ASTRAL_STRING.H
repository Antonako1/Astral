/*+++
ASTRAL_STRING.H
Author: Antonako1
Description: Astral string header file
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_STRING_H
#define ASTRAL_STRING_H

#include <ASTRAL_STDINT.H>
#include <ASTRAL_API.H>
#include <ASTRAL_MACROS.H>

/// @brief String structure
typedef struct _AS_STRING {
    AS_U64 LENGTH;          // Length of the string
    AS_U64 CAPACITY;        // Capacity of the string
    AS_U8* DATA;            // Pointer to the string data
} AS_STRING;

#if ASTRAL_PLATFORM_WINDOWS
typedef AS_U16 AS_W_STRING_T;
#elif ASTRAL_PLATFORM_LINUX
typedef AS_U32 AS_W_STRING_T;
#endif

typedef struct _AS_WSTRING {
    AS_U64 LENGTH;          // Length of the string
    AS_U64 CAPACITY;        // Capacity of the string
    #if ASTRAL_PLATFORM_WINDOWS
        AS_W_STRING_T* DATA;       // Pointer to the string data
    #elif ASTRAL_PLATFORM_LINUX
        AS_W_STRING_T* DATA;       // Pointer to the string data
    #endif
} AS_WSTRING;

/*+++
C STR FUNCTIONS
---*/
ASTRAL_EXPORT AS_U64 C_STRLEN(AS_U8* STR);
ASTRAL_EXPORT AS_U64 C_STRLEN_S(AS_U8* STR, AS_U64 SIZE);


#endif // ASTRAL_STRING_H