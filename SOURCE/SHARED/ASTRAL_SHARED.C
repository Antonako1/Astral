/*+++
Contains shared, non-platform specific code for the ASTRAL library.
---*/

#include <ASTRAL.H>
/*+++
ASTRAL_MEMORY.H
---*/



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

AS_U64 C_STRCMP(AS_U8* STR1, AS_U8* STR2) {
    AS_U64 I = 0;
    while(STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_STRCMP_S(AS_U8* STR1, AS_U8* STR2, AS_U64 SIZE) {
    AS_U64 I = 0;
    while(I < SIZE && STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_STRCPY(AS_U8* DEST, AS_U8* SRC) {  
    AS_U64 I = 0;
    while(SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_STRCPY_S(AS_U8* DEST, AS_U8* SRC, AS_U64 SIZE){
    AS_U64 I = 0;
    while(I < SIZE && SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_STRCAT(AS_U8* DEST, AS_U8* SRC) {
    AS_U64 I = 0;
    while(DEST[I] != '\0') {
        I++;
    }
    AS_U64 J = 0;
    while(SRC[J] != '\0') {
        DEST[I] = SRC[J];
        I++;
        J++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_STRCAT_S(AS_U8* DEST, AS_U8* SRC, AS_U64 SIZE){
    AS_U64 I = 0;
    while(DEST[I] != '\0') {
        I++;
    }
    AS_U64 J = 0;
    while(J < SIZE && SRC[J] != '\0') {
        DEST[I] = SRC[J];
        I++;
        J++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 ASTRAL_STRLEN(AS_STRING* STR) {
    return STR->LENGTH;
}
AS_STRING* ASTRAL_STR_CREATE(AS_U64 SIZE) {
    AS_STRING* STR = (AS_STRING*)ASTRAL_M_ALLOC(sizeof(AS_STRING));
    STR->DATA = (AS_U8*)ASTRAL_M_ALLOC(SIZE);
    STR->LENGTH = SIZE;
    return STR;
}
AS_STRING* ASTRAL_STR_CREATE(AS_U64 SIZE, AS_U8* DATA, AS_U64 DATA_SIZE) {
    AS_STRING* STR = (AS_STRING*)ASTRAL_M_ALLOC(sizeof(AS_STRING));
    STR->DATA = (AS_U8*)ASTRAL_M_ALLOC(SIZE);
    C_STRCPY_S(STR->DATA, DATA, DATA_SIZE);
    STR->LENGTH = SIZE;
    return STR;
}
AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_STRING* SRC) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_U8*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_U8* SRC, AS_U64 SIZE) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_U8*)ASTRAL_M_ALLOC(SIZE);
    DEST->LENGTH = SIZE;
    for(AS_U64 I = 0; I < SIZE; I++) {
        DEST->DATA[I] = SRC[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_STR_APPEND(AS_STRING* DEST, AS_STRING* SRC) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_U8*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_STR_APPEND(AS_STRING* DEST, AS_U8* SRC, AS_U64 SIZE) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_U8*)ASTRAL_M_ALLOC(SIZE);
    DEST->LENGTH = SIZE;
    for(AS_U64 I = 0; I < SIZE; I++) {
        DEST->DATA[I] = SRC[I];
    }
    return DEST->LENGTH;
}
AS_BOOLEAN ASTRAL_STR_CMP(AS_STRING* STR1, AS_STRING* STR2) {
    for(AS_U64 I = 0; I < STR1->LENGTH; I++) {
        if(STR1->DATA[I] != STR2->DATA[I]) {
            return FALSE;
        }
    }
    return TRUE;
}
AS_BOOLEAN ASTRAL_STR_CMP(AS_STRING* STR1, AS_U8* STR2, AS_U64 SIZE) {
    for(AS_U64 I = 0; I < SIZE; I++) {
        if(STR1->DATA[I] != STR2[I]) {
            return FALSE;
        }
    }
    return TRUE;
}
AS_BOOLEAN ASTRAL_STR_FREE(AS_STRING* STR) {
    ASTRAL_M_FREE(STR->DATA);
    ASTRAL_M_FREE(STR);
    STR = NULLPTR;
    return TRUE;
}

/*+++
ASTRAL_CON.H
---*/

AS_BOOLEAN ASTRAL_CON_IS_RUNNING(ASTRAL_CONSOLE* CONSOLE) {
    return CONSOLE->RUNNING;
}

AS_U0 SET_CON_COLOUR_F(ASTRAL_CON_COLOUR* COLOUR, AS_U8 R, AS_U8 G, AS_U8 B, AS_U8 A) {
    COLOUR->R_F = R;
    COLOUR->G_F = G;
    COLOUR->B_F = B;
    COLOUR->A_F = A;
}
AS_U0 SET_CON_COLOUR_F(ASTRAL_CON_COLOUR* COLOUR, AS_U32 RGBA) {
    COLOUR->R_F = (AS_U8)(RGBA >> 24);
    COLOUR->G_F = (AS_U8)(RGBA >> 16);
    COLOUR->B_F = (AS_U8)(RGBA >> 8);
    COLOUR->A_F = (AS_U8)(RGBA);
}
AS_U0 SET_CON_COLOUR_B(ASTRAL_CON_COLOUR* COLOUR, AS_U8 R, AS_U8 G, AS_U8 B, AS_U8 A) {
    COLOUR->R_B = R;
    COLOUR->G_B = G;
    COLOUR->B_B = B;
    COLOUR->A_B = A;
}
AS_U0 SET_CON_COLOUR_B(ASTRAL_CON_COLOUR* COLOUR, AS_U32 RGBA) {
    COLOUR->R_B = (AS_U8)(RGBA >> 24);
    COLOUR->G_B = (AS_U8)(RGBA >> 16);
    COLOUR->B_B = (AS_U8)(RGBA >> 8);
    COLOUR->A_B = (AS_U8)(RGBA);
}