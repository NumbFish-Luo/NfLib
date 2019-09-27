#ifndef FSM_CFG_H
#define FSM_CFG_H

#include "../Base/Type.h"

// ���� ////////////////////////////////////////////////////////////////////////
typedef struct FsmNode     FsmNode;                   // �ڵ�
typedef enum   FsmNodeName FsmNodeName;               // �ڵ�����

typedef struct FsmLine     FsmLine;                   // ��
typedef enum   FsmLineName FsmLineName, FsmEventName; // ������, ͬʱҲ���¼�����

typedef struct Fsm         Fsm;                       // ����״̬��
typedef struct Fsm_ops     Fsm_ops;                   // ����״̬����Ա�����б�

typedef void (*FsmCall)(void);                        // ״ִ̬�к���

// ��Ҫ��������, �������Ҫ���ú��ʵĴ�С, ��ֹ�˷��ڴ� ////////////////////////
enum {
    FsmNode_MaxLineNum = 8, // һ���ڵ�ɴ洢���ߵ��������
    Fsm_MaxNodeNum     = 64 // ״̬���ڿɴ洢�Ľڵ���������
};

// ����ʱ�������ַ����洢�ڵ������Լ�������, ����������mapȥ��¼ ///////////////
// �ڵ�����
enum FsmNodeName {
    FsmNode_None = 0, // ��
    FsmNode_A    = 1, // A
    FsmNode_B    = 2, // B
    FsmNode_C    = 3  // C
};

// ������
enum FsmLineName {
    FsmLine_None = 0, // ��
    FsmLine_1    = 1, // 1
    FsmLine_2    = 2, // 2
    FsmLine_3    = 3  // 3
};

#endif // FSM_CFG_H
