/*+++
Contains shared, non-platform specific code for the ASTRAL library.

For ASTRAL_MEMORY.C
---*/

#include <ASTRAL.H>

/*+++
ASTRAL_MEMORY.H
---*/

AS_U0 *ASTRAL_M_COPY(AS_U0 *DEST, AS_U0 *SRC, AS_U64 NUM) {
    // Cast to byte pointers
    AS_U8 *D = (AS_U8*)DEST;
    AS_U8 *S = (AS_U8*)SRC;
    for(AS_U64 I = 0; I < NUM; I++) {
        D[I] = S[I];
    }
    return DEST;
}
AS_U0 *ASTRAL_M_SET(AS_U0 *PTR, AS_U8 VALUE, AS_U64 NUM) {
    AS_U8 *P = (AS_U8*)PTR;
    for(AS_U64 I = 0; I < NUM; I++) {
        P[I] = VALUE;
    }
    return PTR;
}

AS_U0 *ASTRAL_M_ZERO(AS_U0 *PTR, AS_U64 NUM){
    return ASTRAL_M_SET(PTR, 0, NUM);
}