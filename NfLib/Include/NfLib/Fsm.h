#ifndef _NFLIB_FSM_H
#define _NFLIB_FSM_H

#include <NfLib/Base.h>
#include <NfLib/FsmCfg.h>
#include <NfLib/FsmNode.h>
#include <NfLib/FsmLine.h>

struct Fsm {
    FsmNode*   currNode;
    FsmNode*   nodes[Fsm_MaxNodeNum];
    u8         size;
    void*      args;
    Fsm_ops* (*Ops) (void);
};

struct Fsm_ops {
    bool (*At         ) (Fsm* this, const char name[FsmName_MaxLen]);
    bool (*AddNode    ) (Fsm* this, FsmNode* node);
    bool (*AddLine    ) (Fsm* this, FsmLine* line);
    bool (*Start      ) (Fsm* this, const char name[FsmName_MaxLen]);
    bool (*HandleEvent) (Fsm* this, FsmEvent event);
    bool (*Run        ) (Fsm* this);
};

void Fsm_Init(Fsm* this, void* args);

#endif // _NFLIB_FSM_H
