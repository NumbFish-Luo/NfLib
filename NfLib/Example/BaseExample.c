#include "Examples.h"

#include <NfLib/Base.h>
#include <NfLib/Swap.h>
#include <stdio.h>

static void PrintBytes(const u8* bytes, u8 len) {
    printf("{ ");
    while (len--) {
        printf("0x%X", *(bytes++));
        printf(len ? ", " : " }\n");
    }
}

Swap_IMPL(u8x4);

void BaseExample(void) {
    u8x4 a, b;
    u8 bcd[8];
    u8 i = 0;

    a.dWord[0] = 0x12345678;
    printf("a.byte = { ");
    for (i = 0; i < 4; ++i) { printf("0x%X ", a.byte[i]); }
    printf("}\n");

    b.byte[0] = 0x90; b.byte[1] = 0xAB; b.byte[2] = 0xCD; b.byte[3] = 0xEF;
    printf("b.dWord[0] = 0x%X\n", b.dWord[0]);

    Swap(u8x4)(&a, &b);
    printf("a.dWord[0] = 0x%X, b.dWord[0] = 0x%X\n", a.dWord[0], b.dWord[0]);

    Ascii2BCD(bcd, "0123456789ABCDEF", 8);
    printf("bcd: ");
    for (i = 0; i < 8; ++i) { printf("%02X ", bcd[i]); }
    printf("\n");
}
