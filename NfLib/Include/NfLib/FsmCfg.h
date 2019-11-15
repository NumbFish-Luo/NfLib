#ifndef _NFLIB_FSM_CFG_H
#define _NFLIB_FSM_CFG_H

#include <NfLib/Base.h>
// user defined :-D
#define FsmArgType           u8
#define FsmName_MaxLen       32
#define FsmNode_MaxLineNum   4
#define Fsm_MaxNodeNum       32
#define Fsm_MaxEventNum      4
#define FsmNode_Timer_MaxNum 4
#define FsmNone              "none"
#define FSM_NO_CALL_LINE     0

#define FSM_NODE_INIT(NODE) FsmNode_Init(&NODE, #NODE, Call_##NODE)
#define FSM_NODE_INIT_i(NODE, i) FsmNode_Init(&NODE[i], #NODE, Call_##NODE)
#define CallNode_IMPL(NODE) void Call_##NODE(FsmNode* this, FsmArgType arg)

#if FSM_NO_CALL_LINE
#define FSM_LINE_INIT(LINE, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE, &PREV_NODE, &NEXT_NODE, #LINE, 0)
#define FSM_LINE_INIT_i(LINE, i, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE[i], &PREV_NODE, &NEXT_NODE, #LINE, 0)
#else
#define FSM_LINE_INIT(LINE, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE, &PREV_NODE, &NEXT_NODE, #LINE, Call_##LINE)
#define FSM_LINE_INIT_i(LINE, i, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE[i], &PREV_NODE, &NEXT_NODE, #LINE, Call_##LINE)
#define CallLine_IMPL(LINE) void Call_##LINE(FsmLine* this, FsmArgType arg)
#endif

typedef struct Fsm           Fsm;
typedef struct Fsm_ops       Fsm_ops;
typedef struct FsmNode       FsmNode;
typedef struct FsmNode_Timer FsmNode_Timer;
typedef struct FsmLine       FsmLine;
typedef struct FsmEvent      FsmEvent;
typedef void (*FsmNodeCall) (FsmNode* this, FsmArgType arg);
typedef void (*FsmLineCall) (FsmLine* this, FsmArgType arg);

#endif // _NFLIB_FSM_CFG_H
