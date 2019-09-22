#ifndef NFLIB_TYPE_H
#define NFLIB_TYPE_H

#define False 0
#define True  1

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef u8 Bool;
typedef u8 Bit;
typedef u8 Byte;
typedef u16 Word;
typedef u32 DWord;
typedef u64 QWord;

typedef u16 SizeType; // 一般数据大小的表示u16也就够用了
typedef u16 IdxType; // Index

typedef const char* String;

// 类型转换
typedef union ByteWord ByteWord;
typedef union ByteDWord ByteDWord;
typedef union ByteQWord ByteQWord;

union ByteWord {
    Byte byte[2];
    Word word[1];
};

union ByteDWord {
    Byte byte[4];
    Word word[2];
    DWord dWord[1];
};

union ByteQWord {
    Byte byte[8];
    Word word[4];
    DWord dWord[2];
    QWord qWord[1];
};

Bit GetBit(Byte byte, Byte i); // 获取字节第i位二进制数据
void SetBit(Byte* byte, Byte i, Bit data); // 设置字节第i位二进制数据
void EndianReverse(Byte byte[], SizeType size); // 大小端转换

#endif // NFLIB_TYPE_H
