#include <NfLib/Base.h>
#include <NfLib/Swap.h>

#if __DEBUG_MODE__
const char* g_assert = "";
#endif

inline Bit GetBit(Byte byte, Byte i) { return ((i < 8) && ((byte & (1 << i)) >> i)) ? 1 : 0; }
inline void SetBit(Byte* byte, Byte i, Bit data) { (i < 8 && data) ? (*byte |= (1 << i)) : (*byte &= ~(1 << i)); }
void Ascii2BCD(u8* bcd, const u8* ascii, size_t bcdSize) {
    u8 i;
    for (i = 0; i < bcdSize; ++i) {
        // first BCD
             if ('0' <= *ascii && *ascii <= '9') { *bcd = (*ascii - '0' + 0x00) << 4; }
        else if ('a' <= *ascii && *ascii <= 'f') { *bcd = (*ascii - 'a' + 0x0A) << 4; }
        else if ('A' <= *ascii && *ascii <= 'F') { *bcd = (*ascii - 'A' + 0x0A) << 4; }
        ++ascii;
        // second BCD
             if ('0' <= *ascii && *ascii <= '9') { *bcd |= (*ascii - '0' + 0x00); }
        else if ('a' <= *ascii && *ascii <= 'f') { *bcd |= (*ascii - 'a' + 0x0A); }
        else if ('A' <= *ascii && *ascii <= 'F') { *bcd |= (*ascii - 'A' + 0x0A); }
        ++ascii;
        ++bcd;
    }
}
