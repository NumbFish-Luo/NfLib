#ifndef NFLIB_FSM_H
#define NFLIB_FSM_H

#include "FsmCfg.h"
#include "FsmNode.h"
#include "FsmLine.h"

struct Fsm {
    FsmNode* currNode;                // ��ǰ�ڵ�
    FsmNode* nodes[Fsm_MaxNodeNum]; // ״̬���ڵĽڵ�
    u8 size;                          // �ڵ�����
    Fsm_ops* ops;                     // ��Ա�����б�
};

struct Fsm_ops {
    Bool (*AddNode)(Fsm* this, FsmNode* node);        // ��ӽڵ�
    Bool (*AddLine)(Fsm* this, FsmLine* line);        // �����
    Bool (*Start)(Fsm* this, FsmNodeName name);       // ���ÿ�ʼ�ڵ�
    Bool (*HandleEvent)(Fsm* this, FsmLineName name); // �����¼�
};

void Fsm_Init(Fsm* this);

#endif // NFLIB_FSM_H
