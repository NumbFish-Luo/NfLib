#include <NfLib/FsmLine.h>
#include <string.h>

#pragma warning(disable : 4996)

FsmLine* FsmLine_Init(
    FsmLine*    this,
    FsmNode*    prevNode,
    FsmNode*    nextNode,
    const char  name[FsmName_MaxLen],
    FsmLineCall Func
) {
    this->prevNode = prevNode;
    this->nextNode = nextNode;
    strcpy(this->name, name);
    this->Func = Func;
    return this;
}
