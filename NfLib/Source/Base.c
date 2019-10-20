#include <NfLib/Base.h>
#include <NfLib/Swap.h>

static inline Swap_IMPL(Byte);
Bit GetBit(Byte byte, Byte i) { return ((i < 8) && ((byte & (1 << i)) >> i)) ? 1 : 0; }
void SetBit(Byte* byte, Byte i, Bit data) { (i < 8 && data) ? (*byte |= (1 << i)) : (*byte &= ~(1 << i)); }
void EndianReverse(Byte byte[], size_t size) {
    size_t i;
    for (i = 0; i < (size >> 1); ++i) { Swap(Byte)(&(byte[i]), &(byte[size - i - 1])); }
}
u8x1 ToU8x1(u8  value) { u8x1 tmp; tmp. byte[0] = value; return tmp; }
u8x2 ToU8x2(u16 value) { u8x2 tmp; tmp. word[0] = value; return tmp; }
u8x4 ToU8x4(u32 value) { u8x4 tmp; tmp.dWord[0] = value; return tmp; }
u8x8 ToU8x8(u64 value) { u8x8 tmp; tmp.qWord[0] = value; return tmp; }
