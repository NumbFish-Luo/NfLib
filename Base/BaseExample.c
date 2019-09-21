#include "BaseExample.h"
#include <stdio.h>

// C����C++, Ҫ���ȶ���ø���ģ��
// DEF��IMPL���Է���, һ��DEF����.h��, IMPL����.c��
// ע��DEF��IMPL������Ҫһ��
static inline Swap_IMPL(Byte);
Pair_DEF(Byte, Word);
Array_DEF(Word, 10);
Array_IMPL(Word, 10);
Bytes_DEF(20);
Bytes_IMPL(20);

typedef void (*PrintFunc) (const Word*);
ForInRange_IMPL(Array(Word, 10), PrintFunc);
static inline void PrintWord(const Word* w) {
    printf("0x%x\n", *w);
}

// ʾ��
void NfLib_Base_Example(void) {
    SizeType i = 0;
    ByteWord bw;
    Byte byte1 = 0;
    Byte byte2 = 0xFF;
    Bit bit = 0;
    Word word = 0x1234;
    Pair(Byte, Word) pair;
    Array(Word, 10) words;
    Bytes(20) bytes;
    
    // ����ת�� ////////////////////////////////////////////////////////////////
    printf("\n����ת��:\n");
    bw.word[0] = 0x1234;
    printf("0x%x, 0x%x, 0x%x\n", bw.word[0], bw.byte[1], bw.byte[0]);
    // printf: 0x1234, 0x12, 0x34
    
    // ��С���л� //////////////////////////////////////////////////////////////
    printf("\n��С���л�:\n");
    EndianReverse(bw.byte, 2);
    printf("0x%x, 0x%x, 0x%x\n", bw.word[0], bw.byte[1], bw.byte[0]);
    // printf: 0x3412, 0x34, 0x12
    
    // λ���� //////////////////////////////////////////////////////////////////
    printf("\nλ����:\n");
    SetBit(&byte1, 7, 1);
    bit = GetBit(byte1, 7);
    printf("0x%x\n", bit);
    // printf: 0x1
    
    // ���ݽ��� ////////////////////////////////////////////////////////////////
    printf("\n���ݽ���:\n");
    printf("0x%x, 0x%x\n", byte1, byte2);
    // printf: 0x80, 0xFF
    Swap(Byte)(&byte1, &byte2);
    printf("0x%x, 0x%x\n", byte1, byte2);
    // printf: 0xFF, 0x80
    
    // Pair ////////////////////////////////////////////////////////////////////
    printf("\nPair:\n");
    pair.t1 = byte1;
    pair.t2 = word;
    printf("0x%x, 0x%x\n", pair.t1, pair.t2);
    // printf: 0xFF, 0x1234
    
    // Array ///////////////////////////////////////////////////////////////////
    printf("\nArray:\n");
    // ��Init������ʹ��֮ǰҪ�ǵó�ʼ��
    Array(Word, 10, _Init) (&words);
    words.ops->Push(&words, 0x1234);
    words.ops->Push(&words, 0x5678);

    // ���������ForInRange����ӡ����
    ForInRange(Array(Word, 10), PrintFunc) (&words, PrintWord);
    // printf: 0x1234, 0x5678
    words.ops->Pop(&words, &word);
    // Ҳ�����ô�ͳ�ķ�����ӡ����
    for (i = 0; i < words.size; ++i) {
        printf("0x%x\n", words.data[i]);
    }
    // printf: 0x1234
    printf("0x%x\n", word);
    // printf: 0x5678
    
    // Bytes(�൱��Array(Byte, SIZE)) //////////////////////////////////////////
    printf("\nBytes(�൱��Array(Byte, SIZE)):\n");
    Bytes(20, _Init) (&bytes);
    bytes.ops->Push(&bytes, 0x12);
    bytes.ops->Push(&bytes, 0x34);

    for (i = 0; i < bytes.size; ++i) {
        printf("0x%x\n", bytes.data[i]);
    }
    // printf: 0x12, 0x34
    bytes.ops->Pop(&bytes, &byte1);
    for (i = 0; i < bytes.size; ++i) {
        printf("0x%x\n", bytes.data[i]);
    }
    // printf: 0x12
    printf("0x%x\n", byte1);
    // printf: 0x34
}
