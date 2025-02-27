#include "../../INCLUDE/ASTRAL.H"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    AS_U64 min_size = ASTRAL_M_MIN_SIZE();
    ASTRAL_M_ARENA arena = ASTRAL_M_ARENA_ALLOC(min_size, (AS_U0*)malloc(min_size));
    
    ASTRAL_CONSOLE console = ASTRAL_CON_CREATE(&arena);
    
    ASTRAL_CON_APPLY_MODES(&console, ASTRAL_CON_MODE_MOUSE_INPUT | ASTRAL_CON_MODE_IGNORE_CTRL_C);
    
    ASTRAL_CON_EVENT input;
    AS_U64 i = 0;
    while(ASTRAL_CON_IS_RUNNING(&console)) {
        ASTRAL_CON_GET_EVENT(&console, &input);
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
        if(i++ > 10) break;
    }
    ASTRAL_CON_END_CONSOLE(&console);
    return 0;
}
