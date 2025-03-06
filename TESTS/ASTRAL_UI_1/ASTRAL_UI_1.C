#define ASTRAL_DEBUG_ACTIVE 1 // Allow use of internal functions
#include "../../INCLUDE/ASTRAL.H"
#include <stdio.h>
#include <stdlib.h>

enum IDs {
    AS_ROOT_ID=0,         // Root element reserves ID 0
    AS_MAIN_BOX_ID,
};

int main(void) {
    
    ASTRAL_CONSOLE *console = ASTRAL_CON_CREATE();
    ASTRAL_CON_APPLY_MODES(console, ASTRAL_CON_MODE_MOUSE_INPUT | ASTRAL_CON_MODE_IGNORE_CTRL_C);

    printf("Console root id: %llu\n", console->ROOT->ID);
    printf("Console root height: %llu\n", console->ROOT->STYLING.SIZE.HEIGHT);
    printf("Console root width: %llu\n", console->ROOT->STYLING.SIZE.WIDTH);

    ASTRAL_CON_UI_ELEM_SET_TEXT(console->ROOT, ASTRAL_STR_CREATE_EX(STR_MAX_COMBO("Hello, world!")));

    ASTRAL_CON(CONSOLE,
        ASTRAL_CON_CE(
            ASTRAL_CON_UI_ELEM_TYPE_BOX,
            ASTRAL_DEF_SUB_TYPE,
            AS_MAIN_BOX_ID,
            ASTRAL_CON_CREATE_COORD(0,0),
            ASTRAL_CON_CREATE_STYLING(
                ASTRAL_CON_CREATE_COLOUR_F_B(ASTRAL_CON_FOREGROUND_DEFAULT, ASTRAL_CON_BACKGROUND_DEFAULT),
                ASTRAL_CON_CREATE_MARGIN(0,0,0,0),
                ASTRAL_CON_CREATE_PADDING(0,0,0,0),
                0, 0, ASTRAL_CON_CREATE_COLOUR_F_B(ASTRAL_CON_FOREGROUND_DEFAULT, ASTRAL_CON_BACKGROUND_DEFAULT), BORDER_STYLE_DEFAULT,
                ASTRAL_CON_CREATE_SIZE(10, 10)
            ),
            NULLPTR,
            //children...
        )
    )

    ASTRAL_CON_EVENT input;
    AS_U64 i = 0;
    while(ASTRAL_CON_IS_RUNNING(console)) {
        ASTRAL_CON_GET_EVENT(console, &input);
        switch (input.EVENT_TYPE) {
            case ASTRAL_CON_EVENT_KEY:
                printf("Key event\n");
                break;
            case ASTRAL_CON_EVENT_MOUSE:
                printf("Mouse event\n");
                break;
            default:
                printf("No event\n");
                break;
        }
        if(i++ > 10) break; // TEMP: <-
    }
    printf("Cleaning up\n");
    goto CLEANUP;

CLEANUP:
    ASTRAL_CON_DELETE(console);
    console = NULLPTR; 
    return 0;
}
