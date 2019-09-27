#include "MapExample.h"
#include <stdio.h>
#include <NfLib/Base/Type.h>
#include <NfLib/Map/RBTree/RBTree.h>

RbNode_DEF(u8);
RbNode_IMPL(u8);

RbIter_DEF(u8);
RbIter_IMPL(u8);

RbTree_DEF(u8, u8);

void Map_Example(void) {
    RbBasePtr b = 0;
    RbNode(u8) n;
    RbIter(u8) i;
    RbTree(u8, u8) t;

    RbNode(u8, _Init) (&n);
    RbIter(u8, _Init) (&i);

    b = (RbBasePtr)&n;
    b->ops->Max(b);
    b->ops->Min(b);

    i.base.node = b;
    i.ops->GetValue(&i);
    i.ops->Increment(&i);
    i.ops->Decrement(&i);
}
