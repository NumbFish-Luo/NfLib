#include <NfLib/Base.h>
#include <NfLib/Swap.h>

static inline Swap_IMPL(Byte);

inline Assert(bool isTrue, const char* name) { if (!isTrue) { g_assertName = name; while (1); } }

Bit GetBit(Byte byte, Byte i) { return ((i < 8) && ((byte & (1 << i)) >> i)) ? 1 : 0; }

void SetBit(Byte* byte, Byte i, Bit data) { (i < 8 && data) ? (*byte |= (1 << i)) : (*byte &= ~(1 << i)); }

void EndianReverse(Byte byte[], size_t size) {
    size_t i;
    for (i = 0; i < (size >> 1); ++i) { Swap(Byte)(&(byte[i]), &(byte[size - i - 1])); }
}

void ASC2BCD(u8* bcd, const u8* asc, u16 bcdSize) {
    u8 i;
    for (i = 0; i < bcdSize; i++) {
        // first BCD
             if ('0' <= *asc && *asc <= '9') { *bcd = (*asc - '0' + 0x00) << 4; }
        else if ('a' <= *asc && *asc <= 'f') { *bcd = (*asc - 'a' + 0x0A) << 4; }
        else if ('A' <= *asc && *asc <= 'F') { *bcd = (*asc - 'A' + 0x0A) << 4; }
        ++asc;
        // second BCD
             if ('0' <= *asc && *asc <= '9') { *bcd |= (*asc - '0' + 0x00); }
        else if ('a' <= *asc && *asc <= 'f') { *bcd |= (*asc - 'a' + 0x0A); }
        else if ('A' <= *asc && *asc <= 'F') { *bcd |= (*asc - 'A' + 0x0A); }
        ++asc;
        ++bcd;
    }
}
