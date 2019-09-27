#include "FsmLine.h"

void FsmLine_Init(
    FsmLine* this,
    FsmNode* prevNode,
    FsmNode* nextNode,
    FsmLineName name,
    FsmCall Func
) {
    this->prevNode = prevNode;
    this->nextNode = nextNode;
    this->name = name;
    this->Func = Func;
}
