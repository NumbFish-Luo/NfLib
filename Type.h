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

typedef u16 SizeType; // һ�����ݴ�С�ı�ʾu16Ҳ�͹�����
typedef u16 IdxType; // Index

typedef const char* String;

// ����ת��
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

Bit GetBit(Byte byte, Byte i); // ��ȡ�ֽڵ�iλ����������
void SetBit(Byte* byte, Byte i, Bit data); // �����ֽڵ�iλ����������
void EndianReverse(Byte byte[], SizeType size); // ��С��ת��

#endif // NFLIB_TYPE_H
