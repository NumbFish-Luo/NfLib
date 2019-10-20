#ifndef _NFLIB_FSM_CFG_H
#define _NFLIB_FSM_CFG_H

#include <Windows.h>
#define GET_TICK_COUNT() (u32)GetTickCount64()

typedef struct Fsm            Fsm;
typedef struct Fsm_ops        Fsm_ops;
typedef struct FsmNode        FsmNode;
typedef struct FsmNode_Timer FsmNode_Timer;
typedef struct FsmLine        FsmLine;
typedef struct FsmEvent       FsmEvent;
typedef void (*FsmNodeCall)  (FsmNode* this, void* args);
typedef void (*FsmLineCall)  (FsmLine* this, void* args);

#define FsmName_MaxLen        32
#define FsmNode_MaxLineNum    4
#define Fsm_MaxNodeNum        32
#define Fsm_MaxEventNum       4
#define FsmNode_Timer_MaxNum 4
#define FsmNone               "none"

#endif // _NFLIB_FSM_CFG_H
