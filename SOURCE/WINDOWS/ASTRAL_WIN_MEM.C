/*+++
Contains Windows specific code for the ASTRAL library.

For ASTRAL_MEMORY.H
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