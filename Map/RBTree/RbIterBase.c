#include "RbIterBase.h"
#include <NfLib/Base/Type.h>

static Bool Increment(RbIterBase* this) {
#define node this->node
    RbBasePtr y = 0;
    if (node->right != 0) {
        node = node->right;
        while (node->left != 0) { node = node->left; }
    } else {
        y = node->parent;
        if (y == 0) { return False; }
        while (node == y->right) {
            node = y;
            y = y->parent;
        }
        if (node->right != y) { node = y; }
    }
    return True;
#undef node
}

static Bool Decrement(RbIterBase* this) {
#define node this->node
    RbBasePtr y;
    if (node->color == Rb_Red && node->parent != 0 && node->parent->parent == node) {
        node = node->right;
    } else if (node->left != 0) {
        y = node->left;
        while(y->right != 0) { y = y->right; }
        node = y;
    } else {
        y = node->parent;
        if (y == 0) { return False; }
        while (node == y->left) {
            node = y;
            y = y->parent;
        }
        node = y;
    }
    return True;
#undef node
}

void RbIterBase_Init(RbIterBase* this) {
    this->node = 0;
    this->ops = RbIterBaseOps();
}

RbIterBase_ops* RbIterBaseOps(void) {
    static RbIterBase_ops ops;
    static Bool init = False;
    if (init == False) {
        init = True;
        ops.Increment = Increment;
        ops.Decrement = Decrement;
    }
    return &ops;
}
