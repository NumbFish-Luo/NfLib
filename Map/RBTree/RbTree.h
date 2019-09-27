// Î´Íê³É //////////////////////////////////////////////////////////////////////
#ifndef NFLIB_RBTREE_H
#define NFLIB_RBTREE_H

#include <NfLib/Base/Type.h>
#include "RbNode.h"
#include "RbIter.h"

// RbTree //////////////////////////////////////////////////////////////////////
#define _RbTree(KEY, VALUE, ...) RbTree$_##KEY##_$$_##VALUE##_$##__VA_ARGS__
#define RbTree(KEY, VALUE, ...) _RbTree(KEY, VALUE, __VA_ARGS__)

// DEF /////////////////////////////////////////////////////////////////////////
#define _RbTree_DEF(KEY, VALUE)                                                 \
/* typedef */                                                                   \
typedef struct RbTree(KEY, VALUE)       RbTree(KEY, VALUE);                     \
typedef struct RbTree(KEY, VALUE, _ops) RbTree(KEY, VALUE, _ops);               \
/* Rb */                                                                        \
struct RbTree(KEY, VALUE) {                                                     \
    SizeType size;                                                              \
    RbNode(VALUE)* header;                                                      \
    Bool (*Compare) (VALUE* lhs, VALUE* rhs);                                   \
    RbTree(KEY, VALUE, _ops)* ops;                                              \
};                                                                              \
/* ops */                                                                       \
struct RbTree(KEY, VALUE, _ops) {                                               \
    RbIter(VALUE) (*Begin) (RbTree(KEY, VALUE)* this);                          \
    RbIter(VALUE) (*End  ) (RbTree(KEY, VALUE)* this);                          \
    RbIter(VALUE) (*Add  ) (const VALUE* v);                                    \
    RbIter(VALUE) (*Find ) (const KEY* k);                                      \
};                                                                              \
/* init */                                                                      \
void RbTree(KEY, VALUE, _Init) (RbTree(KEY, VALUE)* this, Bool (*Compare) (VALUE* lhs, VALUE* rhs));
#define RbTree_DEF(KEY, VALUE) _RbTree_DEF(KEY, VALUE)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _RbTree_IMPL(KEY, VALUE)                                                \

#define RbTree_IMPL(KEY, VALUE) _Rb_IMPL(KEY, VALUE)

#endif // NFLIB_RBTREE_H
