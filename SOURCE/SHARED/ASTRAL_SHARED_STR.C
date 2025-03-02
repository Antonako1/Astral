/*+++
Contains shared, non-platform specific code for the ASTRAL library.

For ASTRAL_STRING.H
---*/

#include <ASTRAL.H>

/*+++
ASTRAL_STRING.H
---*/

AS_U64 C_STRLEN(AS_CHAR* STR){
    AS_U64 LENGTH = 0;
    while(STR[LENGTH] != '\0'){
        LENGTH++;
    }
    return LENGTH;
}
AS_U64 C_STRLEN_S(AS_CHAR* STR, AS_U64 SIZE){
    AS_U64 LENGTH = 0;
    while(LENGTH < SIZE && STR[LENGTH] != '\0'){
        LENGTH++;
    }
    return LENGTH;
}

AS_U64 C_STRCMP(AS_CHAR* STR1, AS_CHAR* STR2) {
    AS_U64 I = 0;
    while(STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_STRCMP_S(AS_CHAR* STR1, AS_CHAR* STR2, AS_U64 SIZE) {
    AS_U64 I = 0;
    while(I < SIZE && STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_STRCPY(AS_CHAR* DEST, AS_CHAR* SRC) {  
    AS_U64 I = 0;
    while(SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_STRCPY_S(AS_CHAR* DEST, AS_CHAR* SRC, AS_U64 SIZE){
    AS_U64 I = 0;
    while(I < SIZE && SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_STRCAT(AS_CHAR* DEST, AS_CHAR* SRC) {
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
AS_U64 C_STRCAT_S(AS_CHAR* DEST, AS_CHAR* SRC, AS_U64 SIZE){
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
AS_STRING* ASTRAL_STR_CREATE() {
    AS_STRING* STR = (AS_STRING*)ASTRAL_M_ALLOC(sizeof(AS_STRING));
    if(STR == NULLPTR) return NULLPTR;
    STR->DATA = NULLPTR;
    STR->LENGTH = 0;
    return STR;
}
AS_STRING* ASTRAL_STR_CREATE_EX(AS_CHAR* DATA, AS_U64 MAX_SIZE) {
    AS_U64 SIZE = C_STRLEN_S(DATA, MAX_SIZE);
    AS_STRING* STR = (AS_STRING*)ASTRAL_M_ALLOC(sizeof(AS_STRING));
    STR->DATA = (AS_CHAR*)ASTRAL_M_ALLOC(SIZE);
    C_STRCPY_S(STR->DATA, DATA, SIZE);
    STR->LENGTH = SIZE;
    return STR;
}
AS_U64 ASTRAL_STR_COPY(AS_STRING* DEST, AS_STRING* SRC) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_CHAR*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_STR_COPY_CH(AS_STRING* DEST, AS_CHAR* SRC, AS_U64 SIZE) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_CHAR*)ASTRAL_M_ALLOC(SIZE);
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
    DEST->DATA = (AS_CHAR*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_STR_APPEND_CH(AS_STRING* DEST, AS_CHAR* SRC, AS_U64 SIZE) {
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_CHAR*)ASTRAL_M_ALLOC(SIZE);
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
AS_BOOLEAN ASTRAL_STR_CMP_CH(AS_STRING* STR1, AS_CHAR* STR2, AS_U64 SIZE) {
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

AS_STRING* ASTRAL_STR_DUPLICATE(AS_STRING* STR) {
    AS_STRING* STR_DUP = ASTRAL_STR_CREATE_EX(STR->DATA, STR->LENGTH);
    return STR_DUP;
}

AS_U0 *C_STRCHR(AS_CHAR* STR, AS_CHAR C, AS_U64 N) {
    AS_U64 I = 0;
    AS_U64 J = 0;
    while(STR[I] != '\0') {
        if(STR[I] == C) {
            if(J == N) {
                return &STR[I];
            }
            J++;
        }
        I++;
    }
    return NULLPTR;
}

AS_U0 *ASTRAL_STR_STRCHR(AS_STRING* STR, AS_CHAR C, AS_U64 N) {
    AS_U64 I = 0;
    AS_U64 J = 0;
    while(I < STR->LENGTH) {
        if(STR->DATA[I] == C) {
            if(J == N) {
                return &STR->DATA[I];
            }
            J++;
        }
        I++;
    }
    return NULLPTR;
}

AS_U0 *ASTRAL_WSTR_STRCHR(AS_WSTRING* STR, AS_WCHAR C, AS_U64 N) {
    AS_U64 I = 0;
    AS_U64 J = 0;
    while(I < STR->LENGTH) {
        if(STR->DATA[I] == C) {
            if(J == N) {
                return &STR->DATA[I];
            }
            J++;
        }
        I++;
    }
    return NULLPTR;
}

AS_WSTRING* ASTRAL_WSTR_DUPLICATE(AS_WSTRING* STR) {
    AS_WSTRING* STR_DUP = ASTRAL_WSTR_CREATE_EX(STR->DATA, STR->LENGTH);
    return STR_DUP;
}
AS_U64 C_WSTRLEN(AS_WCHAR* STR) {
    AS_U64 LENGTH = 0;
    while(STR[LENGTH] != '\0') {
        LENGTH++;
    }
    return LENGTH;
}
AS_U64 C_WSTRLEN_S(AS_WCHAR* STR, AS_U64 SIZE) {
    AS_U64 LENGTH = 0;
    while(LENGTH < SIZE && STR[LENGTH] != '\0') {
        LENGTH++;
    }
    return LENGTH;
}
AS_U64 C_WSTRCMP(AS_WCHAR* STR1, AS_WCHAR* STR2){
    AS_U64 I = 0;
    while(STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_WSTRCMP_S(AS_WCHAR* STR1, AS_WCHAR* STR2, AS_U64 SIZE){
    AS_U64 I = 0;
    while(I < SIZE && STR1[I] != '\0' && STR2[I] != '\0') {
        if(STR1[I] != STR2[I]) {
            return 0;
        }
        I++;
    }
    return 1;
}
AS_U64 C_WSTRCPY(AS_WCHAR* DEST, AS_WCHAR* SRC){
    AS_U64 I = 0;
    while(SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_WSTRCPY_S(AS_WCHAR* DEST, AS_WCHAR* SRC, AS_U64 SIZE){
    AS_U64 I = 0;
    while(I < SIZE && SRC[I] != '\0') {
        DEST[I] = SRC[I];
        I++;
    }
    DEST[I] = '\0';
    return I;
}
AS_U64 C_WSTRCAT(AS_WCHAR* DEST, AS_WCHAR* SRC){
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
AS_U64 C_WSTRCAT_S(AS_WCHAR* DEST, AS_WCHAR* SRC, AS_U64 SIZE){
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

AS_U64 ASTRAL_WSTRLEN(AS_WSTRING* STR){
    return STR->LENGTH;
}
AS_U64 ASTRAL_WSTR_COPY(AS_WSTRING* DEST, AS_WSTRING* SRC){
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_WCHAR*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_WSTR_COPY_WCH(AS_WSTRING* DEST, AS_WCHAR* SRC, AS_U64 SIZE){
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_WCHAR*)ASTRAL_M_ALLOC(SIZE);
    DEST->LENGTH = SIZE;
    for(AS_U64 I = 0; I < SIZE; I++) {
        DEST->DATA[I] = SRC[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_WSTR_APPEND(AS_WSTRING* DEST, AS_WSTRING* SRC){
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_WCHAR*)ASTRAL_M_ALLOC(SRC->LENGTH);
    DEST->LENGTH = SRC->LENGTH;
    for(AS_U64 I = 0; I < SRC->LENGTH; I++) {
        DEST->DATA[I] = SRC->DATA[I];
    }
    return DEST->LENGTH;
}
AS_U64 ASTRAL_WSTR_APPEND_WCH(AS_WSTRING* DEST, AS_WCHAR* SRC, AS_U64 SIZE){
    if(DEST->DATA != NULLPTR) {
        ASTRAL_M_FREE(DEST->DATA);
    }
    DEST->DATA = (AS_WCHAR*)ASTRAL_M_ALLOC(SIZE);
    DEST->LENGTH = SIZE;
    for(AS_U64 I = 0; I < SIZE; I++) {
        DEST->DATA[I] = SRC[I];
    }
    return DEST->LENGTH;
}
AS_BOOLEAN ASTRAL_WSTR_CMP(AS_WSTRING* STR1, AS_WSTRING* STR2){
    for(AS_U64 I = 0; I < STR1->LENGTH; I++) {
        if(STR1->DATA[I] != STR2->DATA[I]) {
            return FALSE;
        }
    }
    return TRUE;
}
AS_BOOLEAN ASTRAL_WSTR_CMP_WCH(AS_WSTRING* STR1, AS_WCHAR* STR2, AS_U64 SIZE){
    for(AS_U64 I = 0; I < SIZE; I++) {
        if(STR1->DATA[I] != STR2[I]) {
            return FALSE;
        }
    }
    return TRUE;
}

AS_U0 *C_WSTRCHR(AS_WCHAR* STR, AS_WCHAR C, AS_U64 N){
    AS_U64 I = 0;
    AS_U64 J = 0;
    while(STR[I] != '\0') {
        if(STR[I] == C) {
            if(J == N) {
                return &STR[I];
            }
            J++;
        }
        I++;
    }
    return NULLPTR;
}

AS_WSTRING* ASTRAL_WSTR_CREATE() {
    AS_WSTRING* STR = (AS_WSTRING*)ASTRAL_M_ALLOC(sizeof(AS_WSTRING));
    if(STR==NULLPTR) return NULLPTR;
    STR->DATA = NULLPTR;
    STR->LENGTH = 0;
    return STR;
}
AS_WSTRING* ASTRAL_WSTR_CREATE_EX(AS_WCHAR* DATA, AS_U64 MAX_SIZE) {
    AS_U64 SIZE = C_WSTRLEN_S(DATA, MAX_SIZE);
    AS_WSTRING* STR = (AS_WSTRING*)ASTRAL_M_ALLOC(sizeof(AS_WSTRING));
    STR->DATA = (AS_WCHAR*)ASTRAL_M_ALLOC(SIZE);
    C_WSTRCPY_S(STR->DATA, DATA, SIZE);
    STR->LENGTH = SIZE;
    return STR;
}
AS_BOOLEAN ASTRAL_WSTR_FREE(AS_WSTRING* STR) {
    ASTRAL_M_FREE(STR->DATA);
    ASTRAL_M_FREE(STR);
    STR = NULLPTR;
    return TRUE;
}