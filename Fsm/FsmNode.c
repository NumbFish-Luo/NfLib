#include "FsmNode.h"

void FsmNode_Init(FsmNode* node, FsmNodeName name, FsmCall Func) {
    u8 i = 0;
    node->name = name;
    for (; i < FsmNode_MaxLineNum; ++i) { node->lines[i] = 0; }
    node->lineSize = 0;
    node->Func = Func;
}
