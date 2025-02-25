/*+++
Contains Windows specific code for the ASTRAL library.
---*/
#include <Windows.h>
#include <ASTRAL.H>

/*+++
ASTRAL_MEMORY.H
---*/

/*+++
ASTRAL_CON.H
---*/
ASTRAL_CONSOLE ASTRAL_CON_CREATE(ASTRAL_M_ARENA* ARENA) {
    ASTRAL_CONSOLE CONSOLE;
    CONSOLE.BUFFER = NULL;
    CONSOLE.ARENA = ARENA;
    CONSOLE.HANDLEOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE.HANDLEIN = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE.RUNNING = TRUE;
    CONSOLE.CON_MODE = 0;
    CONSOLE.WIDTH = GetSystemMetrics(SM_CXSCREEN);
    CONSOLE.HEIGHT = GetSystemMetrics(SM_CYSCREEN);
    return CONSOLE;
}

AS_BOOLEAN ASTRAL_CON_APPLY_MODES(ASTRAL_CONSOLE* CONSOLE, AS_U64 MODES) {
    DWORD mode = 0;
    if(!GetConsoleMode(CONSOLE->HANDLEOUT, &mode)) {
        return FALSE;
    }
    if(MODES & ASTRAL_CON_MODE_IGNORE_CTRL_C)    mode |= ENABLE_PROCESSED_INPUT;
    if(MODES & ASTRAL_CON_MODE_LINE_WRAP)        mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
    if(MODES & ASTRAL_CON_MODE_CURSOR_VISIBLE)   mode |= ENABLE_PROCESSED_OUTPUT;
    if(MODES & ASTRAL_CON_MODE_CURSOR_BLINK)     mode |= ENABLE_MOUSE_INPUT;
    if(MODES & ASTRAL_CON_MODE_MOUSE_INPUT)      mode |= ENABLE_MOUSE_INPUT;
    if(MODES & ASTRAL_CON_MODE_WINDOW_INPUT)     mode |= ENABLE_WINDOW_INPUT;
    if(!SetConsoleMode(CONSOLE->HANDLEOUT, mode)) return FALSE;
    CONSOLE->CON_MODE = MODES;

    return TRUE;
}





AS_U0 ASTRAL_CON_GET_EVENT(ASTRAL_CONSOLE* CONSOLE, ASTRAL_CONSOLE_EVENT* EVENT) {
    INPUT_RECORD input;
    if(!ReadConsoleInput(CONSOLE->HANDLEIN, &input, 1, (LPDWORD)&EVENT->EVENTS_READ)) {
        WriteConsoleW(CONSOLE->HANDLEOUT, L"Error reading console input\n", 30, NULL, NULL);
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
    if(!GetConsoleMode(CONSOLE->HANDLEOUT, &mode)) {
        return (AS_U16)GetLastError();
    }

    const DWORD original_mode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(CONSOLE->HANDLEOUT, mode)) {
        return (AS_U16)GetLastError();
    }

    DWORD written = 0;
    PCWSTR clear_sequence = L"\x1b[2J";
    if(!WriteConsoleW(CONSOLE->HANDLEOUT, clear_sequence, 4, &written, NULL)) {
        SetConsoleMode(CONSOLE->HANDLEOUT, original_mode);
        return (AS_U16)GetLastError();
    }

    SetConsoleMode(CONSOLE->HANDLEOUT, original_mode);
    return 0;
}
