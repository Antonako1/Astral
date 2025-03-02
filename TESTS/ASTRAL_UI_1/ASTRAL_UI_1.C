#include "../../INCLUDE/ASTRAL.H"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    ASTRAL_CONSOLE *console = ASTRAL_CON_CREATE();
    ASTRAL_CON_APPLY_MODES(console, ASTRAL_CON_MODE_MOUSE_INPUT | ASTRAL_CON_MODE_IGNORE_CTRL_C);

    printf("Console root id: %d\n", console->ROOT->ID);
    printf("Console root height: %llu\n", console->ROOT->STYLING.SIZE.HEIGHT);
    printf("Console root width: %llu\n", console->ROOT->STYLING.SIZE.WIDTH);
    
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
    return 0;
}
