#ifndef _NFLIB_ARRAY_H
#define _NFLIB_ARRAY_H

#include <stdlib.h>
#include <NfLib/Base.h>

// T: Type
// S: Size

#if _LAYER(0, "array") /////////////////////////////////////////////////////////
#define _Array(T, S, ...) Array$_##T##_$$_##S##_$##__VA_ARGS__
#define Array(T, S, ...) _Array(T, S, __VA_ARGS__)
#endif // _LAYER(0, "array")

#if _LAYER(0, "def") ///////////////////////////////////////////////////////////
#define _Array_DEF(T, S)                                                        \
/* typedef */                                                                   \
typedef struct Array(T, S)       Array(T, S);                                   \
typedef struct Array(T, S, _ops) Array(T, S, _ops);                             \
typedef T*                       Array(T, S, _Iter);                            \
/* Array */                                                                     \
struct Array(T, S) {                                                            \
    T _data[S];                                                                 \
    u16 _size;                                                                  \
    Array(T, S, _ops)* (*Ops) (void);                                           \
};                                                                              \
/* ops */                                                                       \
struct Array(T, S, _ops) {                                                      \
    u16                (*MaxSize   ) (void);                                    \
    u16                (*Size      ) (Array(T, S)* this);                       \
    bool               (*PushBacks ) (Array(T, S)* this, const T* data, u16 count); \
    bool               (*PushFronts) (Array(T, S)* this, const T* data, u16 count); \
    bool               (*PushBack  ) (Array(T, S)* this, T data);               \
    bool               (*PushFront ) (Array(T, S)* this, T data);               \
    bool               (*PopBacks  ) (Array(T, S)* this, T* data, u16 count);   \
    bool               (*PopFronts ) (Array(T, S)* this, T* data, u16 count);   \
    bool               (*PopBack   ) (Array(T, S)* this, T* data);              \
    bool               (*PopFront  ) (Array(T, S)* this, T* data);              \
    void               (*SetData   ) (Array(T, S)* this, const T data[S]);      \
    bool               (*Set       ) (Array(T, S)* this, u16 i, T data);        \
    bool               (*Get       ) (Array(T, S)* this, u16 i, T** data);      \
    Array(T, S, _Iter) (*Begin     ) (Array(T, S)* this);                       \
    Array(T, S, _Iter) (*End       ) (Array(T, S)* this);                       \
};                                                                              \
/* Init */                                                                      \
Array(T, S)* Array(T, S, _Init) (Array(T, S)* this)
#define Array_DEF(T, S) _Array_DEF(T, S)
#endif // _LAYER(0, "def")

#if _LAYER(0, "impl") //////////////////////////////////////////////////////////
#define _Array_IMPL(T, S)                                                       \
/* static function */                                                           \
static inline u16 Array(T, S, _MaxSize) (void) { return S; }                    \
static inline u16 Array(T, S, _Size) (Array(T, S)* this) { return this->_size; } \
static inline bool Array(T, S, _PushBacks) (Array(T, S)* this, const T* data, u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size + count > S) { return false; }                              \
    for (i = 0; i < count; ++i) { this->_data[this->_size++] = data[i]; }       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, S, _PushFronts) (Array(T, S)* this, const T* data, u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size + count > S) { return false; }                              \
    for (i = 0; i < this->_size; ++i) {                                         \
        this->_data[this->_size - i + count - 1] = this->_data[this->_size - i - 1]; \
    }                                                                           \
    for (i = 0; i < count; ++i) { this->_data[i] = data[i]; }                   \
    this->_size += count;                                                       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, S, _PushBack) (Array(T, S)* this, T data) {         \
    return Array(T, S, _PushBacks) (this, &data, 1);                            \
}                                                                               \
static inline bool Array(T, S, _PushFront) (Array(T, S)* this, T data) {        \
    return Array(T, S, _PushFronts) (this, &data, 1);                           \
}                                                                               \
static inline bool Array(T, S, _PopBacks) (Array(T, S)* this, T* data, u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size < count) { return false; }                                  \
    for (i = 0; i < count; ++i) { data[i] = this->_data[--this->_size]; }       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, S, _PopFronts) (Array(T, S)* this, T* data, u16 count) { \
    u16 i = 0;                                                                  \
    if (this->_size < count) { return false; }                                  \
    for (i = 0; i < count; ++i) { data[i] = this->_data[i]; }                   \
    for (i = 0; i < this->_size; ++i) {                                         \
        this->_data[i] = this->_data[i + count];                                \
    }                                                                           \
    this->_size -= count;                                                       \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, S, _PopBack) (Array(T, S)* this, T* data) {         \
    return Array(T, S, _PopBacks) (this, data, 1);                              \
}                                                                               \
static inline bool Array(T, S, _PopFront) (Array(T, S)* this, T* data) {        \
    return Array(T, S, _PopFronts) (this, data, 1);                             \
}                                                                               \
static inline void Array(T, S, _SetData) (Array(T, S)* this, const T data[S]) { \
    u16 i = 0;                                                                  \
    for (i = 0; i < S; ++i) { this->_data[i] = data[i]; }                       \
    this->_size = S;                                                            \
}                                                                               \
static inline bool Array(T, S, _Set) (Array(T, S)* this, u16 i, T data) {       \
    if (i >= this->_size) { return false; }                                     \
    this->_data[i] = data;                                                      \
    return true;                                                                \
}                                                                               \
static inline bool Array(T, S, _Get) (Array(T, S)* this, u16 i, T** data) {     \
    if (i >= this->_size) { return false; }                                     \
    *data = &this->_data[i];                                                    \
    return true;                                                                \
}                                                                               \
static inline Array(T, S, _Iter) Array(T, S, _Begin) (Array(T, S)* this) {      \
    return &this->_data[0];                                                     \
}                                                                               \
static inline Array(T, S, _Iter) Array(T, S, _End) (Array(T, S)* this) {        \
    return &this->_data[this->_size];                                           \
}                                                                               \
static inline Array(T, S, _ops)* Array(T, S, Ops) (void) {                      \
    static Array(T, S, _ops) ops;                                               \
    static bool init = false;                                                   \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.MaxSize    = Array(T, S, _MaxSize   );                              \
        ops.Size       = Array(T, S, _Size      );                              \
        ops.PushBacks  = Array(T, S, _PushBacks );                              \
        ops.PushFronts = Array(T, S, _PushFronts);                              \
        ops.PushBack   = Array(T, S, _PushBack  );                              \
        ops.PushFront  = Array(T, S, _PushFront );                              \
        ops.PopBacks   = Array(T, S, _PopBacks  );                              \
        ops.PopFronts  = Array(T, S, _PopFronts );                              \
        ops.PopBack    = Array(T, S, _PopBack   );                              \
        ops.PopFront   = Array(T, S, _PopFront  );                              \
        ops.SetData    = Array(T, S, _SetData   );                              \
        ops.Set        = Array(T, S, _Set       );                              \
        ops.Get        = Array(T, S, _Get       );                              \
        ops.Begin      = Array(T, S, _Begin     );                              \
        ops.End        = Array(T, S, _End       );                              \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* Init */                                                                      \
inline Array(T, S)* Array(T, S, _Init) (Array(T, S)* this) {                    \
    this->_size = 0;                                                            \
    this->Ops = Array(T, S, Ops);                                               \
    return this;                                                                \
}
#define Array_IMPL(T, S) _Array_IMPL(T, S)
#endif // _LAYER(0, "impl")

#endif // _NFLIB_ARRAY_H
