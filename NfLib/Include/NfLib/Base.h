#ifndef _NFLIB_BASE_H
#define _NFLIB_BASE_H

#include <stddef.h>
#include <stdbool.h>

#define __WINDOWS_10__ 1
#define __LPC177X_8X__ 0
#define __DEBUG_MODE__ 0

#if __WINDOWS_10__
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)
#pragma warning(disable:28159)
#define GET_TICK_COUNT() GetTickCount()
#define ABORT() abort()
typedef char      i8;
typedef short     i16;
typedef int       i32;
typedef long long i64;

#elif __LPC177X_8X__
#include "base/time.h"
#define GET_TICK_COUNT() get_tick()
#define ABORT() while(1)

#else
#define GET_TICK_COUNT()
#define ABORT()
#endif // __WINDOWS_10__

#if __DEBUG_MODE__
extern const char* g_assert;
#define ASSERT(IS_TRUE, STR) \
    do {                     \
        if (!(IS_TRUE)) {    \
            g_assert = STR;  \
            ABORT();         \
        }                    \
    } while (0);
#else
#define ASSERT(IS_TRUE, STR)
#endif // __DEBUG_MODE__

typedef bool               u1 , Bit;
typedef unsigned char      u8 , Byte;
typedef unsigned short     u16, Word;
typedef unsigned int       u32, DWord;
typedef unsigned long long u64, QWord;

typedef union { Byte byte[1];                                               }            u8x1;
typedef union { Byte byte[2]; Word word[1];                                 } ByteWord,  u8x2;
typedef union { Byte byte[4]; Word word[2]; DWord dWord[1];                 } ByteDWord, u8x4;
typedef union { Byte byte[8]; Word word[4]; DWord dWord[2]; QWord qWord[1]; } ByteQWord, u8x8;

inline Bit GetBit(Byte byte, Byte i);
inline void SetBit(Byte* byte, Byte i, Bit data);
void Ascii2BCD(u8* bcd, const u8* ascii, size_t bcdSize);

#endif // _NFLIB_BASE_H
