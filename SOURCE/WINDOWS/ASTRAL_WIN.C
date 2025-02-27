/*+++
Contains Windows specific code for the ASTRAL library.
---*/
#include <Windows.h>
#include <ASTRAL.H>

/*+++
ASTRAL_MEMORY.H
---*/

AS_U0 *ASTRAL_M_ALLOC(AS_U64 SIZE) {
    if(SIZE == 0) return NULL;
    AS_U0 *RETVAL = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, SIZE);
    return RETVAL;
}
AS_U0 *ASTRAL_M_REALLOC(AS_U0 *PTR, AS_U64 SIZE) {
    if(PTR == NULL) return ASTRAL_M_ALLOC(SIZE);
    if(SIZE == 0) {
        ASTRAL_M_FREE(PTR);
        return NULL;
    }
    AS_U0 *RETVAL = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, PTR, SIZE);
    return RETVAL;
}
AS_U0 ASTRAL_M_FREE(AS_U0 *PTR) {
    if(PTR == NULL) return;
    HeapFree(GetProcessHeap(), 0, PTR);
}

/*+++
ASTRAL_CON.H
---*/
ASTRAL_CONSOLE ASTRAL_CON_CREATE() {
    ASTRAL_CONSOLE CONSOLE;
    
    CONSOLE.BUFFER = NULL;
    CONSOLE.BUFFER_SIZE = 0;

    CONSOLE.HANDLEOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE.HANDLEIN = GetStdHandle(STD_INPUT_HANDLE);
    
    CONSOLE.SZ.WIDTH = GetSystemMetrics(SM_CXSCREEN);
    CONSOLE.SZ.HEIGHT = GetSystemMetrics(SM_CYSCREEN);
    
    CONSOLE.RUNNING = TRUE;
    
    CONSOLE.CON_MODE = 0;
    CONSOLE.OGOCHCP = GetConsoleOutputCP();
    CONSOLE.OGCHCP = GetConsoleCP();
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);
    GetConsoleMode(CONSOLE.HANDLEIN, (LPDWORD)&CONSOLE.OG_MODE);
    CONSOLE.CON_MODE |= ENABLE_WINDOW_INPUT;
    SetConsoleMode(CONSOLE.HANDLEIN, (DWORD)CONSOLE.CON_MODE);
    
    return CONSOLE;
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





AS_U16 ASTRAL_CON_CLEAR(ASTRAL_CONSOLE* CONSOLE) {
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
