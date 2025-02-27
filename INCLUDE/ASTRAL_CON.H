/*+++
ASTRAL_CON.H
Author: Antonako1
Description: Astral console API header file
             Contains console functions, structures and definitions
             Header file for all console manipulation
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
#   include <Windows.h>
#endif

/// @brief Console size structure
typedef struct _ASTRAL_CON_SIZE {
    AS_U64 WIDTH;               // Width
    AS_U64 HEIGHT;              // Height
} ASTRAL_CON_SIZE, *PASTRAL_CON_SIZE;

/// @brief Console structure
typedef struct _ASTRAL_CONSOLE {
    ASTRAL_CON_SIZE SZ;         // Console size

    AS_U8 *BUFFER;              // Buffer for the console
    AS_U64 BUFFER_SIZE;         // Size of the buffer
    
#if ASTRAL_PLATFORM_WINDOWS
    HANDLE HANDLEIN;            // Handle to the console input
    HANDLE HANDLEOUT;           // Handle to the console output
#elif ASTRAL_PLATFORM_LINUX
    AS_I32 HANDLEIN;            // File descriptor for the console input
    AS_I32 HANDLEOUT;           // File descriptor for the console output
#endif
    AS_BOOLEAN RUNNING;         // Is the console running
    
    AS_U32 CON_MODE;            // Console mode
    AS_U32 OG_MODE;             // Original console mode

    AS_U32 OGOCHCP;             // Original output console code page
    AS_U32 OGCHCP;              // Original console code page

} ASTRAL_CONSOLE, *PASTRAL_CONSOLE;


/*+++
Console modes. Apply with ASTRAL_CON_APPLY_MODES.
Use bitwise OR ('|') to combine modes.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Example:
    ASTRAL_CON_MODE_IGNORE_CTRL_C | ASTRAL_CON_MODE_MOUSE_INPUT
        --> Ignore CTRL+C and enable mouse input for the console
---*/
#define ASTRAL_CON_MODE_IGNORE_CTRL_C       0x00000001  // Ignore CTRL+C
#define ASTRAL_CON_MODE_MOUSE_INPUT         0x00000002  // Mouse input, allows mouse events


/// @brief Mouse event structure
typedef struct _ASTRAL_CON_MOUSE_EVENT {
    AS_U64 BUTTON_STATE;        // Button state
    AS_U64 BUTTONS;             // Buttons
    AS_U64 X;                   // X position
    AS_U64 Y;                   // Y position
} ASTRAL_CON_MOUSE_EVENT, *PASTRAL_CON_MOUSE_EVENT;
 
/// @brief Key event structure
typedef struct _ASTRAL_CON_KEY_EVENT {
    AS_U64 KEY_STATE;           // Key state
    AS_U64 KEY_CODE;            // Key code
    AS_U64 CHAR;                // Character
} ASTRAL_CON_KEY_EVENT, *PASTRAL_CON_KEY_EVENT;

/// @brief Resize event structure
typedef struct _ASTRAL_CON_RESIZE_EVENT {
    AS_U64 WIDTH;               // Width
    AS_U64 HEIGHT;              // Height
} ASTRAL_CON_RESIZE_EVENT, *PASTRAL_CON_RESIZE_EVENT;

/// @brief Menu event structure
typedef struct _ASTRAL_CON_MENU_EVENT {
    AS_U64 MENU_ID;             // Menu ID
} ASTRAL_CON_MENU_EVENT, *PASTRAL_CON_MENU_EVENT;

/// @brief Focus event structure. Contains the focus state
typedef struct _ASTRAL_CON_FOCUS_EVENT {
    AS_U64 FOCUS_STATE;         // Focus state
} ASTRAL_CON_FOCUS_EVENT, *PASTRAL_CON_FOCUS_EVENT;

/*+++
Console event types
---*/
#define ASTRAL_CON_EVENT_KEY         0x00000001 // Key event
#define ASTRAL_CON_EVENT_MOUSE       0x00000002 // Mouse event
#define ASTRAL_CON_EVENT_RESIZE      0x00000004 // Resize event
#define ASTRAL_CON_EVENT_MENU        0x00000008 // Menu event
#define ASTRAL_CON_EVENT_FOCUS       0x00000010 // Focus event
#define ASTRAL_CON_EVENT_NO_EVENT    0x00000020 // No event

/// @brief Console event structure
typedef struct _ASTRAL_CON_EVENT {
    AS_U64 EVENTS_READ;         // Events read
    AS_U32 EVENT_TYPE;          // Event type
    AS_U64 EVENT_SIZE;          // Size of the event
    AS_U8* EVENT_DATA;          // Event data
    ASTRAL_CON_MOUSE_EVENT  _MOUSE_EVENT;
    ASTRAL_CON_KEY_EVENT    _KEY_EVENT;
    ASTRAL_CON_RESIZE_EVENT _RESIZE_EVENT;
    ASTRAL_CON_MENU_EVENT   _MENU_EVENT;
    ASTRAL_CON_FOCUS_EVENT  _FOCUS_EVENT;
} ASTRAL_CON_EVENT, *PASTRAL_CON_EVENT;

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_GET_EVENT")
/// @brief Retrieves the next console event
/// @param CONSOLE Console to get event from
/// @param EVENT Event to store the event in
ASTRAL_EXPORT AS_U0 ASTRAL_CON_GET_EVENT(ASTRAL_CONSOLE* CONSOLE, ASTRAL_CON_EVENT* EVENT);


/// @brief Checks if the console is running
/// @param CONSOLE Console to check
/// @return BOOLEAN, is running
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_IS_RUNNING(ASTRAL_CONSOLE* CONSOLE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_CREATE")
/// @brief Creates a new console
/// @return ASTRAL_CONSOLE
ASTRAL_EXPORT ASTRAL_CONSOLE ASTRAL_CON_CREATE();

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_CLEAR")
/// @brief Clears the console screen
/// @param CONSOLE Console to clear
/// @return U16, error code
ASTRAL_EXPORT AS_U16 ASTRAL_CON_CLEAR(ASTRAL_CONSOLE* CONSOLE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_ADD_TO_BUFFER")
/// @brief Adds a string to the console buffer
/// @param CONSOLE Console to add to
/// @param STRING String to add
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_ADD_TO_BUFFER(ASTRAL_CONSOLE* CONSOLE, AS_STRING STRING);

// TODO: x2, implement
#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_WRITE_BUFFER")
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_WRITE_BUFFER(ASTRAL_CONSOLE* CONSOLE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_WRITE_STRING")
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_WRITE_STRING(ASTRAL_CONSOLE* CONSOLE, AS_U8* STRING);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_APPLY_MODES")
/// @brief Applies console modes
/// @param CONSOLE Console to apply modes to
/// @param MODES Modes to apply
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_APPLY_MODES(ASTRAL_CONSOLE* CONSOLE, AS_U64 MODES);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_DELETE")
/// @brief Releases the console, restores original console mode
/// @param CONSOLE Console to release
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_DELETE(ASTRAL_CONSOLE* CONSOLE);

/// @brief Console coordinate structure
typedef struct _ASTRAL_CON_COORD {
    AS_U64 X;                   // X position
    AS_U64 Y;                   // Y position
} ASTRAL_CON_COORD, *PASTRAL_CON_COORD;

#define ASTRAL_CON_STR_POS_CENTER   0x0001
#define ASTRAL_CON_STR_POS_LEFT     0x0002
#define ASTRAL_CON_STR_POS_RIGHT    0x0003


// Use RGBA macro to create a colour
#define RGBA(r, g, b, a) ((AS_U32)(((AS_U8)(r)|((AS_U16)((AS_U8)(g))<<8))|(((AS_U32)(AS_U8)(b))<<16)|(((AS_U32)(AS_U8)(a))<<24)))

/// @brief Console colour structure
typedef struct _ASTRAL_CON_COLOUR {
    AS_U8 R_F;                  // Red foreground
    AS_U8 G_F;                  // Green foreground
    AS_U8 B_F;                  // Blue foreground
    AS_U8 A_F;                  // Foreground alpha

    AS_U8 R_B;                  // Red background
    AS_U8 G_B;                  // Green background
    AS_U8 B_B;                  // Blue background
    AS_U8 A_B;                  // Background alpha
} ASTRAL_CON_COLOUR, *PASTRAL_CON_COLOUR;

/// @brief Sets the console colour structure with the given RGB values for the foreground
/// @param COLOUR Pointer to the colour structure
/// @param R Red value
/// @param G Green value
/// @param B Blue value
/// @param A Alpha value
/// @return U0
ASTRAL_EXPORT AS_U0 SET_CON_COLOUR_F(ASTRAL_CON_COLOUR* COLOUR, AS_U8 R, AS_U8 G, AS_U8 B, AS_U8 A);

/// @brief Sets the console colour structure with the given RGB value for the foreground
/// @param COLOUR Pointer to the colour structure
/// @param RGBA RGBA value, use the RGBA macro to create a colour
/// @return U0
ASTRAL_EXPORT AS_U0 SET_CON_COLOUR_F_M(ASTRAL_CON_COLOUR* COLOUR, AS_U32 RGBA);

/// @brief Sets the console colour structure with the given RGB values for the background
/// @param COLOUR Pointer to the colour structure
/// @param R Red value
/// @param G Green value
/// @param B Blue value
/// @param A Alpha value
/// @return U0
ASTRAL_EXPORT AS_U0 SET_CON_COLOUR_B(ASTRAL_CON_COLOUR* COLOUR, AS_U8 R, AS_U8 G, AS_U8 B, AS_U8 A);

/// @brief Sets the console colour structure with the given RGB value for the background
/// @param COLOUR Pointer to the colour structure
/// @param RGBA RGBA value, use the RGBA macro to create a colour
/// @return U0
ASTRAL_EXPORT AS_U0 SET_CON_COLOUR_B_M(ASTRAL_CON_COLOUR* COLOUR, AS_U32 RGBA);

/// @brief Basic string object
typedef struct _ASTRAL_CON_STR_OBJ {
    AS_STRING STRING;          // String data
    ASTRAL_CON_COLOUR COLOUR;   // Colour
} ASTRAL_CON_STR_OBJ, *PASTRAL_CON_STR_OBJ;

#define ASTRAL_CON_BUTTON_TYPE_TEXT  0x00000001
#define ASTRAL_CON_BUTTON_TYPE_RADIO 0x00000002
#define ASTRAL_CON_BUTTON_TYPE_CHECK 0x00000003

/// @brief Console button structure
typedef struct _ASTRAL_CON_BUTTON {
    AS_U64 BUTTON_STATE;        // Button state
    AS_U64 BUTTONS;             // Buttons
    AS_U64 TYPE;                // Type
    ASTRAL_CON_COORD POS;       // Position
    ASTRAL_CON_SIZE SZ;         // Size
    AS_U64 ID;                  // ID
    ASTRAL_CON_COLOUR COLOUR;   // Colour
    ASTRAL_CON_STR_OBJ STR_OBJ; // String object    
} ASTRAL_CON_BUTTON, *PASTRAL_CON_BUTTON;



/*+++
ASTRAL_CON KEY STATES

The following key states are used for the ASTRAL_CON_KEY_EVENT structure
    and for certain functions.
---*/
#define ASTRAL_CON_KEY_STATE_DOWN   0x00000001
#define ASTRAL_CON_KEY_STATE_UP     0x00000002

/*+++
ASTRAL_CON KEY CODES

The following key codes are used for the ASTRAL_CON_KEY_EVENT structure.

Codes follow the ASCII standard where possible.
---*/

#define ASTRAL_CON_KEY_BACKSPACE    0x00000008
#define ASTRAL_CON_KEY_TAB          0x00000009
#define ASTRAL_CON_KEY_ENTER        0x0000000D
#define ASTRAL_CON_KEY_ESCAPE       0x0000001B
#define ASTRAL_CON_KEY_SPACE        0x00000020
#define ASTRAL_CON_KEY_EXCLAMATION  0x00000021  // !
#define ASTRAL_CON_KEY_QUOTATION    0x00000022  // "
#define ASTRAL_CON_KEY_HASH         0x00000023  // #
#define ASTRAL_CON_KEY_DOLLAR       0x00000024  // $
#define ASTRAL_CON_KEY_PERCENT      0x00000025  // %
#define ASTRAL_CON_KEY_AMPERSAND    0x00000026  // &
#define ASTRAL_CON_KEY_APOSTROPHE   0x00000027  // '
#define ASTRAL_CON_KEY_LEFT_PAREN   0x00000028  // (
#define ASTRAL_CON_KEY_RIGHT_PAREN  0x00000029  // )
#define ASTRAL_CON_KEY_ASTERISK     0x0000002A  // *
#define ASTRAL_CON_KEY_PLUS         0x0000002B  // +
#define ASTRAL_CON_KEY_COMMA        0x0000002C  // ,
#define ASTRAL_CON_KEY_MINUS        0x0000002D  // -
#define ASTRAL_CON_KEY_PERIOD       0x0000002E  // .
#define ASTRAL_CON_KEY_SLASH        0x0000002F  // /
#define ASTRAL_CON_KEY_0            0x00000030  // 0
#define ASTRAL_CON_KEY_1            0x00000031  // 1
#define ASTRAL_CON_KEY_2            0x00000032  // 2
#define ASTRAL_CON_KEY_3            0x00000033  // 3
#define ASTRAL_CON_KEY_4            0x00000034  // 4
#define ASTRAL_CON_KEY_5            0x00000035  // 5
#define ASTRAL_CON_KEY_6            0x00000036  // 6
#define ASTRAL_CON_KEY_7            0x00000037  // 7
#define ASTRAL_CON_KEY_8            0x00000038  // 8
#define ASTRAL_CON_KEY_9            0x00000039  // 9
#define ASTRAL_CON_KEY_COLON        0x0000003A  // :
#define ASTRAL_CON_KEY_SEMICOLON    0x0000003B  // ;
#define ASTRAL_CON_KEY_LESS_THAN    0x0000003C  // <
#define ASTRAL_CON_KEY_EQUALS       0x0000003D  // =
#define ASTRAL_CON_KEY_GREATER_THAN 0x0000003E  // >
#define ASTRAL_CON_KEY_QUESTION     0x0000003F  // ?
#define ASTRAL_CON_KEY_AT           0x00000040  // @
#define ASTRAL_CON_KEY_A            0x00000041  // A
#define ASTRAL_CON_KEY_B            0x00000042  // B
#define ASTRAL_CON_KEY_C            0x00000043  // C
#define ASTRAL_CON_KEY_D            0x00000044  // D
#define ASTRAL_CON_KEY_E            0x00000045  // E
#define ASTRAL_CON_KEY_F            0x00000046  // F
#define ASTRAL_CON_KEY_G            0x00000047  // G
#define ASTRAL_CON_KEY_H            0x00000048  // H
#define ASTRAL_CON_KEY_I            0x00000049  // I
#define ASTRAL_CON_KEY_J            0x0000004A  // J
#define ASTRAL_CON_KEY_K            0x0000004B  // K
#define ASTRAL_CON_KEY_L            0x0000004C  // L
#define ASTRAL_CON_KEY_M            0x0000004D  // M
#define ASTRAL_CON_KEY_N            0x0000004E  // N
#define ASTRAL_CON_KEY_O            0x0000004F  // O
#define ASTRAL_CON_KEY_P            0x00000050  // P
#define ASTRAL_CON_KEY_Q            0x00000051  // Q
#define ASTRAL_CON_KEY_R            0x00000052  // R
#define ASTRAL_CON_KEY_S            0x00000053  // S
#define ASTRAL_CON_KEY_T            0x00000054  // T
#define ASTRAL_CON_KEY_U            0x00000055  // U
#define ASTRAL_CON_KEY_V            0x00000056  // V
#define ASTRAL_CON_KEY_W            0x00000057  // W
#define ASTRAL_CON_KEY_X            0x00000058  // X
#define ASTRAL_CON_KEY_Y            0x00000059  // Y
#define ASTRAL_CON_KEY_Z            0x0000005A  // Z
#define ASTRAL_CON_KEY_LEFT_BRACKET 0x0000005B  // [
#define ASTRAL_CON_KEY_BACKSLASH    0x0000005C  // \.
#define ASTRAL_CON_KEY_RIGHT_BRACKET 0x0000005D // ]
#define ASTRAL_CON_KEY_CARET        0x0000005E  // ^
#define ASTRAL_CON_KEY_UNDERSCORE   0x0000005F  // _
#define ASTRAL_CON_KEY_GRAVE        0x00000060  // `
#define ASTRAL_CON_KEY_a            0x00000061  // a
#define ASTRAL_CON_KEY_b            0x00000062  // b
#define ASTRAL_CON_KEY_c            0x00000063  // c
#define ASTRAL_CON_KEY_d            0x00000064  // d
#define ASTRAL_CON_KEY_e            0x00000065  // e
#define ASTRAL_CON_KEY_f            0x00000066  // f
#define ASTRAL_CON_KEY_g            0x00000067  // g
#define ASTRAL_CON_KEY_h            0x00000068  // h
#define ASTRAL_CON_KEY_i            0x00000069  // i
#define ASTRAL_CON_KEY_j            0x0000006A  // j
#define ASTRAL_CON_KEY_k            0x0000006B  // k
#define ASTRAL_CON_KEY_l            0x0000006C  // l
#define ASTRAL_CON_KEY_m            0x0000006D  // m
#define ASTRAL_CON_KEY_n            0x0000006E  // n
#define ASTRAL_CON_KEY_o            0x0000006F  // o
#define ASTRAL_CON_KEY_p            0x00000070  // p
#define ASTRAL_CON_KEY_q            0x00000071  // q
#define ASTRAL_CON_KEY_r            0x00000072  // r
#define ASTRAL_CON_KEY_s            0x00000073  // s
#define ASTRAL_CON_KEY_t            0x00000074  // t  
#define ASTRAL_CON_KEY_u            0x00000075  // u
#define ASTRAL_CON_KEY_v            0x00000076  // v
#define ASTRAL_CON_KEY_w            0x00000077  // w
#define ASTRAL_CON_KEY_x            0x00000078  // x
#define ASTRAL_CON_KEY_y            0x00000079  // y
#define ASTRAL_CON_KEY_z            0x0000007A  // z
#define ASTRAL_CON_KEY_LEFT_BRACE   0x0000007B  // {
#define ASTRAL_CON_KEY_PIPE         0x0000007C  // |
#define ASTRAL_CON_KEY_RIGHT_BRACE  0x0000007D  // }
#define ASTRAL_CON_KEY_TILDE        0x0000007E  // ~
#define ASTRAL_CON_KEY_DELETE       0x0000007F
#define ASTRAL_CON_KEY_F1           0x00000080
#define ASTRAL_CON_KEY_F2           0x00000081
#define ASTRAL_CON_KEY_F3           0x00000082
#define ASTRAL_CON_KEY_F4           0x00000083
#define ASTRAL_CON_KEY_F5           0x00000084
#define ASTRAL_CON_KEY_F6           0x00000085
#define ASTRAL_CON_KEY_F7           0x00000086
#define ASTRAL_CON_KEY_F8           0x00000087
#define ASTRAL_CON_KEY_F9           0x00000088
#define ASTRAL_CON_KEY_F10          0x00000089
#define ASTRAL_CON_KEY_F11          0x0000008A
#define ASTRAL_CON_KEY_F12          0x0000008B
#define ASTRAL_CON_KEY_CTRL         0x0000008C
#define ASTRAL_CON_KEY_SHIFT        0x0000008D
#define ASTRAL_CON_KEY_ALT          0x0000008E
#define ASTRAL_CON_KEY_CAPS_LOCK    0x0000008F
#define ASTRAL_CON_KEY_NUM_LOCK     0x00000090
#define ASTRAL_CON_KEY_SCROLL_LOCK  0x00000091
#define ASTRAL_CON_KEY_INSERT       0x00000092
#define ASTRAL_CON_KEY_HOME         0x00000093
#define ASTRAL_CON_KEY_END          0x00000094
#define ASTRAL_CON_KEY_PAGE_UP      0x00000095
#define ASTRAL_CON_KEY_PAGE_DOWN    0x00000096
#define ASTRAL_CON_KEY_ARROW_UP     0x00000097
#define ASTRAL_CON_KEY_ARROW_DOWN   0x00000098
#define ASTRAL_CON_KEY_ARROW_LEFT   0x00000099
#define ASTRAL_CON_KEY_ARROW_RIGHT  0x0000009A
#define ASTRAL_CON_KEY_PRINT_SCREEN 0x0000009B
#define ASTRAL_CON_KEY_PAUSE        0x0000009C
#define ASTRAL_CON_KEY_MENU         0x0000009D
#define ASTRAL_CON_KEY_WIN          0x0000009E

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_GET_SPEC_KEY_STATE") 
/// @brief Gets the state of a specific key
/// @param KEY_CODE Key code
/// @return AS_U16, key state, see key states above
ASTRAL_EXPORT AS_U16 ASTRAL_CON_GET_SPEC_KEY_STATE(AS_U64 KEY_CODE);


#endif // ASTRAL_CON_H