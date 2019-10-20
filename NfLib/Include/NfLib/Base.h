#ifndef _NFLIB_BASE_H
#define _NFLIB_BASE_H

#include <stddef.h>
#include <stdbool.h>

#define _LAYER(layer, name) 1

#if _LAYER(0, "macro") /////////////////////////////////////////////////////////
#include <Windows.h>
#define GET_TICK_COUNT() (u32)GetTickCount64()
#pragma warning(disable:4996)
#endif // _LAYER(0, "typedef")

#if _LAYER(0, "typedef") ///////////////////////////////////////////////////////
typedef bool        Bit;
typedef char*       Str;
typedef const char* CStr;

typedef char      i8;
typedef short     i16;
typedef int       i32;
typedef long long i64;

typedef unsigned char      u8, Byte;
typedef unsigned short     u16, Word;
typedef unsigned int       u32, DWord;
typedef unsigned long long u64, QWord;

typedef union {
    Word word[1];
    Byte byte[2];
} ByteWord, u8x2;

typedef union {
    DWord dWord[1];
    Word word[2];
    Byte byte[4];
} ByteDWord, u8x4;

typedef union {
    QWord qWord[1];
    DWord dWord[2];
    Word word[4];
    Byte byte[8];
} ByteQWord, u8x8;
#endif // _LAYER(0, "typedef")

#if _LAYER(0, "function") //////////////////////////////////////////////////////
Bit GetBit(Byte byte, Byte i);
void SetBit(Byte* byte, Byte i, Bit data);
void EndianReverse(Byte byte[], size_t size);
u8x2 ToU8x2(u16 value);
u8x4 ToU8x4(u32 value);
u8x8 ToU8x8(u64 value);
#endif // _LAYER(0, "function")

#endif // _NFLIB_BASE_H
