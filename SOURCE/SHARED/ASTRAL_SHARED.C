/*+++
Contains shared, non-platform specific code for the ASTRAL library.
---*/

#include <ASTRAL.H>
/*+++
ASTRAL_MEMORY.H
---*/
ASTRAL_M_ARENA ASTRAL_M_ARENA_ALLOC(AS_U64 SIZE, AS_U8* MEMORY) {
    ASTRAL_M_ARENA ARENA;
    ARENA.SIZE = SIZE;
    ARENA.MEMORY = MEMORY;
    ARENA.NEXT_BLOCK = ARENA.MEMORY;
    return ARENA;
}

AS_U64 ASTRAL_M_MIN_SIZE(AS_U0) {
    return 1024;
}

/*+++
ASTRAL_STRING.H
---*/

AS_U64 C_STRLEN(AS_U8* STR){
    AS_U64 LENGTH = 0;
    while(STR[LENGTH] != '\0'){
        LENGTH++;
    }
    return LENGTH;
}
AS_U64 C_STRLEN_S(AS_U8* STR, AS_U64 SIZE){
    AS_U64 LENGTH = 0;
    while(LENGTH < SIZE && STR[LENGTH] != '\0'){
        LENGTH++;
    }
    return LENGTH;
}
