#include "Examples.h"

#include <NfLib/Base.h>
#include <NfLib/R2L.h>
#include <NfLib/Swap.h>
#include <stdio.h>

static void PrintBytes(const u8* bytes, u8 len) {
    printf("{ ");
    while (len--) {
        printf("0x%X", *(bytes++));
        printf(len ? ", " : " }\n");
    }
}

#if _LAYER(0, "template") //////////////////////////////////////////////////////
R2L_DEF(u8);
R2L_IMPL(u8);
Swap_IMPL(u8x4);
#endif // _LAYER(0, "template")

void BaseExample(void) {
    u8x4 a, b;

#if _LAYER(0, "u8x4") //////////////////////////////////////////////////////////
    a.dWord[0] = 0x12345678;
    printf("a.byte = ");
    PrintBytes(a.byte, 4);

    b.byte[0] = 0x90; b.byte[1] = 0xAB; b.byte[2] = 0xCD; b.byte[3] = 0xEF;
    printf("b.dWord[0] = 0x%X\n", b.dWord[0]);
#endif // _LAYER(0, "u8x4")

#if _LAYER(0, "swap") //////////////////////////////////////////////////////////
    Swap(u8x4)(&a, &b);
    printf("a.dWord[0] = 0x%X, b.dWord[0] = 0x%X\n", a.dWord[0], b.dWord[0]);
#endif // _LAYER(0, "swap")

#if _LAYER(0, "right value to left value") /////////////////////////////////////
    // PrintBytes(0xAB, 1); // ERROR! :-(
    PrintBytes(R2L(u8)(0xAB).data, 1); // It's OK! :-)
#endif // _LAYER(0, "right value to left value")
}
