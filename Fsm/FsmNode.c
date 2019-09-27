#include "FsmNode.h"

void FsmNode_Init(FsmNode* this, FsmNodeName name, FsmCall Func) {
    u8 i = 0;
    this->name = name;
    for (; i < FsmNode_MaxLineNum; ++i) { this->lines[i] = 0; }
    this->lineSize = 0;
    this->Func = Func;
}
