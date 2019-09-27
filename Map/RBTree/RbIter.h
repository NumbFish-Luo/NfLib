#ifndef NFLIB_RBTREE_ITER_H
#define NFLIB_RBTREE_ITER_H

#include "RbIterBase.h"
#include <NfLib/Base/Type.h>

// iter ////////////////////////////////////////////////////////////////////////
#define _RbIter(VALUE, ...) RbIter$_##VALUE##_$##__VA_ARGS__
#define RbIter(VALUE, ...) _RbIter(VALUE, __VA_ARGS__)

// DEF /////////////////////////////////////////////////////////////////////////
#define _RbIter_DEF(VALUE)                                                      \
/* typedef */                                                                   \
typedef struct RbIter(VALUE)       RbIter(VALUE);                               \
typedef struct RbIter(VALUE, _ops) RbIter(VALUE, _ops);                         \
/* def */                                                                       \
struct RbIter(VALUE) {                                                          \
    RbIterBase base;                                                            \
    RbIter(VALUE, _ops)* ops;                                                   \
};                                                                              \
struct RbIter(VALUE, _ops) {                                                    \
    VALUE* (*GetValue ) (RbIter(VALUE)* this);                                  \
    Bool   (*Increment) (RbIter(VALUE)* this);                                  \
    Bool   (*Decrement) (RbIter(VALUE)* this);                                  \
};                                                                              \
/* init */                                                                      \
void RbIter(VALUE, _Init) (RbIter(VALUE)* this);
#define RbIter_DEF(VALUE) _RbIter_DEF(VALUE)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _RbIter_IMPL(VALUE)                                                     \
static VALUE* RbIter(VALUE, _GetValue) (RbIter(VALUE)* this) {                  \
    RbNode(VALUE)* node = (RbNode(VALUE)*)this->base.node;                      \
    return &node->value;                                                        \
}                                                                               \
static Bool RbIter(VALUE, _Increment) (RbIter(VALUE)* this) {                   \
    return this->base.ops->Increment(&this->base);                              \
}                                                                               \
static Bool RbIter(VALUE, _Decrement) (RbIter(VALUE)* this) {                   \
    return this->base.ops->Decrement(&this->base);                              \
}                                                                               \
static RbIter(VALUE, _ops)* RbIter(VALUE, _Ops) (void) {                        \
    static RbIter(VALUE, _ops) ops;                                             \
    static Bool init = False;                                                   \
    if (init == False) {                                                        \
        init = True;                                                            \
        ops.GetValue  = RbIter(VALUE, _GetValue );                              \
        ops.Increment = RbIter(VALUE, _Increment);                              \
        ops.Decrement = RbIter(VALUE, _Decrement);                              \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
/* init */                                                                      \
void RbIter(VALUE, _Init) (RbIter(VALUE)* this) {                               \
    RbIterBase_Init(&this->base);                                               \
    this->ops = RbIter(VALUE, _Ops)();                                          \
}
#define RbIter_IMPL(VALUE) _RbIter_IMPL(VALUE)

#endif // NFLIB_RBTREE_ITER_H
