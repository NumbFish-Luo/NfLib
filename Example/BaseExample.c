#include <stdio.h>
#include "BaseExample.h"

#include <NfLib/Base/Array.h>
#include <NfLib/Base/Base.h>
#include <NfLib/Base/Bytes.h>
#include <NfLib/Base/ForEach.h>
#include <NfLib/Base/ForInRange.h>
#include <NfLib/Base/Layer.h>
#include <NfLib/Base/Pair.h>
#include <NfLib/Base/Swap.h>
#include <NfLib/Base/Type.h>
#include <NfLib/Base/Max_Min.h>

// C����C++, Ҫ���ȶ���ø���ģ��
// DEF��IMPL���Է���, һ��DEF����.h��, IMPL����.c��
// ע��DEF��IMPL������Ҫһ��
static inline Swap_IMPL(Byte);
static inline Max_IMPL(Byte);
static inline Min_IMPL(Byte);
Pair_DEF(Byte, Word);
Array_DEF(Word, 10);
Array_IMPL(Word, 10);
Bytes_DEF(20);
Bytes_IMPL(20);

typedef void (*PrintFunc) (const Word*);
ForInRange_IMPL(Array(Word, 10), PrintFunc);
static inline void PrintWord(const Word* w) { printf("0x%X\n", *w); }

// ʾ��
void Base_Example(void) {
    SizeType i = 0;
    ByteWord bw;
    Byte byte1 = 0;
    Byte byte2 = 0xFF;
    Bit bit = 0;
    Word word = 0x1234;
    Pair(Byte, Word) pair;
    Array(Word, 10) words;
    Bytes(20) bytes;
    
    // �ַ�����ϣֵ ////////////////////////////////////////////////////////////
    printf("\n\"NfLib\"��ϣֵ = 0x%X\n", StrHash("NfLib"));
    // >> 0xDBBB750
    
    // ����ת�� ////////////////////////////////////////////////////////////////
    bw.word[0] = 0x1234;
    printf("\n����ת��: 0x%X, 0x%X, 0x%X\n", bw.word[0], bw.byte[1], bw.byte[0]);
    // >> 0x1234, 0x12, 0x34
    
    // ��С���л� //////////////////////////////////////////////////////////////
    EndianReverse(bw.byte, 2);
    printf("\n��С���л�: 0x%X, 0x%X, 0x%X\n", bw.word[0], bw.byte[1], bw.byte[0]);
    // >> 0x3412, 0x34, 0x12
    
    // λ���� //////////////////////////////////////////////////////////////////
    SetBit(&byte1, 7, 1);
    bit = GetBit(byte1, 7);
    printf("\nλ����: 0x%X\n", bit);
    // >> 0x1
    
    // ���ݽ��� ////////////////////////////////////////////////////////////////
    printf("\n���ݽ���:\n");
    printf("0x%X, 0x%X\n", byte1, byte2);
    // >> 0x80, 0xFF
    Swap(Byte)(&byte1, &byte2);
    printf("0x%X, 0x%X\n", byte1, byte2);
    // >> 0xFF, 0x80
    
    // Max Min /////////////////////////////////////////////////////////////////
    printf("\nMax = 0x%x, Min = 0x%x\n", Max(Byte)(byte1, byte2), Min(Byte)(byte1, byte2));

    // Pair ////////////////////////////////////////////////////////////////////
    pair.t1 = byte1;
    pair.t2 = word;
    printf("\nPair: 0x%X, 0x%X\n", pair.t1, pair.t2);
    // >> 0xFF, 0x1234
    
    // Array ///////////////////////////////////////////////////////////////////
    printf("\nArray:\n");
    // ��Init������ʹ��֮ǰҪ�ǵó�ʼ��
    Array(Word, 10, _Init) (&words);
    words.ops->PushBack(&words, 0x1234);
    words.ops->PushBack(&words, 0x5678);

    // ���������ForInRange����ӡ����
    ForInRange(Array(Word, 10), PrintFunc) (&words, PrintWord);
    // >> 0x1234
    // >> 0x5678
    words.ops->PopBack(&words, &word);
    // Ҳ�����ô�ͳ�ķ�����ӡ����
    for (i = 0; i < words.size; ++i) {
        printf("0x%X\n", words.data[i]);
    }
    // >> 0x1234
    printf("0x%X\n", word);
    // >> 0x5678
    
    // Bytes(�൱��Array(Byte, SIZE)) //////////////////////////////////////////
    printf("\nBytes(�൱��Array(Byte, SIZE)):\n");
    Bytes(20, _Init) (&bytes);
    bytes.ops->PushBack(&bytes, 0x12);
    bytes.ops->PushBack(&bytes, 0x34);

    for (i = 0; i < bytes.size; ++i) {
        printf("0x%X\n", bytes.data[i]);
    }
    // >> 0x12
    // >> 0x34
    bytes.ops->PopBack(&bytes, &byte1);
    for (i = 0; i < bytes.size; ++i) {
        printf("0x%X\n", bytes.data[i]);
    }
    // >> 0x12
    printf("0x%X\n", byte1);
    // >> 0x34
}
