#ifndef _NFLIB_FSM_NODE_H
#define _NFLIB_FSM_NODE_H

#include <NfLib/Base.h>
#include <NfLib/FsmCfg.h>

struct FsmNode_Period { u32 preTime, nowTime, runTimes; };
FsmNode_Period* FsmNode_Period_Init(FsmNode_Period* this);

struct FsmNode {
    char           name[FsmName_MaxLen];
    FsmLine*       lines[FsmNode_MaxLineNum];
    u8             lineSize;
    FsmNodeCall    Func;
    FsmNode_Period period[FsmNode_Period_MaxNum];
};

FsmNode* FsmNode_Init(
    FsmNode*    this,
    const char  name[FsmName_MaxLen],
    FsmNodeCall Func
);

#endif // _NFLIB_FSM_NODE_H
