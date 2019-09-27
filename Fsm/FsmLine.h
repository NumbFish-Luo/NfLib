#ifndef FSM_LINE_H
#define FSM_LINE_H

#include "FsmCfg.h"

struct FsmLine {
    FsmNode*    prevNode; // ��һ���ڵ�
    FsmNode*    nextNode; // ��һ���ڵ�
    FsmLineName name;     // ������
    FsmCall     Func;     // ת�ƽڵ�ʱִ�еĺ���
};

void FsmLine_Init(
    FsmLine*    this,     // ��
    FsmNode*    prevNode, // ��һ���ڵ�
    FsmNode*    nextNode, // ��һ���ڵ�
    FsmLineName name,     // ������
    FsmCall     Func      // ת�ƽڵ�ʱִ�еĺ���
);

#endif // FSM_LINE_H
