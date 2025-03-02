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

#define WIN_LINUX_OTHER(x, y, z) ASTRAL_HELP_MACRO_WLO(x, y, z)

#if ASTRAL_PLATFORM_WINDOWS
#   define ASTRAL_HELP_MACRO_WLO(x, y, z) x
#elif ASTRAL_PLATFORM_LINUX
#   define ASTRAL_HELP_MACRO_WLO(x, y, z) y
#else
#   define ASTRAL_HELP_MACRO_WLO(x, y, z) z
#endif

/// @brief Converts a C string to an AS_CHAR string
#define C_STR_TO_AS_CHAR(STR) (AS_CHAR*)STR
#define CSTR_TO_ACH(STR) C_STR_TO_AS_CHAR(STR)
#define CS_AS(STR) C_STR_TO_AS_CHAR(STR)

/// @brief Converts a C string to an AS_WCHAR string
#define C_STR_TO_AS_WCHAR(STR) (AS_WCHAR*)STR
#define CSTR_TO_AWCH(STR) C_STR_TO_AS_WCHAR(STR)
#define CWS_AS(STR) C_STR_TO_AS_WCHAR(STR)

#define STR_TO_VP(STR) (AS_VPTR)STR
#define TYPE_TO_VP(TYPE) (AS_VPTR)TYPE

typedef AS_U8 AS_CHAR;

/// @brief Wide character. 16 bits on Windows, 32 bits on Linux, 32 bits on undefined platforms
typedef WIN_LINUX_OTHER(AS_U16, AS_U32, AS_U32) AS_WCHAR;
#define AS_WCHAR_SIZE WIN_LINUX_OTHER(sizeof(AS_U16), sizeof(AS_U32), sizeof(AS_U32))
#define AS_WCHARMAX WIN_LINUX_OTHER(U16_MAX, U32_MAX, U32_MAX)
#define AS_WCHARMIN WIN_LINUX_OTHER(U16_MIN, U32_MIN, U32_MIN)

/// @brief String structure. Turns into a wide string on Windows,
#define AS_WCH(STR) WIN_LINUX_OTHER(L##STR, L##STR, L##STR)

/// @brief String structure
typedef struct _AS_STRING {
    AS_U64 LENGTH;          // Length of the string
    AS_CHAR* DATA;          // Pointer to the string data
} AS_STRING, *PAS_STRING;


typedef struct _AS_WSTRING {
    AS_U64 LENGTH;          // Length of the string
    AS_WCHAR* DATA;       // Pointer to the string data
} AS_WSTRING, *PAS_WSTRING;

/*+++
C STR FUNCTIONS
---*/

/// @brief Gets the length of a string
/// @param STR String to get the length of
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRLEN(AS_CHAR* STR);

/// @brief Gets the length of a string
/// @param STR String to get the length of
/// @param SIZE Size of the string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRLEN_S(AS_CHAR* STR, AS_U64 SIZE);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @return U64, are the strings equal
ASTRAL_EXPORT AS_U64 C_STRCMP(AS_CHAR* STR1, AS_CHAR* STR2);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @param SIZE Size of STR2
/// @return U64, are the strings equal
ASTRAL_EXPORT AS_U64 C_STRCMP_S(AS_CHAR* STR1, AS_CHAR* STR2, AS_U64 SIZE);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCPY(AS_CHAR* DEST, AS_CHAR* SRC);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCPY_S(AS_CHAR* DEST, AS_CHAR* SRC, AS_U64 SIZE);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCAT(AS_CHAR* DEST, AS_CHAR* SRC);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 C_STRCAT_S(AS_CHAR* DEST, AS_CHAR* SRC, AS_U64 SIZE);

/// @brief Finds a character in a string
/// @param STR String to search
/// @param C Character to find
/// @param N Selects the Nth character. 0 for the first
/// @return U0*, pointer to the character
ASTRAL_EXPORT AS_U0 *C_STRCHR(AS_CHAR* STR, AS_CHAR C, AS_U64 N);


/*+++
WIDE C STR FUNCTIONS
---*/

/// @brief Gets the length of a wide string
/// @param STR String to get the length of
/// @return U64, length of the string
AS_U64 C_WSTRLEN(AS_WCHAR* STR);

/// @brief Gets the length of a wide string
/// @param STR String to get the length of
/// @param SIZE Size of the string
/// @return U64, length of the string
AS_U64 C_WSTRLEN_S(AS_WCHAR* STR, AS_U64 SIZE);

/// @brief Compares two wide strings
/// @param STR1 First string
/// @param STR2 Second string
/// @return U64, are the strings equal
AS_U64 C_WSTRCMP(AS_WCHAR* STR1, AS_WCHAR* STR2);

/// @brief Compares two wide strings
/// @param STR1 First string
/// @param STR2 Second string
/// @param SIZE Size of STR2
/// @return U64, are the strings equal
AS_U64 C_WSTRCMP_S(AS_WCHAR* STR1, AS_WCHAR* STR2, AS_U64 SIZE);

/// @brief Copies a wide string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
AS_U64 C_WSTRCPY(AS_WCHAR* DEST, AS_WCHAR* SRC);

/// @brief Copies a wide string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
AS_U64 C_WSTRCPY_S(AS_WCHAR* DEST, AS_WCHAR* SRC, AS_U64 SIZE);

/// @brief Appends a wide string to another wide string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
AS_U64 C_WSTRCAT(AS_WCHAR* DEST, AS_WCHAR* SRC);

/// @brief Appends a wide string to another wide string
/// @param DEST Destination string
/// @param SRC Source string
/// @param SIZE Size of SRC
/// @return U64, length of the string
AS_U64 C_WSTRCAT_S(AS_WCHAR* DEST, AS_WCHAR* SRC, AS_U64 SIZE);

/// @brief Finds a character in a wide string
/// @param STR String to search
/// @param C Character to find
/// @param N Selects the Nth character. 0 for the first
/// @return U0*, pointer to the character
AS_U0 *C_WSTRCHR(AS_WCHAR* STR, AS_WCHAR C, AS_U64 N);

/*+++
ASTRAL STR FUNCTIONS
---*/

/// @brief Returns the length of the string
/// @param STR String to get the length of
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STRLEN(AS_STRING* STR);

/// @brief Creates a new string. Free with ASTRAL_STR_FREE
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_STRING* ASTRAL_STR_CREATE();

/// @brief Creates a new string with data. Free with ASTRAL_STR_FREE
/// @param DATA Text data
/// @param MAX_SIZE Maximum size of the string. Use against buffer overflows 
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_STRING* ASTRAL_STR_CREATE_EX(AS_CHAR* DATA, AS_U64 MAX_SIZE);

/// @brief Duplicates a string
/// @param STR String to duplicate
/// @return STRING, pointer to the duplicated string
ASTRAL_EXPORT AS_STRING* ASTRAL_STR_DUPLICATE(AS_STRING* STR);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_STRING* SRC);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_COPY_CH(AS_STRING* DEST, AS_CHAR* SRC, AS_U64 SIZE);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_APPEND(AS_STRING* DEST, AS_STRING* SRC);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_STR_APPEND_CH(AS_STRING* DEST, AS_CHAR* SRC, AS_U64 SIZE);

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
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_STR_CMP_CH(AS_STRING* STR1, AS_CHAR* STR2, AS_U64 SIZE);

/// @brief Frees a string
/// @param STR String to free
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_STR_FREE(AS_STRING* STR);

/// @brief Finds a character in a string
/// @param STR String to search
/// @param C Character to find
/// @param N Selects the Nth character. 0 for the first
/// @return U0*, pointer to the character
ASTRAL_EXPORT AS_U0 *ASTRAL_STR_STRCHR(AS_STRING* STR, AS_CHAR C, AS_U64 N);


/*+++
WIDE ASTRAL STR FUNCTIONS
---*/

/// @brief Returns the length of the string
/// @param STR String to get the length of
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_WSTRLEN(AS_WSTRING* STR);

/// @brief Creates a new string. Free with ASTRAL_WSTR_FREE
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_WSTRING* ASTRAL_WSTR_CREATE();

/// @brief Creates a new string with data. Free with ASTRAL_WSTR_FREE
/// @param DATA Text data
/// @param MAX_SIZE Max size of data. Used against buffer overflows
/// @return STRING, pointer to the string
ASTRAL_EXPORT AS_WSTRING* ASTRAL_WSTR_CREATE_EX(AS_WCHAR* DATA, AS_U64 MAX_SIZE);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_WSTR_COPY(AS_WSTRING* DEST, AS_WSTRING* SRC);

/// @brief Copies a string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_WSTR_COPY_WCH(AS_WSTRING* DEST, AS_WCHAR* SRC, AS_U64 SIZE);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_WSTR_APPEND(AS_WSTRING* DEST, AS_WSTRING* SRC);

/// @brief Appends a string to another string
/// @param DEST Destination string
/// @param SRC Source string
/// @return U64, length of the string
ASTRAL_EXPORT AS_U64 ASTRAL_WSTR_APPEND_WCH(AS_WSTRING* DEST, AS_WCHAR* SRC, AS_U64 SIZE);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @return BOOLEAN, are the strings equal
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_WSTR_CMP(AS_WSTRING* STR1, AS_WSTRING* STR2);

/// @brief Compares two strings
/// @param STR1 First string
/// @param STR2 Second string
/// @param SIZE Size of STR2
/// @return BOOLEAN, are the strings equal
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_WSTR_CMP_WCH(AS_WSTRING* STR1, AS_WCHAR* STR2, AS_U64 SIZE);

/// @brief Frees a string
/// @param STR String to free
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_WSTR_FREE(AS_WSTRING* STR);

/// @brief Finds a character in a wide string
/// @param STR String to search
/// @param C Character to find
/// @param N Selects the Nth character. 0 for the first
/// @return U0*, pointer to the character
ASTRAL_EXPORT AS_U0 *ASTRAL_WSTR_STRCHR(AS_WSTRING* STR, AS_WCHAR C, AS_U64 N);

/// @brief Duplicates a string
/// @param STR String to duplicate
/// @return STRING, pointer to the duplicated string
ASTRAL_EXPORT AS_WSTRING* ASTRAL_WSTR_DUPLICATE(AS_WSTRING* STR);

/*+++
Use for functions that require:
    (STR, SIZE) or something similar
---*/
#define STR_MAX_COMBO(STR) CS_AS(STR), C_STRLEN(CS_AS(STR))
#define WSTR_MAX_COMBO(STR) CWS_AS(STR), C_WSTRLEN(CWS_AS(STR))

#endif // ASTRAL_STRING_H