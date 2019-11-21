#ifndef _NFLIB_QUEUE_H
#define _NFLIB_QUEUE_H

#include <NfLib/Base.h>

// T: Type
// S: Size

#define _Queue(T, S, ...) Queue$_##T##_$$_##S##_$##__VA_ARGS__
#define Queue(T, S, ...) _Queue(T, S, __VA_ARGS__)

#define _Queue_DEF(T, S)                                                        \
/* typedef */                                                                   \
typedef struct Queue(T, S) Queue(T, S);                                         \
typedef struct Queue(T, S, _ops) Queue(T, S, _ops);                             \
/* queue */                                                                     \
struct Queue(T, S) {                                                            \
    T _data[S];                                                                 \
    u16 _head;                                                                  \
    u16 _tail;                                                                  \
    Queue(T, S, _ops)* (*Ops) (void);                                           \
};                                                                              \
/* ops */                                                                       \
struct Queue(T, S, _ops) {                                                      \
    u16 (*MaxSize) (void);                                                      \
    u16 (*Size   ) (Queue(T, S)* this);                                         \
    \
};

#define Queue_DEF(T, S) _Queue_DEF(T, S)

#define _Queue_IMPL(T, S)                                                       \

#define Queue_IMPL(T, S) _Queue_IMPL(T, S)

#endif // _NFLIB_QUEUE_H
