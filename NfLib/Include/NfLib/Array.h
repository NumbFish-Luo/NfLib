#ifndef _NFLIB_ARRAY_H
#define _NFLIB_ARRAY_H

#include <stdlib.h>
#include <NfLib/Base.h>

#if _LAYER(0, "array") /////////////////////////////////////////////////////////
#define _Array(T, SIZE, ...) Array$_##T##_$$_##SIZE##_$##__VA_ARGS__
#define Array(T, SIZE, ...) _Array(T, SIZE, __VA_ARGS__)
#endif // _LAYER(0, "array")

#if _LAYER(0, "def") ///////////////////////////////////////////////////////////
#define _Array_DEF(T, SIZE)                                                     \
/* typedef */                                                                   \
typedef struct Array(T, SIZE)       Array(T, SIZE);                             \
typedef struct Array(T, SIZE, _ops) Array(T, SIZE, _ops);                       \
typedef T*                          Array(T, SIZE, _Iter);                      \
/* Array */                                                                     \
struct Array(T, SIZE) {                                                         \
    T _data[SIZE];                                                              \
    u16 _size;                                                                  \
    Array(T, SIZE, _ops)* ops;                                                  \
};                                                                              \
/* ops */                                                                       \
struct Array(T, SIZE, _ops) {                                                   \
    u16                   (*MaxSize   ) (void);                                 \
    bool                  (*PushBacks ) (Array(T, SIZE)* this, const T data[], u16 count); \
    bool                  (*PushFronts) (Array(T, SIZE)* this, const T data[], u16 count); \
    bool                  (*PushBack  ) (Array(T, SIZE)* this, T data);         \
    bool                  (*PushFront ) (Array(T, SIZE)* this, T data);         \
    bool                  (*PopBacks  ) (Array(T, SIZE)* this, T data[], u16 count); \
    bool                  (*PopFronts ) (Array(T, SIZE)* this, T data[], u16 count); \
    bool                  (*PopBack   ) (Array(T, SIZE)* this, T* data);        \
    bool                  (*PopFront  ) (Array(T, SIZE)* this, T* data);        \
    void                  (*SetData   ) (Array(T, SIZE)* this, const T data[SIZE]); \
    Array(T, SIZE, _Iter) (*Begin     ) (Array(T, SIZE)* this);                 \
    Array(T, SIZE, _Iter) (*End       ) (Array(T, SIZE)* this);                 \
};                                                                              \
/* Init */                                                                      \
Array(T, SIZE)* Array(T, SIZE, _Init) (Array(T, SIZE)* this)
#define Array_DEF(T, SIZE) _Array_DEF(T, SIZE)
#endif // _LAYER(0, "def")

#if _LAYER(0, "impl") //////////////////////////////////////////////////////////
#define _Array_IMPL(T, SIZE)                                                    \
/* static function */                                                           \
static inline u16 Array(T, SIZE, _MaxSize) (void) {                             \
    return SIZE;                                                                \
}                                                                               \
static inline bool Array(T, SIZE, _PushBacks) (Array(T, SIZE)* this, const T data[], u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size + count > SIZE) { return false; }                           \
    for (i = 0; i < count; ++i) { this->_data[this->_size++] = data[i]; }       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, SIZE, _PushFronts) (Array(T, SIZE)* this, const T data[], u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size + count > SIZE) { return false; }                           \
    for (i = 0; i < this->_size; ++i) {                                         \
        this->_data[this->_size - i + count - 1] = this->_data[this->_size - i - 1]; \
    }                                                                           \
    for (i = 0; i < count; ++i) {                                               \
        this->_data[i] = data[i];                                               \
    }                                                                           \
    this->_size += count;                                                       \
    return true;                                                                \
}                                                                               \
static bool Array(T, SIZE, _PushBack) (Array(T, SIZE)* this, T data) {          \
    return Array(T, SIZE, _PushBacks) (this, &data, 1);                         \
}                                                                               \
static bool Array(T, SIZE, _PushFront) (Array(T, SIZE)* this, T data) {         \
    return Array(T, SIZE, _PushFronts) (this, &data, 1);                        \
}                                                                               \
static inline bool Array(T, SIZE, _PopBacks) (Array(T, SIZE)* this, T data[], u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size < count) { return false; }                                  \
    for (i = 0; i < count; ++i) { data[i] = this->_data[--this->_size]; }       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, SIZE, _PopFronts) (Array(T, SIZE)* this, T data[], u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size < count) { return false; }                                  \
    for (i = 0; i < count; ++i) {                                               \
        data[i] = this->_data[i];                                               \
    }                                                                           \
    for (i = 0; i < this->_size; ++i) {                                         \
        this->_data[i] = this->_data[i + count];                                \
    }                                                                           \
    this->_size -= count;                                                       \
    return true;                                                                \
}                                                                               \
static bool Array(T, SIZE, _PopBack) (Array(T, SIZE)* this, T* data) {          \
    return Array(T, SIZE, _PopBacks) (this, data, 1);                           \
}                                                                               \
static bool Array(T, SIZE, _PopFront) (Array(T, SIZE)* this, T* data) {         \
    return Array(T, SIZE, _PopFronts) (this, data, 1);                          \
}                                                                               \
static inline void Array(T, SIZE, _SetData) (Array(T, SIZE)* this, const T data[SIZE]) { \
    u16 i = 0;                                                                  \
    for (i = 0; i < SIZE; ++i) { this->_data[i] = data[i]; }                    \
    this->_size = SIZE;                                                         \
}                                                                               \
static inline Array(T, SIZE, _Iter) Array(T, SIZE, _Begin) (Array(T, SIZE)* this) { \
    return &this->_data[0];                                                     \
}                                                                               \
static inline Array(T, SIZE, _Iter) Array(T, SIZE, _End) (Array(T, SIZE)* this) { \
    return &this->_data[this->_size];                                           \
}                                                                               \
static Array(T, SIZE, _ops)* Array(T, SIZE, Ops) (void) {                       \
    static Array(T, SIZE, _ops) ops;                                            \
    static bool init = false;                                                   \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.MaxSize    = Array(T, SIZE, _MaxSize   );                           \
        ops.PushBacks  = Array(T, SIZE, _PushBacks );                           \
        ops.PushFronts = Array(T, SIZE, _PushFronts);                           \
        ops.PushBack   = Array(T, SIZE, _PushBack  );                           \
        ops.PushFront  = Array(T, SIZE, _PushFront );                           \
        ops.PopBacks   = Array(T, SIZE, _PopBacks  );                           \
        ops.PopFronts  = Array(T, SIZE, _PopFronts );                           \
        ops.PopBack    = Array(T, SIZE, _PopBack   );                           \
        ops.PopFront   = Array(T, SIZE, _PopFront  );                           \
        ops.SetData    = Array(T, SIZE, _SetData   );                           \
        ops.Begin      = Array(T, SIZE, _Begin     );                           \
        ops.End        = Array(T, SIZE, _End       );                           \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* Init */                                                                      \
Array(T, SIZE)* Array(T, SIZE, _Init) (Array(T, SIZE)* this) {                  \
    this->_size = 0;                                                            \
    this->ops = Array(T, SIZE, Ops) ();                                         \
    return this;                                                                \
}
#define Array_IMPL(T, SIZE) _Array_IMPL(T, SIZE)
#endif // _LAYER(0, "impl")

#endif // _NFLIB_ARRAY_H
