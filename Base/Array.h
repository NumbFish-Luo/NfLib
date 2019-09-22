#ifndef NFLIB_ARRAY_H
#define NFLIB_ARRAY_H

// Array ///////////////////////////////////////////////////////////////////////
#define _Array(T, SIZE, ...) Array$_##T##_$$_##SIZE##_$##__VA_ARGS__
#define Array(T, SIZE, ...) _Array(T, SIZE, __VA_ARGS__)

// DEF /////////////////////////////////////////////////////////////////////////
#define _Array_DEF(T, SIZE)                                                     \
/* typedef */                                                                   \
typedef struct Array(T, SIZE)       Array(T, SIZE);                             \
typedef struct Array(T, SIZE, _ops) Array(T, SIZE, _ops);                       \
typedef T*                          Array(T, SIZE, _Iter);                      \
/* Array */                                                                     \
struct Array(T, SIZE) {                                                         \
    T data[SIZE];                                                               \
    SizeType size;                                                              \
    Array(T, SIZE, _ops)* ops;                                                  \
};                                                                              \
/* ops */                                                                       \
struct Array(T, SIZE, _ops) {                                                   \
    SizeType              (*MaxSize) (void);                                    \
    Bool                  (*Push   ) (Array(T, SIZE)* this, T data);            \
    Bool                  (*Pop    ) (Array(T, SIZE)* this, T* data);           \
    void                  (*SetData) (Array(T, SIZE)* this, T data[SIZE]);      \
    Array(T, SIZE, _Iter) (*Begin  ) (Array(T, SIZE)* this);                    \
    Array(T, SIZE, _Iter) (*End    ) (Array(T, SIZE)* this);                    \
};                                                                              \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this)
#define Array_DEF(T, SIZE) _Array_DEF(T, SIZE)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _Array_IMPL(T, SIZE)                                                    \
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
static inline Array(T, SIZE, _Iter) Array(T, SIZE, _Begin) (Array(T, SIZE)* this) { \
    return &this->data[0];                                                      \
}                                                                               \
static inline Array(T, SIZE, _Iter) Array(T, SIZE, _End) (Array(T, SIZE)* this) { \
    return &this->data[this->size];                                             \
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
        ops.Begin   = Array(T, SIZE, _Begin  );                                 \
        ops.End     = Array(T, SIZE, _End    );                                 \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* Init */                                                                      \
void Array(T, SIZE, _Init) (Array(T, SIZE)* this) {                             \
    this->size = 0;                                                             \
    this->ops = Array(T, SIZE, Ops) ();                                         \
}
#define Array_IMPL(T, SIZE) _Array_IMPL(T, SIZE)

#endif // NFLIB_ARRAY_H
