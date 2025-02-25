#include "../../INCLUDE/ASTRAL.H"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    AS_U64 min_size = ASTRAL_M_MIN_SIZE();
    ASTRAL_M_ARENA arena = ASTRAL_M_ARENA_ALLOC(min_size, (AS_U0*)malloc(min_size));
    ASTRAL_CONSOLE console = ASTRAL_CON_CREATE(&arena);
    ASTRAL_CON_APPLY_MODES(&console, ASTRAL_CON_MODE_IGNORE_CTRL_C | ASTRAL_CON_MODE_CURSOR_VISIBLE);
    ASTRAL_CONSOLE_EVENT input;
    AS_U64 i = 0;
    printf("Press any key to exit\n");
    while(console.RUNNING) {
        ASTRAL_CON_GET_EVENT(&console, &input);
        printf("Event type: %llu\n", input.EVENT_TYPE);
        if(input.EVENT_TYPE == ASTRAL_CON_EVENT_NO_EVENT) {
            printf("No event\n");
        }
    }
    free(arena.MEMORY);
    return 0;
}
