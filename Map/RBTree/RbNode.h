#ifndef NFLIB_RBTREE_NODE_H
#define NFLIB_RBTREE_NODE_H

#include "RbNodeBase.h"

#define _RbNode(VALUE, ...) RbNode$_##VALUE##_$##__VA_ARGS__
#define RbNode(VALUE, ...) _RbNode(VALUE, __VA_ARGS__)

#define _RbNode_DEF(VALUE) typedef struct {                                     \
    RbNodeBase base;                                                            \
    VALUE value;                                                                \
} RbNode(VALUE);                                                                \
void RbNode(VALUE, _Init) (RbNode(VALUE)* this);
#define RbNode_DEF(VALUE) _RbNode_DEF(VALUE)

#define _RbNode_IMPL(VALUE)                                                     \
void RbNode(VALUE, _Init) (RbNode(VALUE)* this) {                               \
    RbNodeBase_Init(&this->base);                                               \
}
#define RbNode_IMPL(VALUE) _RbNode_IMPL(VALUE)

#endif // NFLIB_RBTREE_NODE_H
