#ifndef _NFLIB_RING_H
#define _NFLIB_RING_H

#include <NfLib/Base.h>

// T: Type
// S: Size

#define _Ring(T, S, ...) Ring$_##T##_$$_##S##_$##__VA_ARGS__
#define Ring(T, S, ...) _Ring(T, S, __VA_ARGS__)

#define _Ring_DEF(T, S)                                                         \
/* typedef */                                                                   \
typedef struct Ring(T, S)       Ring(T, S);                                     \
typedef struct Ring(T, S, _ops) Ring(T, S, _ops);                               \
/* Ring */                                                                      \
struct Ring(T, S) {                                                             \
    size_t _head, _tail;                                                        \
    T _data[S];                                                                 \
    Ring(T, S, _ops)* (*Ops) (void);                                            \
};                                                                              \
/* Ops */                                                                       \
struct Ring(T, S, _ops) {                                                       \
    size_t (*MaxSize  ) (void);                                                 \
    size_t (*Size     ) (Ring(T, S)* this);                                     \
    bool   (*PushBack ) (Ring(T, S)* this, T data);                             \
    bool   (*PushFront) (Ring(T, S)* this, T data);                             \
    bool   (*PopBack  ) (Ring(T, S)* this, T* data);                            \
    bool   (*PopFront ) (Ring(T, S)* this, T* data);                            \
    bool   (*Get      ) (Ring(T, S)* this, size_t i, T* data);                  \
    bool   (*Set      ) (Ring(T, S)* this, size_t i, T data);                   \
};                                                                              \
/* Init */                                                                      \
void Ring(T, S, _Init) (Ring(T, S)* this);
#define Ring_DEF(T, S) _Ring_DEF(T, S)

#define _Ring_IMPL(T, S)                                                        \
static inline size_t Ring(T, S, _MaxSize) (void) { return S; }                  \
static inline size_t Ring(T, S, _Size) (Ring(T, S)* this) {                     \
    if (this->_head <= this->_tail) { return this->_tail - this->_head; }       \
    return S - this->_head + this->_tail;                                       \
}                                                                               \
static inline bool Ring(T, S, _PushBack) (Ring(T, S)* this, T data) {           \
    if ((this->_tail + 1) % S == this->_head) { return false; }                 \
    this->_data[this->_tail++] = data;                                          \
    this->_tail %= S;                                                           \
    return true;                                                                \
}                                                                               \
static inline bool Ring(T, S, _PushFront) (Ring(T, S)* this, T data) {          \
    if ((this->_head + S - 1) % S == this->_tail) { return false; }             \
    this->_head = (this->_head + S - 1) % S;                                    \
    this->_data[this->_head] = data;                                            \
    return true;                                                                \
}                                                                               \
static inline bool Ring(T, S, _PopBack) (Ring(T, S)* this, T* data) {           \
    if (this->_tail == this->_head) { return false; }                           \
    this->_tail = (this->_tail + S - 1) % S;                                    \
    if (data) { *data = this->_data[this->_tail]; }                             \
    return true;                                                                \
}                                                                               \
static inline bool Ring(T, S, _PopFront) (Ring(T, S)* this, T* data) {          \
    if (this->_head == this->_tail) { return false; }                           \
    if (data) { *data = this->_data[this->_head]; }                             \
    this->_head = (this->_head + 1) % S;                                        \
    return true;                                                                \
}                                                                               \
static inline bool Ring(T, S, _Get) (Ring(T, S)* this, size_t i, T* data) {     \
    if (i >= S || i >= this->Ops()->Size(this) || data == 0) { return false; }  \
    *data = this->_data[(this->_head + i) % S];                                 \
    return true;                                                                \
}                                                                               \
static inline bool Ring(T, S, _Set) (Ring(T, S)* this, size_t i, T data) {      \
    if (i >= S || i >= this->Ops()->Size(this)) { return false; }               \
    this->_data[(this->_head + i) % S] = data;                                  \
    return true;                                                                \
}                                                                               \
static inline Ring(T, S, _ops)* Ring(T, S, _Ops) (void) {                       \
    static Ring(T, S, _ops) ops;                                                \
    static bool init = false;                                                   \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.MaxSize   = Ring(T, S, _MaxSize  );                                 \
        ops.Size      = Ring(T, S, _Size     );                                 \
        ops.PushBack  = Ring(T, S, _PushBack );                                 \
        ops.PushFront = Ring(T, S, _PushFront);                                 \
        ops.PopBack   = Ring(T, S, _PopBack  );                                 \
        ops.PopFront  = Ring(T, S, _PopFront );                                 \
        ops.Get       = Ring(T, S, _Get      );                                 \
        ops.Set       = Ring(T, S, _Set      );                                 \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
void Ring(T, S, _Init) (Ring(T, S)* this) {                                     \
    this->_head = this->_tail = 0;                                              \
    this->Ops = Ring(T, S, _Ops);                                               \
}
#define Ring_IMPL(T, S) _Ring_IMPL(T, S)

#endif // _NFLIB_RING_H
