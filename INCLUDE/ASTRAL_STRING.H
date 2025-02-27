/*+++
ASTRAL_STRING.H
Author: Antonako1
Description: Astral string header file
             Contains string functions, structures and definitions
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

/// @brief Gets the length of a string
/// @param STR String to get the length of
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRLEN(AS_U8* STR);

/// @brief Gets the length of a string
/// @param STR String to get the length of
/// @param SIZE Size of the string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRLEN_S(AS_U8* STR, AS_U64 SIZE);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @return U64, are the strings equal
ASTRAL_EXPORT AS_U64 C_STRCMP(AS_U8* STR1, AS_U8* STR2);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @param SIZE Size of STR2
/// @return U64, are the strings equal
ASTRAL_EXPORT AS_U64 C_STRCMP_S(AS_U8* STR1, AS_U8* STR2, AS_U64 SIZE);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCPY(AS_U8* DEST, AS_U8* SRC);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCPY_S(AS_U8* DEST, AS_U8* SRC, AS_U64 SIZE);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCAT(AS_U8* DEST, AS_U8* SRC);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCAT_S(AS_U8* DEST, AS_U8* SRC, AS_U64 SIZE);

/*+++
ASTRAL STR FUNCTIONS
---*/

/// @brief Returns the length of the string
/// @param STR String to get the length of
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STRLEN(AS_STRING* STR);

/// @brief Creates a new string
/// @param SIZE Size of the string
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_STRING* ASTRAL_STR_CREATE(AS_U64 SIZE);

/// @brief Creates a new string with data
/// @param SIZE Size of the string
/// @param DATA Text data
/// @param DATA_SIZE Size of the data
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_STRING* ASTRAL_STR_CREATE(AS_U64 SIZE, AS_U8* DATA, AS_U64 DATA_SIZE);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_STRING* SRC);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_U8* SRC, AS_U64 SIZE);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_APPEND(AS_STRING* DEST, AS_STRING* SRC);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_APPEND(AS_STRING* DEST, AS_U8* SRC, AS_U64 SIZE);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @return BOOLEAN, are the strings equal
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_STR_CMP(AS_STRING* STR1, AS_STRING* STR2);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @param SIZE Size of STR2
/// @return BOOLEAN, are the strings equal
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_STR_CMP(AS_STRING* STR1, AS_U8* STR2, AS_U64 SIZE);

/// @brief Frees a string
/// @param STR String to free
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_STR_FREE(AS_STRING* STR);

#endif // ASTRAL_STRING_H