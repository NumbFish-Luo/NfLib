#include <NfLib/Base.h>
#include <NfLib/Swap.h>

static inline Swap_IMPL(Byte);
Bit GetBit(Byte byte, Byte i) { return ((i < 8) && ((byte & (1 << i)) >> i)) ? 1 : 0; }
void SetBit(Byte* byte, Byte i, Bit data) { (i < 8 && data) ? (*byte |= (1 << i)) : (*byte &= ~(1 << i)); }
void EndianReverse(Byte byte[], size_t size) {
    size_t i;
    for (i = 0; i < (size >> 1); ++i) { Swap(Byte)(&(byte[i]), &(byte[size - i - 1])); }
}
