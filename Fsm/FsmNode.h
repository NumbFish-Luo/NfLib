#ifndef FSM_NODE_H
#define FSM_NODE_H

#include "FsmCfg.h"

struct FsmNode {
    FsmNodeName   name;                         // �ڵ�����
    FsmLine*      lines[FsmNode_MaxLineNum]; // ��ýڵ����ӵ�״̬��
    SmallSizeType lineSize;                     // ������
    FsmCall       Func;                         // ���ڸýڵ�ʱ�������еĺ���
};

void FsmNode_Init(
    FsmNode*    node, // �ڵ�
    FsmNodeName name, // �ڵ�����
    FsmCall     Func  // ���ڸýڵ�ʱ�������еĺ���
);

#endif // FSM_NODE_H
