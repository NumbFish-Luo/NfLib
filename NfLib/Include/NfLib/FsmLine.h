#ifndef _NFLIB_FSM_LINE_H
#define _NFLIB_FSM_LINE_H

#include <NfLib/FsmCfg.h>

struct FsmLine {
    FsmNode*    prevNode;
    FsmNode*    nextNode;
    const char  name[FsmName_MaxLen];
    FsmLineCall Func;
};

FsmLine* FsmLine_Init(FsmLine* this, FsmNode* prevNode, FsmNode* nextNode, const char name[FsmName_MaxLen], FsmLineCall Func);;

#endif // _NFLIB_FSM_LINE_H
