#include <NfLib/Base.h>
#include <NfLib/Swap.h>

static inline Swap_IMPL(Byte);

Bit GetBit(Byte byte, Byte i) { return ((i < 8) && ((byte & (1 << i)) >> i)) ? 1 : 0; }

void SetBit(Byte* byte, Byte i, Bit data) { (i < 8 && data) ? (*byte |= (1 << i)) : (*byte &= ~(1 << i)); }

void EndianReverse(Byte byte[], size_t size) {
    size_t i;
    for (i = 0; i < (size >> 1); ++i) { Swap(Byte)(&(byte[i]), &(byte[size - i - 1])); }
}

u8 ASC2BCD(u8* bcd, const u8* asc, u32 len) {
    u8 c = 0;
    u8 index = 0;
    u8 i;
    static u8 ascii2bcd1[10] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
    static u8 ascii2bcd2[ 6] = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
    len >>= 1;
    for (i = 0; i < len; i++) {
        // first BCD
        if (*asc >= 'A' && *asc <= 'F') {
            index = *asc - 'A';
            c = ascii2bcd2[index] << 4;
        } else if (*asc >= '0' && *asc <= '9') {
            index = *asc - '0';
            c = ascii2bcd1[index] << 4;
        }
        asc++;
        // second BCD
        if (*asc >= 'A' && *asc <= 'F') {
            index = *asc - 'A';
            c |= ascii2bcd2[index];
        } else if (*asc >= '0' && *asc <= '9') {
            index = *asc - '0';
            c |= ascii2bcd1[index];
        }
        asc++;
        *bcd++ = c;
    }
    return 0;
}
