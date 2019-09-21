#ifndef NFLIB_BASE_H
#define NFLIB_BASE_H

#define False 0
#define True  1

// #if编辑器辅助宏, 主要用于分清层次关系
#define _LAYER(Layer, LayerName) 1

#if _LAYER(0, "typedef") ///////////////////////////////////////////////////////
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

// 类型转换
typedef union ByteWord ByteWord;
typedef union ByteDWord ByteDWord;
typedef union ByteQWord ByteQWord;

typedef const char* String;
#endif // (0, "typedef") ///////////////////////////////////////////////////////

#if _LAYER(0, "union") /////////////////////////////////////////////////////////
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
#endif // (0, "union") /////////////////////////////////////////////////////////

#if _LAYER(0, "function") //////////////////////////////////////////////////////
Bit GetBit(Byte byte, Byte i); // 获取字节第i位二进制数据
void SetBit(Byte* byte, Byte i, Bit data); // 设置字节第i位二进制数据
void EndianReverse(Byte byte[], SizeType size); // 大小端转换
void Delay(u32 delay); // 简单延时
void WarnKiller(void* anything, ...); // 忽略定义但未引用警告
#endif // (0, "function") //////////////////////////////////////////////////////

#if _LAYER(0, "Swap") //////////////////////////////////////////////////////////
#define Swap(T) Swap$_##T##_$
#define Swap_DEF(T) void Swap(T)(T* lhs, T* rhs)
#define Swap_IMPL(T) void Swap(T)(T* lhs, T* rhs) {                             \
    T tmp;                                                                      \
    tmp = *lhs;                                                                 \
    *lhs = *rhs;                                                                \
    *rhs = tmp;                                                                 \
}
#endif // (0, "Swap") //////////////////////////////////////////////////////////

#if _LAYER(0, "Pair") //////////////////////////////////////////////////////////
#define Pair(T1, T2) Pair$_##T1##_$$_##T2##_$
#define Pair_DEF(T1, T2) typedef struct Pair(T1, T2) { T1 t1; T2 t2; } Pair(T1, T2)
#define Pair_IMPL(T1, T2) // nothing~
#endif // (0, "Pair") //////////////////////////////////////////////////////////

#if _LAYER(0, "Array") /////////////////////////////////////////////////////////
#define Array(T, SIZE, ...) Array$_##T##_$$_##SIZE##_$##__VA_ARGS__
#if _LAYER(1, "Array_DEF") /////////////////////////////////////////////////////
#define Array_DEF(T, SIZE)                                                      \
/* typedef */                                                                   \
typedef struct Array(T, SIZE) Array(T, SIZE);                                   \
typedef struct Array(T, SIZE, _ops) Array(T, SIZE, _ops);                       \
/* Array */                                                                     \
struct Array(T, SIZE) {                                                         \
    T data[SIZE];                                                               \
    SizeType size;                                                              \
    Array(T, SIZE, _ops)* ops;                                                  \
};                                                                              \
/* ops */                                                                       \
struct Array(T, SIZE, _ops) {                                                   \
    SizeType (*MaxSize) (void);                                                 \
    Bool     (*Push   ) (Array(T, SIZE)* this, T data);                         \
    Bool     (*Pop    ) (Array(T, SIZE)* this, T* data);                        \
    void     (*SetData) (Array(T, SIZE)* this, T data[SIZE]);                   \
};                                                                              \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this)
#endif // (1, "Array_DEF") /////////////////////////////////////////////////////

#if _LAYER(1, "Array_IMPL") ////////////////////////////////////////////////////
#define Array_IMPL(T, SIZE)                                                     \
/* static function */                                                           \
static inline SizeType Array(T, SIZE, _MaxSize) (void) {                        \
    return SIZE;                                                                \
}                                                                               \
static inline Bool Array(T, SIZE, _Push) (Array(T, SIZE)* this, T data) {       \
    if (this->size < SIZE) {                                                    \
        this->data[this->size++] = data;                                        \
        return True;                                                            \
    }                                                                           \
    return False;                                                               \
}                                                                               \
static inline Bool Array(T, SIZE, _Pop) (Array(T, SIZE)* this, T* data) {       \
    if (this->size) {                                                           \
        *data = this->data[--this->size];                                       \
        return True;                                                            \
    }                                                                           \
    return False;                                                               \
}                                                                               \
static inline void Array(T, SIZE, _SetData) (Array(T, SIZE)* this, T data[SIZE]) { \
    SizeType i = 0;                                                             \
    for (; i < SIZE; ++i) {                                                     \
        this->data[i] = data[i];                                                \
    }                                                                           \
    this->size = SIZE;                                                          \
}                                                                               \
static Array(T, SIZE, _ops)* Array(T, SIZE, Ops) (void) {                       \
    static Array(T, SIZE, _ops) ops;                                            \
    static Bool init = False;                                                   \
    if (init == False) {                                                        \
        init = True;                                                            \
        ops.MaxSize = Array(T, SIZE, _MaxSize);                                 \
        ops.Push    = Array(T, SIZE, _Push   );                                 \
        ops.Pop     = Array(T, SIZE, _Pop    );                                 \
        ops.SetData = Array(T, SIZE, _SetData);                                 \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this) {                             \
    this->size = 0;                                                             \
    this->ops = Array(T, SIZE, Ops) ();                                         \
}
#endif // (1, "Array_IMPL") ////////////////////////////////////////////////////
#endif // (0, "Array") /////////////////////////////////////////////////////////

#if _LAYER(0, "Bytes") /////////////////////////////////////////////////////////
#define Bytes(SIZE, ...) Array(Byte, SIZE, __VA_ARGS__)
#define Bytes_DEF(SIZE)  Array_DEF(Byte, SIZE)
#define Bytes_IMPL(SIZE) Array_IMPL(Byte, SIZE)
#endif // (0, "Bytes") /////////////////////////////////////////////////////////

#endif // NFLIB_BASE_H
