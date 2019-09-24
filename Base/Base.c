#include "Base.h"

HashType StrHash(CStr str) {
    HashType hash = 5381;
    HashType c = 0;
    while (c = (HashType)*str++) { hash = ((hash << 5) + hash) + c; } // hash * 33 + c
    return hash;
}
void Delay(u32 delay) { if (delay != 0) { while(--delay); } }
void WarnKiller(void* anything, ...) {}
