#include "FsmLine.h"

void FsmLine_Init(
    FsmLine* line,
    FsmNode* prevNode,
    FsmNode* nextNode,
    FsmLineName name,
    FsmCall Func
) {
    line->prevNode = prevNode;
    line->nextNode = nextNode;
    line->name = name;
    line->Func = Func;
}
