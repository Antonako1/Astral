/*+++
Contains Windows specific code for the ASTRAL library.

For ASTRAL_CON.H
---*/
#include <Windows.h>
#include <ASTRAL.H>

/*+++
ASTRAL_CON.H
---*/
ASTRAL_CONSOLE *ASTRAL_CON_CREATE() {
    ASTRAL_CONSOLE *CONSOLE = (ASTRAL_CONSOLE*)ASTRAL_M_ALLOC(sizeof(ASTRAL_CONSOLE));
    if(CONSOLE == NULLPTR) return NULLPTR;
    CONSOLE->HANDLEOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE->HANDLEIN = GetStdHandle(STD_INPUT_HANDLE);
    
    ASTRAL_CON_GET_SIZE(CONSOLE);
    
    CONSOLE->RUNNING = TRUE;
    
    CONSOLE->CON_MODE = 0;
    CONSOLE->OGOCHCP = GetConsoleOutputCP();
    CONSOLE->OGCHCP = GetConsoleCP();
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);
    GetConsoleMode(CONSOLE->HANDLEIN, (LPDWORD)&CONSOLE->OG_MODE);
    CONSOLE->CON_MODE |= ENABLE_WINDOW_INPUT;
    SetConsoleMode(CONSOLE->HANDLEIN, (DWORD)CONSOLE->CON_MODE);
    

    CONSOLE->BUFFER_SIZE = CONSOLE->SIZE.WIDTH * CONSOLE->SIZE.HEIGHT;
    CONSOLE->BUFFER = (AS_U8*)ASTRAL_M_ALLOC(CONSOLE->BUFFER_SIZE);
    if(CONSOLE->BUFFER == NULLPTR) {
        CONSOLE->RUNNING = FALSE;
        ASTRAL_M_FREE(CONSOLE);
        CONSOLE = NULLPTR;
        return NULLPTR;
    }

    CONSOLE->ROOT = ASTRAL_CON_UI_ELEM_INIT_EX(
        NULLPTR,                    // Parent. NULLPTR for root
        ASTRAL_CON_UI_ELEM_TYPE_ROOT, // Type
        ASTRAL_DEF_SUB_TYPE,        // Sub type
        0,                          // ID. 0 for root
        ASTRAL_CON_CREATE_COORD(0,0),   // Position.
        {
            ASTRAL_CON_CREATE_COLOUR_F_B_M(
                RGBA(0,0,0,0), 
                RGBA(0,0,0,0)
            ),              // Colour
            ASTRAL_CON_CREATE_MARGIN(0,0,0,0),       // Margin
            ASTRAL_CON_CREATE_PADDING(0,0,0,0),      // Padding
            0,              // Border radius
            0,              // Border width
            ASTRAL_CON_CREATE_COLOUR_F_B_M(
                RGBA(0,0,0,0), 
                RGBA(0,0,0,0)
            ),                      // Border colour
            BORDER_STYLE_NONE,      // Border style
            {CONSOLE->SIZE.WIDTH, CONSOLE->SIZE.HEIGHT} // Size
        },                          // Styling
        NULLPTR,                    // Children. NULLPTR, no children yet
        NULLPTR                     // Text. NULLPTR for root.
    );

    return CONSOLE;
}

AS_BOOLEAN ASTRAL_CON_GET_SIZE(ASTRAL_CONSOLE* CONSOLE) {
    // Get console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(CONSOLE->HANDLEOUT, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    CONSOLE->SIZE = ASTRAL_CON_CREATE_SIZE(columns, rows);
    return true;
}

AS_BOOLEAN ASTRAL_CON_APPLY_MODES(ASTRAL_CONSOLE* CONSOLE, AS_U64 MODES) {
    if (MODES & ASTRAL_CON_MODE_IGNORE_CTRL_C) 
        SetConsoleCtrlHandler(NULL, TRUE);
    else 
        SetConsoleCtrlHandler(NULL, FALSE);
    if (MODES & ASTRAL_CON_MODE_MOUSE_INPUT) {
        DWORD sc_mode = ENABLE_EXTENDED_FLAGS;
        if(!SetConsoleMode(CONSOLE->HANDLEIN, sc_mode)) return FALSE;
        sc_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
        if(!SetConsoleMode(CONSOLE->HANDLEIN, sc_mode)) return FALSE;
    } else {
        DWORD sc_mode = ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS;
        if(!SetConsoleMode(CONSOLE->HANDLEIN, sc_mode)) return FALSE;
    }
    return TRUE;
}


AS_BOOLEAN ASTRAL_CON_DELETE(ASTRAL_CONSOLE* CONSOLE) {
    SetConsoleMode(CONSOLE->HANDLEIN, (DWORD)CONSOLE->OG_MODE);
    SetConsoleMode(CONSOLE->HANDLEIN, ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
    SetConsoleCtrlHandler(NULL, FALSE);
    CONSOLE->RUNNING = FALSE;
    ASTRAL_M_FREE(CONSOLE->BUFFER);
    CONSOLE->BUFFER = NULLPTR;
    CONSOLE->BUFFER_SIZE = 0;
    ASTRAL_CON_UI_ELEM_FREE(CONSOLE->ROOT);
    CONSOLE->ROOT = NULLPTR;
    ASTRAL_M_FREE(CONSOLE);
    CONSOLE = NULLPTR;
    return TRUE;
}



AS_U0 ASTRAL_CON_GET_EVENT(ASTRAL_CONSOLE* CONSOLE, ASTRAL_CON_EVENT* EVENT) {
    INPUT_RECORD input;
    if(!ReadConsoleInput(CONSOLE->HANDLEIN, &input, 1, (LPDWORD)&EVENT->EVENTS_READ)) {
        return;
    }
    switch(input.EventType) {
        case KEY_EVENT:
            EVENT->EVENT_TYPE = ASTRAL_CON_EVENT_KEY;
            EVENT->EVENT_SIZE = sizeof(input.Event.KeyEvent);
            EVENT->EVENT_DATA = (AS_U8*)&input.Event.KeyEvent;
            break;
        case MOUSE_EVENT:
            EVENT->EVENT_TYPE = ASTRAL_CON_EVENT_MOUSE;
            EVENT->EVENT_SIZE = sizeof(input.Event.MouseEvent);
            EVENT->EVENT_DATA = (AS_U8*)&input.Event.MouseEvent;
            break;
        case MENU_EVENT:
            EVENT->EVENT_TYPE = ASTRAL_CON_EVENT_MENU;
            EVENT->EVENT_SIZE = sizeof(input.Event.MenuEvent);
            EVENT->EVENT_DATA = (AS_U8*)&input.Event.MenuEvent;
            break;
        case FOCUS_EVENT:
            EVENT->EVENT_TYPE = ASTRAL_CON_EVENT_FOCUS;
            EVENT->EVENT_SIZE = sizeof(input.Event.FocusEvent);
            EVENT->EVENT_DATA = (AS_U8*)&input.Event.FocusEvent;
            break;
        default:
            EVENT->EVENT_TYPE = ASTRAL_CON_EVENT_NO_EVENT;
            EVENT->EVENT_SIZE = 0;
            EVENT->EVENT_DATA = NULL;
            break;
    }
}





AS_U16 ASTRAL_CON_CLS(ASTRAL_CONSOLE* CONSOLE) {
    DWORD mode = 0;
    if(!GetConsoleMode(CONSOLE->HANDLEIN, &mode)) {
        return (AS_U16)GetLastError();
    }

    const DWORD original_mode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(CONSOLE->HANDLEIN, mode)) {
        return (AS_U16)GetLastError();
    }

    SetConsoleCP(CONSOLE->OGCHCP);
    SetConsoleOutputCP(CONSOLE->OGOCHCP);
    DWORD written = 0;
    PCWSTR clear_sequence = L"\x1b[2J";
    if(!WriteConsoleW(CONSOLE->HANDLEOUT, clear_sequence, 4, &written, NULL)) {
        SetConsoleMode(CONSOLE->HANDLEIN, original_mode);
        return (AS_U16)GetLastError();
    }

    SetConsoleMode(CONSOLE->HANDLEIN, original_mode);
    return 0;
}
