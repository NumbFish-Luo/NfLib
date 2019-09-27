#ifndef NFLIB_RBTREE_ITER_BASE_H
#define NFLIB_RBTREE_ITER_BASE_H

#include "RbNodeBase.h"
#include <NfLib/Base/Type.h>

typedef struct RbIterBase     RbIterBase;
typedef struct RbIterBase_ops RbIterBase_ops;

struct RbIterBase {
    RbBasePtr node;
    RbIterBase_ops* ops;
};

struct RbIterBase_ops {
    Bool (*Increment) (RbIterBase* this);
    Bool (*Decrement) (RbIterBase* this);
};

void RbIterBase_Init(RbIterBase* this);
RbIterBase_ops* RbIterBaseOps(void);

#endif // NFLIB_RBTREE_ITER_BASE_H
