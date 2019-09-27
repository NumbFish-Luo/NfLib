#ifndef FSM_LINE_H
#define FSM_LINE_H

#include "FsmCfg.h"

struct FsmLine {
    FsmNode*    prevNode; // 上一个节点
    FsmNode*    nextNode; // 下一个节点
    FsmLineName name;     // 线名称
    FsmCall     Func;     // 转移节点时执行的函数
};

void FsmLine_Init(
    FsmLine*    this,     // 线
    FsmNode*    prevNode, // 上一个节点
    FsmNode*    nextNode, // 下一个节点
    FsmLineName name,     // 线名称
    FsmCall     Func      // 转移节点时执行的函数
);

#endif // FSM_LINE_H
