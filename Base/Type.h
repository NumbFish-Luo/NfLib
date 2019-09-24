#ifndef NFLIB_TYPE_H
#define NFLIB_TYPE_H

typedef enum { False = 0, True = 1 } Bool, Bit;
typedef char*                        Str;
typedef const char*                  CStr;

typedef char                         i8;
typedef short                        i16;
typedef int                          i32;
typedef long long                    i64;

typedef unsigned char                u8 , UChar , Byte , SmallSizeType; // 比SizeType更小的SmallSizeType
typedef unsigned short               u16, UShort, Word , SizeType     ; // SizeType一般数据大小的表示u16也就够用了
typedef unsigned int                 u32, UInt  , DWord, HashType     ; // HashType哈希值类型
typedef unsigned long long           u64, ULL   , QWord;

typedef union ByteWord               ByteWord , u8x2;
typedef union ByteDWord              ByteDWord, u8x4;
typedef union ByteQWord              ByteQWord, u8x8;

union ByteWord {
    Byte byte[2];
    Word word[1];
};

union ByteDWord {
    Byte  byte [4];
    Word  word [2];
    DWord dWord[1];
};

union ByteQWord {
    Byte  byte [8];
    Word  word [4];
    DWord dWord[2];
    QWord qWord[1];
};

Bit  GetBit(Byte byte, Byte i); // 获取字节第i位二进制数据
void SetBit(Byte* byte, Byte i, Bit data); // 设置字节第i位二进制数据
void EndianReverse(Byte byte[], SizeType size); // 大小端转换

#endif // NFLIB_TYPE_H
