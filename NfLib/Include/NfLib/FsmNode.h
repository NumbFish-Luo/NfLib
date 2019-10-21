#ifndef _NFLIB_FSM_NODE_H
#define _NFLIB_FSM_NODE_H

#include <NfLib/Base.h>
#include <NfLib/FsmCfg.h>

typedef enum {
    FsmNode_UpdateTimer_Wait,
    FsmNode_UpdateTimer_TimesUp,
    FsmNode_UpdateTimer_Timeout
} FsmNode_UpdateTimerState;

struct FsmEvent { const char* name; void* args; };

struct FsmNode_Timer { u32 preTime, nowTime, runTimes; };
FsmNode_Timer* FsmNode_Timer_Init(FsmNode_Timer* this);

struct FsmNode {
    char          name[FsmName_MaxLen];
    FsmLine*      lines[FsmNode_MaxLineNum];
    u8            lineSize;
    FsmNodeCall   Func;
    FsmNode_Timer timer[FsmNode_Timer_MaxNum];
    FsmNode_UpdateTimerState (*UpdateTimer) (
        FsmNode* this,
        u8       timerId,
        u32      period,
        u32      maxRunTimes
    );
};

FsmNode* FsmNode_Init(
    FsmNode*    this,
    const char  name[FsmName_MaxLen],
    FsmNodeCall Func
);

#endif // _NFLIB_FSM_NODE_H
