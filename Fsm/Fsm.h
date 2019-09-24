#ifndef NFLIB_FSM_H
#define NFLIB_FSM_H

#include "FsmCfg.h"
#include "FsmNode.h"
#include "FsmLine.h"

struct Fsm {
    FsmNode* currNode;                // 当前节点
    FsmNode* nodes[Fsm_MaxNodeNum]; // 状态机内的节点
    u8 size;                          // 节点数量
    Fsm_ops* ops;                     // 成员函数列表
};

struct Fsm_ops {
    Bool (*AddNode)(Fsm* fsm, FsmNode* node);        // 添加节点
    Bool (*AddLine)(Fsm* fsm, FsmLine* line);        // 添加线
    Bool (*Start)(Fsm* fsm, FsmNodeName name);       // 设置开始节点
    Bool (*HandleEvent)(Fsm* fsm, FsmLineName name); // 处理事件
};

void Fsm_Init(Fsm* fsm);

#endif // NFLIB_FSM_H
