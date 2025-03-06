/*+++
ASTRAL_CON.H
Author: Antonako1
Description: Astral console API header file
                Header file for all console manipulation
                Contains console functions, structures and definitions
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
// Handle definition to avoid including Windows.h
typedef AS_U0 *HANDLE;
#elif ASTRAL_PLATFORM_LINUX
// On Linux, the console is accessed through the terminal
typedef AS_I32 HANDLE;
#else
#   error "Unsupported platform for ASTRAL_CON.H's HANDLE definition"
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief Console coordinate structure
typedef struct _ASTRAL_CON_COORD {
    AS_U64 X;                   // X position
    AS_U64 Y;                   // Y position
} ASTRAL_CON_COORD, *PASTRAL_CON_COORD;

/// @brief Creates a console coordinate structure
/// @param X X position
/// @param Y Y position
/// @return ASTRAL_CON_COORD, coordinate structure
ASTRAL_EXPORT ASTRAL_CON_COORD ASTRAL_CON_CREATE_COORD(AS_U64 X, AS_U64 Y);

/// @brief Console size structure
typedef struct _ASTRAL_CON_SIZE {
    AS_U64 WIDTH;               // Width
    AS_U64 HEIGHT;              // Height
} ASTRAL_CON_SIZE, *PASTRAL_CON_SIZE;

/// @brief Creates a console size structure
/// @param WIDTH Width
/// @param HEIGHT Height
/// @return ASTRAL_CON_SIZE, size structure
ASTRAL_EXPORT ASTRAL_CON_SIZE ASTRAL_CON_CREATE_SIZE(AS_U64 WIDTH, AS_U64 HEIGHT);

/*+++

        |~~~~~~~~~~~|
        |UI ELEMENTS|
        |~~~~~~~~~~~|

    UI elements are used to create a user interface in the console.

    UI is constructed using boxes that stack child elements vertically or horizontally.
    Elements can be buttons, text, other boxes, etc.

    Main types are buttons, text, boxes, etc.
        Sub types are more specific types of the main types.

---*/

/*+++
        |~~~~~~~~~~~~~~~~~~|
        |Colour definitions|
        |~~~~~~~~~~~~~~~~~~|

    Colour definitions are used to set the colour of the console text and background.
    Colours are defined below

---*/

#define ASTRAL_CON_FOREGROUND_WHITE     0x00000001 // White foreground
#define ASTRAL_CON_FOREGROUND_BLACK     0x00000002 // Black foreground

#define ASTRAL_CON_BACKGROUND_WHITE     0x00000001 // White background
#define ASTRAL_CON_BACKGROUND_BLACK     0x00000002 // Black background

#define ASTRAL_CON_FOREGROUND_DEFAULT    ASTRAL_CON_FOREGROUND_WHITE
#define ASTRAL_CON_BACKGROUND_DEFAULT    ASTRAL_CON_BACKGROUND_BLACK

/// @brief Console colour structure. Contains foreground and background colours
typedef struct _ASTRAL_CON_COLOUR {
    AS_U32 FOREGROUND;          // Foreground colour. Use DEFINES above
    AS_U32 BACKGROUND;          // Background colour. Use DEFINES above
} ASTRAL_CON_COLOUR, *PASTRAL_CON_COLOUR;

/// @brief Sets foreground colour
/// @param COLOUR Pointer to the colour structure
/// @param FOREGROUND Foreground colour. Use DEFINES
/// @return U0
ASTRAL_EXPORT AS_U0 ASTRAL_CON_SET_COLOUR_F(ASTRAL_CON_COLOUR* COLOUR, AS_U32 FOREGROUND);

/// @brief Sets background colour
/// @param COLOUR Pointer to the colour structure
/// @param BACKGROUND Background colour. Use DEFINES
/// @return U0
ASTRAL_EXPORT AS_U0 ASTRAL_CON_SET_COLOUR_B(ASTRAL_CON_COLOUR* COLOUR, AS_U32 BACKGROUND);


/// @brief Creates a colour structure with the given foreground and background colours
/// @param FOREGROUND Foreground colour. Use DEFINES
/// @return ASTRAL_CON_COLOUR, colour structure
ASTRAL_EXPORT ASTRAL_CON_COLOUR ASTRAL_CON_CREATE_COLOUR_F_B(AS_U32 FOREGROUND, AS_U32 BACKGROUND);


/*+++
    About borders
    ^^^^^^^^^^^^^

    There are 8 predefined border styles. 4 for ASCII and 4 for UTF-8.

    Borders are used to style boxes and other UI elements.

    Borders are defined by 8 pieces. 4 corners and 4 sides.


    CUSTOM BORDERS
    ^^^^^^^^^^^^^^

    Creating a custom border is done by creating an array of 
        8 characters for ASCII or 8 wide characters for UTF-8.

    The border is defined by the following pieces:
        0: Top left corner      | Definition: BORDER_TOP_LEFT_PIECE
        1: Top piece            | Definition: BORDER_TOP_PIECE
        2: Top right corner     | Definition: BORDER_TOP_RIGHT_PIECE
        3: Right piece          | Definition: BORDER_RIGHT_PIECE
        4: Bottom right corner  | Definition: BORDER_BOTTOM_RIGHT_PIECE
        5: Bottom piece         | Definition: BORDER_BOTTOM_PIECE
        6: Bottom left corner   | Definition: BORDER_BOTTOM_LEFT_PIECE
        7: Left piece           | Definition: BORDER_LEFT_PIECE
    Order is clockwise starting from the top left corner.
       
    Set custom border styles using
        ASTRAL_CON_SET_CUSTOM_ASCII_BORDER 
        and 
        ASTRAL_CON_SET_CUSTOM_UTF8_BORDER functions.

    These functions overwrite the old custom border style,
        so if you need to use multiple custom borders,
        you must set the custom border every time you need to use it.

    Current custom border styles can be retrieved using
        ASTRAL_CON_GET_CUSTOM_ASCII_BORDER
        and
        ASTRAL_CON_GET_CUSTOM_UTF8_BORDER functions.

    Example:
        // This is the solid ASCII border
        AS_U8 NEW_CUSTOM_ASCII_BORDER[PIECES_PER_BORDER] = {
            '/', '-', '\\', 
            '|',      '|', 
            '\\', '-', '/'
        };

        // Sets the custom ASCII border. Old custom border will be overwritten
        ASTRAL_CON_SET_CUSTOM_ASCII_BORDER(NEW_CUSTOM_ASCII_BORDER);
---*/
#define PIECES_PER_BORDER           0x8 // Pieces per border. 4 corners, 4 sides

#define BORDER_TOP_LEFT_PIECE       0x0 // Top left corner piece
#define BORDER_TOP_PIECE            0x1 // Top piece
#define BORDER_TOP_RIGHT_PIECE      0x2 // Top right corner piece
#define BORDER_RIGHT_PIECE          0x3 // Right piece
#define BORDER_BOTTOM_RIGHT_PIECE   0x4 // Bottom right corner piece
#define BORDER_BOTTOM_PIECE         0x5 // Bottom piece
#define BORDER_BOTTOM_LEFT_PIECE    0x6 // Bottom left corner piece
#define BORDER_LEFT_PIECE           0x7 // Left piece



/*+++
    ASCII styling for borders
    ^^^^^^^^^^^^^^^^^^^^^^^^^
---*/

/*
/----\
|    |
\----/
*/
#define BORDER_STYLE_ASCII_SOLID    0x00000001 // Solid border. -, |, etc.

/*
/- - \
|    |
\- - /
*/
#define BORDER_STYLE_ASCII_DASHED   0x00000002 // Dashed border. - - - - - - - - - -

/*
/....\
:    :
\..../
*/
#define BORDER_STYLE_ASCII_DOTTED   0x00000003 // Dotted border. .......................

/*
/====\
|    |
\====/
*/
#define BORDER_STYLE_ASCII_DOUBLE   0x00000004 // Double border. =, |, etc.

/*+++
    UTF-8 styling for borders
    ^^^^^^^^^^^^^^^^^^^^^^^^^

    Use with wide string configured CONSOLE struct!
---*/

/*
┌────┐
│    │
└────┘
*/
#define BORDER_STYLE_UTF8_SOLID     0x00000005 // UTF-8 solid border. ─, │, ┌, ┐, └, ┘, etc.

/*
┌┄┄┄┐
┆   ┆ 
└┄┄┄┘
*/
#define BORDER_STYLE_UTF8_DASHED    0x00000006 // UTF-8 dashed border. ┄, ┆, etc.

/*
┌┉┉┉┐
┊   ┊
└┉┉┉┘
*/
#define BORDER_STYLE_UTF8_DOTTED    0x00000007 // UTF-8 dotted border. ┉, ┊, etc.

/*
╔════╗
║    ║
╚════╝
*/
#define BORDER_STYLE_UTF8_DOUBLE    0x00000008 // UTF-8 double border. ═, ║, etc.

#define BORDER_STYLE_CUSTOM_ASCII   0x00000009 // Custom ASCII border
#define BORDER_STYLE_CUSTOM_UTF8    0x0000000A // Custom UTF-8 border

#define BORDER_STYLE_NONE           0x00000000 // No border
#define BORDER_STYLE_DEFAULT        BORDER_STYLE_ASCII_SOLID // Default border style

/// @brief Sets the predefined ASCII border style
/// @param BORDER_STYLE Border style, see info above in the ABOUT BORDERS section
ASTRAL_EXPORT AS_U0 ASTRAL_CON_SET_CUSTOM_ASCII_BORDER(AS_U8* BORDER_STYLE);

/// @brief Sets the custom UTF8 border style
/// @param BORDER_STYLE Border style array, see info above in the ABOUT BORDERS section
ASTRAL_EXPORT AS_U0 ASTRAL_CON_SET_CUSTOM_UTF8_BORDER(AS_WCHAR* BORDER_STYLE);

/// @brief Gets the custom ASCII border style
/// @return U8*, pointer to the custom ASCII border style
ASTRAL_EXPORT AS_U8 *ASTRAL_CON_GET_CUSTOM_ASCII_BORDER();

/// @brief Gets the custom UTF-8 border style
/// @return WCHAR*, pointer to the custom UTF-8 border style
ASTRAL_EXPORT AS_WCHAR *ASTRAL_CON_GET_CUSTOM_UTF8_BORDER();




typedef struct _ASTRAL_CON_MARGIN {
    AS_U64 TOP;
    AS_U64 BOTTOM;
    AS_U64 LEFT;
    AS_U64 RIGHT;
} ASTRAL_CON_MARGIN, *PASTRAL_CON_MARGIN;

/// @brief Creates a margin structure
/// @param TOP Margin from the top
/// @param BOTTOM Margin from the bottom
/// @param LEFT Margin from the left
/// @param RIGHT Margin from the right
/// @return ASTRAL_CON_MARGIN, margin structure
ASTRAL_EXPORT ASTRAL_CON_MARGIN ASTRAL_CON_CREATE_MARGIN(AS_U64 TOP, AS_U64 BOTTOM, AS_U64 LEFT, AS_U64 RIGHT);

typedef struct _ASTRAL_CON_PADDING {
    AS_U64 TOP;
    AS_U64 BOTTOM;
    AS_U64 LEFT;
    AS_U64 RIGHT;
} ASTRAL_CON_PADDING, *PASTRAL_CON_PADDING;

/// @brief Creates a padding structure
/// @param TOP Padding from the top
/// @param BOTTOM Padding from the bottom
/// @param LEFT Padding from the left
/// @param RIGHT Padding from the right
/// @return ASTRAL_CON_PADDING, padding structure
ASTRAL_EXPORT ASTRAL_CON_PADDING ASTRAL_CON_CREATE_PADDING(AS_U64 TOP, AS_U64 BOTTOM, AS_U64 LEFT, AS_U64 RIGHT);

typedef struct _ASTRAL_CON_STYLING {
    ASTRAL_CON_COLOUR   COLOUR;         // Colour
    ASTRAL_CON_MARGIN   MARGIN;         // Margin
    ASTRAL_CON_PADDING  PADDING;        // Padding
    AS_U64              BORDER_RADIUS;  // Border radius
    AS_U64              BORDER_WIDTH;   // Border width
    ASTRAL_CON_COLOUR   BORDER_COLOUR;  // Border colour
    AS_U64              BORDER_STYLE;   // Border style. Use DEFINES
    ASTRAL_CON_SIZE     SIZE;           // Size
} ASTRAL_CON_STYLING, *PASTRAL_CON_STYLING;

#define ASTRAL_CON_NULL_COLOUR     ASTRAL_CON_CREATE_COLOUR_F_B(ASTRAL_CON_FOREGROUND_DEFAULT, ASTRAL_CON_BACKGROUND_DEFAULT)
#define ASTRAL_CON_NULL_MARGIN     ASTRAL_CON_CREATE_MARGIN(0,0,0,0)
#define ASTRAL_CON_NULL_PADDING    ASTRAL_CON_CREATE_PADDING(0,0,0,0)

/// @brief Creates new ASTRAL_CON_STYLING object
/// @param COLOUR Colours. Create new ASTRAL_CON_COLOUR object with ASTRAL_CON_CREATE_COLOUR_F_B
/// @param MARGIN Margin. Create with ASTRAL_CON_CREATE_MARGIN
/// @param PADDING Padding. Create with ASTRAL_CON_CREATE_PADDING
/// @param BORDER_RADIUS Border radius
/// @param BORDER_WIDTH Border width
/// @param BORDER_COLOUR Border colour. Create new ASTRAL_CON_COLOUR object with ASTRAL_CON_CREATE_COLOUR_F_B
/// @param BORDER_STYLE Border style. USE DEFINES
/// @param SIZE Size of the object
/// @return New ASTRAL_CON_STYLING object 
ASTRAL_EXPORT ASTRAL_CON_STYLING ASTRAL_CON_CREATE_STYLING (
    ASTRAL_CON_COLOUR COLOUR,
    ASTRAL_CON_MARGIN MARGIN,
    ASTRAL_CON_PADDING PADDING,
    AS_U64 BORDER_RADIUS,
    AS_U64 BORDER_WIDTH,
    ASTRAL_CON_COLOUR BORDER_COLOUR,
    AS_U64 BORDER_STYLE,
    ASTRAL_CON_SIZE SIZE
);

#define AS_CON_TYPE_COMBO(TYPE, SUB_TYPE) ((AS_U32)TYPE << 16 | SUB_TYPE)
/// @brief Creates new ASTRAL_CON_STYLING object with default values 
/// @param TYPE_COMBO Use AS_CON_TYPE_COMBO macro defined aboce
/// @param CATEGORY Category of the styling. See comment box below
/// @return New ASTRAL_CON_STYLING object with default the default 
ASTRAL_EXPORT ASTRAL_CON_STYLING ASTRAL_CON_CREATE_STYLING_WITH_PREDEF_STYLING(AS_U32 TYPE_COMBO, AS_U32 CATEGORY);

/*+++
Default styling for UI elements

Each element type has its own default styling.

Categories:
    Colour
    Margin
    Padding
    Border radius
    Border width
    Border colour
    Border style
    Size

Different categories can be combined using bitwise OR ('|').
---*/

#define ASTRAL_CON_STYLING_CATEGORY_COLOUR          0x00000001
#define ASTRAL_CON_STYLING_CATEGORY_MARGIN          0x00000002
#define ASTRAL_CON_STYLING_CATEGORY_PADDING         0x00000004
#define ASTRAL_CON_STYLING_CATEGORY_BORDER_RADIUS   0x00000008
#define ASTRAL_CON_STYLING_CATEGORY_BORDER_WIDTH    0x00000010
#define ASTRAL_CON_STYLING_CATEGORY_BORDER_COLOUR   0x00000020
#define ASTRAL_CON_STYLING_CATEGORY_BORDER_STYLE    0x00000040
#define ASTRAL_CON_STYLING_CATEGORY_SIZE            0x00000080


#define 
/// @brief Sets the predefined styling for a UI element
/// @param ELEMENTUse AS_CON_TYPE_COMBO macro defined aboce for
/// @param CATEGORY Category of the styling
/// @return U0
ASTRAL_EXPORT AS_U0 ASTRAL_CON_SET_PREDEF_STYLING(ASTRAL_CON_UI_ELEM* ELEMENT, AS_U32 CATEGORY);


#define ASTRAL_CON_STR_POS_CENTER   0x0001
#define ASTRAL_CON_STR_POS_LEFT     0x0002
#define ASTRAL_CON_STR_POS_RIGHT    0x0003

/// @brief Basic string object
typedef struct _ASTRAL_CON_STR_OBJ {
    AS_U32 STR_POS;             // String position. Use DEFINES. Defaults to center
    AS_STRING *STRING;           // String data
} ASTRAL_CON_STR_OBJ, *PASTRAL_CON_STR_OBJ;



// UI Element types
#define ASTRAL_CON_UI_ELEM_TYPE_BUTTON      0x00000001 // Button. See sub types
#define ASTRAL_CON_UI_ELEM_TYPE_TEXT        0x00000002 // Text. See sub types
#define ASTRAL_CON_UI_ELEM_TYPE_BOX         0x00000003 // Box. See sub types
#define ASTRAL_CON_UI_ELEM_TYPE_ROOT        0x00000004 // Root element. USED ONLY FOR THE ROOT ELEMENT. DO NOT USE FOR OTHER ELEMENTS

#define ASTRAL_DEF_TYPE                     ASTRAL_CON_UI_ELEM_TYPE_BOX
#define ASTRAL_DEF_SUB_TYPE                 0x00000001 // Default sub type

/*+++
Button sub types

Button types are used to create buttons in the console.

Radio buttons are used to select one option from a group of options.
Check buttons are used to toggle a setting.
Dropdown buttons are used to select one option from a dropdown list.

Options can be added by adding child elements to the button.
These child elements may NOT contain child elements themselves.

State can be checked by looking the state of the button with its ID.
---*/
#define ASTRAL_CON_BUTTON_TYPE_TEXT         0x00000001 // Default. Text button
#define ASTRAL_CON_BUTTON_TYPE_RADIO        0x00000002 // Radio button
#define ASTRAL_CON_BUTTON_TYPE_CHECK        0x00000003 // Check button
#define ASTRAL_CON_BUTTON_TYPE_DROPDOWN     0x00000004 // Dropdown button

/*+++
Text sub types

Text types are used to display text in the console.

TEXT: Default text type. Displays text.
TITLE: Title text type. Displays title text, similar to a <H[1-6]> tag in HTML.
---*/
#define ASTRAL_CON_TEXT_TYPE_TEXT           0x00000001 // Default. Text
#define ASTRAL_CON_TEXT_TYPE_TITLE          0x00000002 // Title

/*+++
Box sub types

Box types are used to create boxes in the console.

VERTICAL: Default. Vertical box. Stacks child elements vertically.
HORIZONTAL: Horizontal box. Stacks child elements horizontally.

Boxes can contain child elements.

If text object data is applied to a box, the text won't be displayed as the box is not a text object.
---*/
#define ASTRAL_CON_BOX_TYPE_VERTICAL        0x00000001 // Default. Vertical box
#define ASTRAL_CON_BOX_TYPE_HORIZONTAL      0x00000002 // Horizontal box

// Forward declarations
typedef struct _ASTRAL_CON_UI_ELEM ASTRAL_CON_UI_ELEM;
typedef struct _ASTRAL_CON_UI_ELEM_ARR ASTRAL_CON_UI_ELEM_ARR;

#define AS_UNUSED_ID U64_MAX

/*+++
Main UI element structure

UI elements are used to create a user interface in the console.

Different types of elements can be created by assigning the type and its sub type.

Each element can have child elements, which can be used to create more complex UIs.

Please read information about each field before using the structure.
---*/
typedef struct _ASTRAL_CON_UI_ELEM {
    /*+++
    Type of the element. Use DEFINES defined above.
    Defaults to box.
    ---*/
    AS_U64 TYPE;

    /*+++
    Sub type of the element. Use DEFINES defined above.
    Defaults to 0x00000001.
    ---*/
    AS_U64 SUB_TYPE;
    
    /*+++
    ID of the element. ( USE RANGE OF 1 - (U64_MAX-1) )
    This field is required and must be unique (AS_UNUSED_ID can be used as much as needed). 
    0 is reserved for the root element, AS_UNUSED_ID is reserved for elements without use for an ID.
    Recommended to use ENUMS for easier use.
    ---*/
    AS_U64 ID;

    /*+++
    Position of the element. Defaults to 0,0.
    ---*/
    ASTRAL_CON_COORD POS;

    /*+++
    Styling of the element. Defaults to default styling. See info of ASTRAL_CON_SET_PREDEF_STYLING.
    ---*/
    ASTRAL_CON_STYLING STYLING;

    // Array of child elements
    ASTRAL_CON_UI_ELEM_ARR *CHILDREN;

    // Pointer to the parent element
    ASTRAL_CON_UI_ELEM *PARENT;

    /*+++
    Text object. Can be empty. Defaults to empty.
    ---*/
    ASTRAL_CON_STR_OBJ *TEXT;

    // State of the element. Used for buttons, etc.
    AS_U64 STATE;

    // Size of this structure
    AS_U64 SZ;
} ASTRAL_CON_UI_ELEM, *PASTRAL_CON_UI_ELEM;

/// @brief Creates a new string object. Free with ASTRAL_CON_FREE_STR_OBJ
/// @param STRING String data. This data will be copied
/// @param STR_POS String position. See DEFINES above ASTRAL_CON_STR_OBJ
/// @return Pointer to the created string object
ASTRAL_EXPORT ASTRAL_CON_STR_OBJ *ASTRAL_CON_CREATE_STR_OBJ(AS_STRING *STRING, AS_U32 STR_POS);

/// @brief Frees the string object
/// @param STR_OBJ String object to free
/// @return U0
ASTRAL_EXPORT AS_U0 ASTRAL_CON_FREE_STR_OBJ(ASTRAL_CON_STR_OBJ* STR_OBJ);

/// @brief Creates a new UI element
/// @param PARENT Pointer to the parent element
/// @return ASTRAL_CON_UI_ELEM, pointer to the created element
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM *ASTRAL_CON_UI_ELEM_INIT(ASTRAL_CON_UI_ELEM* PARENT);

/// @brief Extended UI element creation function
/// @param ELEMENT Pointer to the element to create
/// @param TYPE Type of the element
/// @param SUB_TYPE Sub type of the element
/// @param ID ID of the element
/// @param POS Position of the element
/// @param STYLING Styling of the element
/// @param CHILDREN Array of child elements. Use ASTRAL_CON_UI_ELEM_ARR_INIT to create an array
/// @param PARENT Pointer to the parent element
/// @param TEXT Text object
/// @return ASTRAL_CON_UI_ELEM*, pointer to the created element
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM *ASTRAL_CON_UI_ELEM_INIT_EX(
    ASTRAL_CON_UI_ELEM *PARENT, 
    AS_U64 TYPE, 
    AS_U64 SUB_TYPE, 
    AS_U64 ID, 
    ASTRAL_CON_COORD POS, 
    ASTRAL_CON_STYLING STYLING, 
    ASTRAL_CON_UI_ELEM_ARR *CHILDREN, 
    ASTRAL_CON_STR_OBJ *TEXT 
);

/// @brief Frees the UI element
/// @param ELEMENT Element to free
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_UI_ELEM_FREE(ASTRAL_CON_UI_ELEM* ELEMENT);

/// @brief Sets the text of the UI element
/// @param ELEMENT Element to set the text for
/// @param TEXT Text to set
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_UI_ELEM_SET_TEXT(ASTRAL_CON_UI_ELEM* ELEMENT, AS_STRING *TEXT);

/*+++
    
    |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
    |Children element array manipulation functions and structures|
    |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|

    Functions and structures for manipulating child elements of a UI element.

---*/
/// @brief Array of UI elements
typedef struct _ASTRAL_CON_UI_ELEM_ARR {
    ASTRAL_CON_UI_ELEM* ELEMENTS;           // Array of elements
    AS_U64 SIZE;                            // Size of the array
} ASTRAL_CON_UI_ELEM_ARR, *PASTRAL_CON_UI_ELEM_ARR;

/// @brief Creates a new UI element array
/// @return ASTRAL_CON_UI_ELEM_ARR
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM_ARR* ASTRAL_CON_UI_ELEM_ARR_INIT();

/// @brief Pushes a new element to the array. Only the pointer is pushed
/// @param ARR Array to push the element to
/// @param ELEMENT Element to push
/// @return Pointer to the pushed element
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM *ASTRAL_CON_UI_ELEM_ARR_PUSH(ASTRAL_CON_UI_ELEM_ARR* ARR, ASTRAL_CON_UI_ELEM* ELEMENT);

/// @brief Pops the last element from the array
/// @param ARR Array to pop the element from
/// @return BOOLEAN, success
ASTRAL_EXPORT_INTERNAL AS_BOOLEAN ASTRAL_CON_UI_ELEM_ARR_POP(ASTRAL_CON_UI_ELEM_ARR* ARR);

/// @brief Frees the UI element array
/// @param ARR Array to free
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_UI_ELEM_ARR_FREE(ASTRAL_CON_UI_ELEM_ARR* ARR);

/// @brief Gets the child element at the given index
/// @param ARR Array to get the element from
/// @param INDEX Index of the element
/// @return Pointer to the element. NULLPTR if not found
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM* ASTRAL_CON_UI_GET_CHILD_AT_INDEX(ASTRAL_CON_UI_ELEM_ARR* ARR, AS_U64 INDEX);

/// @brief Searches for a child element with the given ID
/// @param ELEMENT Element to search from
/// @param ID ID of the child element
/// @param CHILD Pointer to save the child element to
/// @return Index of the child element. U64_MAX if not found 
ASTRAL_EXPORT_INTERNAL AS_U64 ASTRAL_CON_UI_GET_CHILD_OF_ID(ASTRAL_CON_UI_ELEM* ELEMENT, AS_U64 ID, ASTRAL_CON_UI_ELEM* CHILD);


/// @brief Recursively searches for an element with the given ID
/// @param ELEMENT Element to start the search from
/// @param ID ID of the element
/// @param MAX_DEPTH Maximum depth to search. 0 for no limit
/// @return Pointer to the element. NULLPTR if not found
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_UI_ELEM* ASTRAL_CON_UI_RECUR_SEARCH_ID(ASTRAL_CON_UI_ELEM* ELEMENT, AS_U64 ID, AS_U32 MAX_DEPTH);



/// @brief Console buffer
typedef struct _ASTRAL_CON_BUFFER {
    AS_U8 *DATA;              // Buffer
    AS_U64 SIZE;                // Size of the buffer
} ASTRAL_CON_BUFFER, *PASTRAL_CON_BUFFER;

/// @brief Initializes the console buffer. Free with ASTRAL_CON_BUFFER_DEL
/// @param BUFFER Buffer to initialize
/// @param SIZE Size of the buffer
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_BUFFER_INIT(ASTRAL_CON_BUFFER* BUFFER, AS_U64 SIZE);

/// @brief Frees the console buffer
/// @param BUFFER Buffer to free
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_BUFFER_DEL(ASTRAL_CON_BUFFER* BUFFER);

/// @brief Sets the buffer size, re-allocating the buffer with the new SIZE
/// @param BUFFER Buffer to set the size for
/// @param SIZE New size
/// @return U0*, pointer to new buffer data
ASTRAL_EXPORT_INTERNAL AS_U0 *ASTRAL_CON_SET_BUFFER_SZ(ASTRAL_CON_BUFFER* BUFFER, AS_U64 SIZE);

/// @brief Clears buffer, setting memory to 0
/// @param BUFFER Buffer to clear
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_BUFFER_CLEAR(ASTRAL_CON_BUFFER* BUFFER);

/// @brief Copies the memory of SRC buffer to DST buffer
/// @param DST Destination buffer
/// @param SRC Source buffer
/// @return U0
ASTRAL_EXPORT_INTERNAL AS_U0 ASTRAL_CON_BUFFER_COPY(ASTRAL_CON_BUFFER* DST, ASTRAL_CON_BUFFER* SRC);

/// @brief Copies the memory of SRC buffer to a new buffer
/// @param SRC Source buffer
/// @return ASTRAL_CON_BUFFER*, pointer to the new buffer
ASTRAL_EXPORT_INTERNAL ASTRAL_CON_BUFFER *ASTRAL_CON_BUFFER_COPY2(ASTRAL_CON_BUFFER* SRC);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_RUN_INFO")
/// @brief Process info for new console
typedef struct _ASTRAL_CON_RUN_INFO {
    HANDLE PROCESS_HANDLE;
    HANDLE THREAD_HANDLE;
    AS_U32 PROCESS_ID;
    AS_U32 THREAD_ID;
} ASTRAL_CON_RUN_INFO, *PASTRAL_CON_RUN_INFO;

/// @brief Console structure
typedef struct _ASTRAL_CONSOLE {
    ASTRAL_CON_SIZE SIZE;       // Console size

    ASTRAL_CON_BUFFER BUFFER;   // Console buffer

    HANDLE HANDLEIN;            // Handle to the console input
    HANDLE HANDLEOUT;           // Handle to the console output

    AS_BOOLEAN RUNNING;         // Is the console running
    
    AS_U32 CON_MODE;            // Console mode
    AS_U32 OG_MODE;             // Original console mode

    AS_U32 OGOCHCP;             // Original output console code page
    AS_U32 OGCHCP;              // Original console code page

    ASTRAL_CON_UI_ELEM* ROOT;    // Root element
    
    ASTRAL_CON_RUN_INFO RUN_INFO; // Console run info
} ASTRAL_CONSOLE, *PASTRAL_CONSOLE;







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

/// @brief Checks if the console is running. Use as the main loop condition
/// @param CONSOLE Console to check
/// @return BOOLEAN, is running
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_IS_RUNNING(ASTRAL_CONSOLE* CONSOLE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_INIT")
/// @brief Gets the current size of the console, updating the CONSOLE struct
/// @param CONSOLE Pointer to the console struct
/// @return BOOLEAN, success
ASTRAL_EXPORT_INTERNAL AS_BOOLEAN ASTRAL_CON_GET_SIZE(ASTRAL_CONSOLE* CONSOLE);

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_CREATE")
/// @brief Creates a new console
/// @return ASTRAL_CONSOLE
ASTRAL_EXPORT ASTRAL_CONSOLE *ASTRAL_CON_CREATE();

#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_DELETE")
/// @brief Releases the console, restores original console mode
/// @param CONSOLE Console to release
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_DELETE(ASTRAL_CONSOLE* CONSOLE);


#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_CLS")
/// @brief Clears the console screen
/// @param CONSOLE Console to clear
/// @return U16, error code (0 = success)
ASTRAL_EXPORT AS_U16 ASTRAL_CON_CLS(ASTRAL_CONSOLE* CONSOLE);






/*+++
        |~~~~~~~~~~~~~~~~~~|
        |  Console modes   |
        |~~~~~~~~~~~~~~~~~~|

Console modes. Apply with ASTRAL_CON_APPLY_MODES.

Use bitwise OR ('|') to combine modes.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Example:
    ASTRAL_CON_MODE_IGNORE_CTRL_C | ASTRAL_CON_MODE_MOUSE_INPUT
        --> Ignore CTRL+C and enable mouse input for the console
---*/
#define ASTRAL_CON_MODE_IGNORE_CTRL_C       0x00000001  // Ignore CTRL+C
#define ASTRAL_CON_MODE_MOUSE_INPUT         0x00000002  // Mouse input, allows mouse events


#pragma ONLY_ON_WINDOWS_REMINDER("ASTRAL_CON_APPLY_MODES")
/// @brief Applies console modes
/// @param CONSOLE Console to apply modes to
/// @param MODES Modes to apply
/// @return BOOLEAN, success
ASTRAL_EXPORT AS_BOOLEAN ASTRAL_CON_APPLY_MODES(ASTRAL_CONSOLE* CONSOLE, AS_U64 MODES);









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


/*+++
        CREATING UI ELEMENT STRUCTURE TREE

    The following macros are used to create a tree structure for the UI elements.

    ASTRAL_CON_CREATE_ELEMENT: Creates a new UI element. Use with ASTRAL_CON macro
    ASTRAL_CON: Master macro for the console

    Example:
        ASTRAL_CON(
            CONSOLE,        // Console to use
            ASTRAL_CON_CREATE_ELEMENT(

            )
        )
---*/

/*+++
            |~~~~~~~~~~~~~|
            |ASTRAL_CON_CE|
            |~~~~~~~~~~~~~|
    
    ASTRAL_CON_CE is a macro used to create a new UI element.

    Use this macro ONLY with ASTRAL_CON.

    TYPE: Type of the element. Use DEFINES above.
    SUB_TYPE: Sub type of the element. Use DEFINES above.
    ID: ID of the element. Use ENUMS for easier use.
    STYLING: Styling of the element. Use ASTRAL_CON_CREATE_STYLING.
    TEXT: Text object. Use ASTRAL_CON_CREATE_STR_OBJ or NULLPTR.
    ...: Child elements. Use ASTRAL_CON_CE for child elements. NULLPTR if there are no child elements.
---*/
#define ASTRAL_CON_CE(  \
        TYPE,           \
        SUB_TYPE,       \
        ID,             \
        STYLING,        \
        TEXT,           \
        ...             \
    )                   

///@brief Master macro for the console
///@param CONSOLE Console to use
///@param TREE_STRUCTURE Tree structure to use
#define ASTRAL_CON(CONSOLE,         \
                    TREE_STRUCTURE  \
                )
                
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ASTRAL_CON_H