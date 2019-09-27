#include "RbNodeBase.h"
#include <NfLib/Base/Type.h>

static inline RbBasePtr Min(RbBasePtr x) {
    while (x->left != 0) { x = x->left; }
    return x;
}

static inline RbBasePtr Max(RbBasePtr x) {
    while (x->right != 0) { x = x->right; }
    return x;
}

void RbNodeBase_Init(RbNodeBase* this) {
    this->color = Rb_Red;
    this->parent = this->left = this->right = 0;
    this->ops = RbNodeBaseOps();
}

RbNodeBase_ops* RbNodeBaseOps(void) {
    static RbNodeBase_ops ops;
    static Bool init = False;
    if (init == False) {
        init = True;
        ops.Min = Min;
        ops.Max = Max;
    }
    return &ops;
}
