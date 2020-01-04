#ifndef _NFLIB_POOL_H
#define _NFLIB_POOL_H

#include <NfLib/Base.h>

#define __Pool(T, S, ...) _Pool$_##T##_$$_##S##_$##__VA_ARGS__
#define Pool(T, S, ...) __Pool(T, S, __VA_ARGS__)

#define _Pool_DEF(T, S)                                                         \
typedef struct Pool(T, S) Pool(T, S);                                           \
typedef struct Pool(T, S, _ops) Pool(T, S, _ops);                               \
struct Pool(T, S) {                                                             \
    T _pool[S];                                                                 \
    size_t _size[S];                                                            \
    Pool(T, S, _ops)* (*Ops) (void);                                            \
};                                                                              \
struct Pool(T, S, _ops) {                                                       \
    size_t (*MaxSize) (void);                                                   \
    T*     (*New    ) (Pool(T, S)* this, size_t size);                          \
    bool   (*Delete ) (Pool(T, S)* this, T** p);                                \
};                                                                              \
inline Pool(T, S)* Pool(T, S, _Init) (Pool(T, S)* this);
#define Pool_DEF(T, S) _Pool_DEF(T, S)

#define _Pool_IMPL(T, S)                                                        \
static inline size_t Pool(T, S, _MaxSize) (void) { return S; }                  \
static inline T* Pool(T, S, _New) (Pool(T, S)* this, size_t size) {             \
    size_t i, j;                                                                \
    bool ok = true;                                                             \
    if (size == 0 || size > S) { return 0; }                                    \
    for (i = 0; i <= S - size; ++i) {                                           \
        if (this->_size[i] == 0) {                                              \
            for (j = i; j < i + size; ++j) {                                    \
                if (this->_size[j] != 0) {                                      \
                    i = j + this->_size[j] - 1;                                 \
                    ok = false;                                                 \
                    break;                                                      \
                }                                                               \
            }                                                                   \
            if (ok) {                                                           \
                this->_size[i] = size;                                          \
                return this->_pool + i;                                         \
            } else { ok = true; }                                               \
        } else { i += this->_size[i] - 1; }                                     \
    }                                                                           \
    return 0;                                                                   \
}                                                                               \
static inline bool Pool(T, S, _Delete) (Pool(T, S)* this, T** p) {              \
    size_t i;                                                                   \
    if (*p >= this->_pool && *p - this->_pool <= S) {                           \
        i = *p - this->_pool;                                                   \
        this->_size[i] = 0;                                                     \
        *p = 0;                                                                 \
        return true;                                                            \
    }                                                                           \
    return false;                                                               \
}                                                                               \
static inline Pool(T, S, _ops)* Pool(T, S, _Ops) (void) {                       \
    static Pool(T, S, _ops) ops;                                                \
    static bool init = false;                                                   \
    if (init == false) {                                                        \
        ops.MaxSize = Pool(T, S, _MaxSize);                                     \
        ops.New     = Pool(T, S, _New    );                                     \
        ops.Delete  = Pool(T, S, _Delete );                                     \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
inline Pool(T, S)* Pool(T, S, _Init) (Pool(T, S)* this) {                       \
    size_t i;                                                                   \
    for (i = 0; i < S; ++i) { this->_size[i] = 0; }                             \
    this->Ops = Pool(T, S, _Ops);                                               \
    return this;                                                                \
}
#define Pool_IMPL(T, S) _Pool_IMPL(T, S)

#endif // _NFLIB_POOL_H
