#ifndef FSM_NODE_H
#define FSM_NODE_H

#include "FsmCfg.h"

struct FsmNode {
    FsmNodeName   name;                         // 节点名称
    FsmLine*      lines[FsmNode_MaxLineNum]; // 与该节点链接的状态线
    SmallSizeType lineSize;                     // 线数量
    FsmCall       Func;                         // 处于该节点时持续运行的函数
};

void FsmNode_Init(
    FsmNode*    node, // 节点
    FsmNodeName name, // 节点名称
    FsmCall     Func  // 处于该节点时持续运行的函数
);

#endif // FSM_NODE_H
