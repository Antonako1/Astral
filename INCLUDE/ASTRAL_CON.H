/*+++
ASTRAL_STRING.H
Author: Antonako1
Description: Astral string header file
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_CON_H
#define ASTRAL_CON_H

#include <ASTRAL_STDINT.H>
#include <ASTRAL_API.H>
#include <ASTRAL_MACROS.H>
#include <ASTRAL_MEMORY.H>
#include <ASTRAL_STRING.H>

#if ASTRAL_PLATFORM_WINDOWS
    #include <Windows.h>
#elif ASTRAL_PLATFORM_LINUX
    #include <unistd.h>
#endif

#define ASTRAL_CON_MODE_IGNORE_CTRL_C       0x00000001  // Ignore CTRL+C
#define ASTRAL_CON_MODE_LINE_WRAP           0x00000002  // Line wrap
#define ASTRAL_CON_MODE_CURSOR_VISIBLE      0x00000004  // Cursor visible
#define ASTRAL_CON_MODE_CURSOR_BLINK        0x00000008  // Cursor blink
#define ASTRAL_CON_MODE_MOUSE_INPUT         0x00000010  // Mouse input
#define ASTRAL_CON_MODE_WINDOW_INPUT        0x00000020  // Window input

typedef struct _ASTRAL_CONSOLE {
    AS_U64 WIDTH;               // Width of the console
    AS_U64 HEIGHT;              // Height of the console
    AS_U8 *BUFFER;              // Buffer for the console
    AS_U64 BUFFER_SIZE;         // Size of the buffer
    ASTRAL_M_ARENA *ARENA;      // Memory arena for the console
    #if ASTRAL_PLATFORM_WINDOWS
        HANDLE HANDLEIN;          // Handle to the console
        HANDLE HANDLEOUT;         // Handle to the console
    #elif ASTRAL_PLATFORM_LINUX
        AS_I32 HANDLEIN;          // File descriptor for the console
        AS_I32 HANDLEOUT;         // File descriptor for the console
    #endif
    AS_BOOLEAN RUNNING;         // Is the console running
    AS_U64 CON_MODE;            // Console mode
} ASTRAL_CONSOLE, *PASTRAL_CONSOLE;

typedef struct _ASTRAL_W_CONSOLE {
    AS_U64 WIDTH;               // Width of the console
    AS_U64 HEIGHT;              // Height of the console
    AS_W_STRING_T *BUFFER;      // Buffer for the console
    AS_U64 BUFFER_SIZE;         // Size of the buffer
    ASTRAL_M_ARENA *ARENA;      // Memory arena for the console
    #if ASTRAL_PLATFORM_WINDOWS
        HANDLE HANDLEIN;          // Handle to the console
        HANDLE HANDLEOUT;         // Handle to the console
    #elif ASTRAL_PLATFORM_LINUX
        AS_I32 HANDLEIN;          // File descriptor for the console
        AS_I32 HANDLEOUT;         // File descriptor for the console
    #endif
    AS_BOOLEAN RUNNING;         // Is the console running
    AS_U64 CON_MODE;            // Console mode
} ASTRAL_W_CONSOLE, *PASTRAL_W_CONSOLE;

typedef struct _ASTRAL_CONSOLE_MOUSE_EVENT {
    AS_U64 BUTTON_STATE;        // Button state
    AS_U64 BUTTONS;             // Buttons
    AS_U64 X;                   // X position
    AS_U64 Y;                   // Y position
} ASTRAL_CONSOLE_MOUSE_EVENT, *PASTRAL_CONSOLE_MOUSE_EVENT;
 
typedef struct _ASTRAL_CONSOLE_KEY_EVENT {
    AS_U64 KEY_STATE;           // Key state
    AS_U64 KEY_CODE;            // Key code
    AS_U64 CHAR;                // Character
} ASTRAL_CONSOLE_KEY_EVENT, *PASTRAL_CONSOLE_KEY_EVENT;

typedef struct _ASTRAL_CONSOLE_RESIZE_EVENT {
    AS_U64 WIDTH;               // Width
    AS_U64 HEIGHT;              // Height
} ASTRAL_CONSOLE_RESIZE_EVENT, *PASTRAL_CONSOLE_RESIZE_EVENT;

typedef struct _ASTRAL_CONSOLE_MENU_EVENT {
    AS_U64 MENU_ID;             // Menu ID
} ASTRAL_CONSOLE_MENU_EVENT, *PASTRAL_CONSOLE_MENU_EVENT;

typedef struct _ASTRAL_CONSOLE_FOCUS_EVENT {
    AS_U64 FOCUS_STATE;         // Focus state
} ASTRAL_CONSOLE_FOCUS_EVENT, *PASTRAL_CONSOLE_FOCUS_EVENT;

typedef struct _ASTRAL_CONSOLE_EVENT {
    AS_U64 EVENTS_READ;         // Events read
    AS_U64 EVENT_TYPE;          // Event type
    AS_U64 EVENT_SIZE;          // Size of the event
    AS_U8* EVENT_DATA;          // Event data
    ASTRAL_CONSOLE_MOUSE_EVENT  _MOUSE_EVENT;
    ASTRAL_CONSOLE_KEY_EVENT    _KEY_EVENT;
    ASTRAL_CONSOLE_RESIZE_EVENT _RESIZE_EVENT;
    ASTRAL_CONSOLE_MENU_EVENT   _MENU_EVENT;
    ASTRAL_CONSOLE_FOCUS_EVENT  _FOCUS_EVENT;
} ASTRAL_CONSOLE_EVENT, *PASTRAL_CONSOLE_EVENT;

ASTRAL_EXPORT AS_U0 ASTRAL_CON_GET_EVENT(ASTRAL_CONSOLE* CONSOLE, ASTRAL_CONSOLE_EVENT* EVENT);

/// @brief Creates a new console
/// @param ARENA Memory arena
/// @return ASTRAL_CONSOLE
ASTRAL_EXPORT ASTRAL_CONSOLE ASTRAL_CON_CREATE(ASTRAL_M_ARENA* ARENA);

/// @brief Clears the console screen
/// @param CONSOLE Console to clear
/// @return U16, error code
ASTRAL_EXPORT AS_U16 ASTRAL_CON_CLEAR(ASTRAL_CONSOLE* CONSOLE);

/// @brief Adds a string to the console buffer
/// @param CONSOLE Console to add to
/// @param STRING String to add
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_ADD_TO_BUFFER(ASTRAL_CONSOLE* CONSOLE, AS_STRING STRING);

/// @brief Adds a wide string to the console buffer
/// @param CONSOLE Console to add to
/// @param STRING String to add
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_W_ADD_TO_BUFFER(ASTRAL_W_CONSOLE* CONSOLE, AS_WSTRING STRING);

ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_WRITE_BUFFER(ASTRAL_CONSOLE* CONSOLE);

ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_WRITE_STRING(ASTRAL_CONSOLE* CONSOLE, AS_U8* STRING);
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_W_WRITE_STRING(ASTRAL_W_CONSOLE* CONSOLE, AS_W_STRING_T* STRING);

/// @brief Applies console modes
/// @param CONSOLE Console to apply modes to
/// @param MODES Modes to apply
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_APPLY_MODES(ASTRAL_CONSOLE* CONSOLE, AS_U64 MODES);

#define ASTRAL_CON_EVENT_KEY         0x00000001
#define ASTRAL_CON_EVENT_MOUSE       0x00000002
#define ASTRAL_CON_EVENT_RESIZE      0x00000004
#define ASTRAL_CON_EVENT_MENU        0x00000008
#define ASTRAL_CON_EVENT_FOCUS       0x00000010
#define ASTRAL_CON_EVENT_NO_EVENT    0x00000020

#endif // ASTRAL_CON_H