#ifndef NFLIB_RBTREE_NODE_BASE_H
#define NFLIB_RBTREE_NODE_BASE_H

typedef enum { Rb_Red = 0, Rb_Black = 1 } RbColor;
typedef struct RbNodeBase RbNodeBase;
typedef struct RbNodeBase_ops RbNodeBase_ops;
typedef RbNodeBase* RbBasePtr;

struct RbNodeBase {
    RbColor color;
    RbBasePtr parent;
    RbBasePtr left;
    RbBasePtr right;
    RbNodeBase_ops* ops;
};

struct RbNodeBase_ops {
    RbBasePtr (*Min) (RbBasePtr x);
    RbBasePtr (*Max) (RbBasePtr x);
};

void RbNodeBase_Init(RbNodeBase* this);
RbNodeBase_ops* RbNodeBaseOps(void);

#endif // NFLIB_RBTREE_NODE_BASE_H
