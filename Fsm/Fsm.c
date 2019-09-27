#include "FSM.h"

#define size this->size
#define nodes this->nodes
#define currNode this->currNode

// ��ӽڵ�
static Bool AddNode(Fsm* this, FsmNode* node) {
    if (node == 0 || size >= Fsm_MaxNodeNum) {
        return False; // ָ��Ϊ��, ��ڵ������������������
    }
    nodes[size++] = node;
    return True;
}

// �����
static Bool AddLine(Fsm* this, FsmLine* line) {
    u8 i = 0;
    if (line == 0 || line->prevNode == 0) {
        return False; // ָ��Ϊ��
    }
    for (; i < size; ++i) {
        if (nodes[i] != 0) {
            if (line->prevNode->name == nodes[i]->name) {
                if (nodes[i]->lineSize >= FsmNode_MaxLineNum) {
                    return False; // �����������
                }
                nodes[i]->lines[nodes[i]->lineSize++] = line;
                return True;
            }
        }
    }
    return False;
}

// ���ÿ�ʼ�ڵ�
static Bool Start(Fsm* this, FsmNodeName name) {
    u8 i = 0;
    for (; i < size; ++i) {
        if (nodes[i] != 0) {
            if (name == nodes[i]->name) {
                currNode = nodes[i];
                return True;
            }
        }
    }
    currNode = 0;
    return False;
}

// ����ʱ����
static inline void SafeDelay(u32 delay) { if (delay > 0) { while(--delay); } }

// �����¼�
static Bool HandleEvent(Fsm* this, FsmLineName name) {
    u8 i = 0;
    // SafeDelay(100); // ����lpc1788оƬ, ������ʱ, ����������, �Զ�����
    if (currNode == 0 || currNode->Func == 0) {
        return False;
    }
    currNode->Func();
    if (name == FsmLine_None) {
        return False;
    }
    for (; i < currNode->lineSize; ++i) {
        if (currNode != 0
            && currNode->lines[i] != 0
            && currNode->lines[i]->name == name
        ) {
            if (currNode->lines[i]->Func != 0) {
                currNode->lines[i]->Func();
            }
            currNode = currNode->lines[i]->nextNode;
            currNode->Func();
            return True;
        }
    }
    return False;
}

static Fsm_ops* FsmOps(void) {
    static Fsm_ops ops;
    static Bool init = False;
    if (init == False) {
        init = True;
        ops.AddNode = AddNode;
        ops.AddLine = AddLine;
        ops.Start = Start;
        ops.HandleEvent = HandleEvent;
    }
    return &ops;
}

// ��ʼ��״̬��
void Fsm_Init(Fsm* this) {
    u8 i = 0;
    currNode = 0;
    for (; i < Fsm_MaxNodeNum; ++i) {
        nodes[i] = 0;
    }
    size = 0;
    this->ops = FsmOps();
}

#undef size
#undef nodes
#undef currNode
