#include "Base.h"

void Delay(u32 delay) {
    if (delay != 0) { while(--delay); }
}

void WarnKiller(void* anything, ...) {}
