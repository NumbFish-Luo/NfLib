#include "FSM.h"

// ��ӽڵ�
static Bool AddNode(Fsm* fsm, FsmNode* node) {
    if (fsm == 0 || node == 0 || fsm->size >= Fsm_MaxNodeNum) {
        return False; // ָ��Ϊ��, ��ڵ������������������
    }
    fsm->nodes[fsm->size++] = node;
    return True;
}

// �����
static Bool AddLine(Fsm* fsm, FsmLine* line) {
    u8 i = 0;
    if (fsm == 0 || line == 0 || line->prevNode == 0) {
        return False; // ָ��Ϊ��
    }
    for (; i < fsm->size; ++i) {
        if (fsm->nodes[i] != 0) {
            if (line->prevNode->name == fsm->nodes[i]->name) {
                if (fsm->nodes[i]->lineSize >= FsmNode_MaxLineNum) {
                    return False; // �����������
                }
                fsm->nodes[i]->lines[fsm->nodes[i]->lineSize++] = line;
                return True;
            }
        }
    }
    return False;
}

// ���ÿ�ʼ�ڵ�
static Bool Start(Fsm* fsm, FsmNodeName name) {
    u8 i = 0;
    if (fsm == 0) {
        return False;
    }
    for (; i < fsm->size; ++i) {
        if (fsm->nodes[i] != 0) {
            if (name == fsm->nodes[i]->name) {
                fsm->currNode = fsm->nodes[i];
                return True;
            }
        }
    }
    fsm->currNode = 0;
    return False;
}

// ����ʱ����
static inline void SafeDelay(u32 delay) { if (delay > 0) { while(--delay); } }

// �����¼�
static Bool HandleEvent(Fsm* fsm, FsmLineName name) {
    u8 i = 0;
    // SafeDelay(100); // ����lpc1788оƬ, ������ʱ, ����������, �Զ�����
    if (fsm == 0 || fsm->currNode == 0 || fsm->currNode->Func == 0) {
        return False;
    }
    fsm->currNode->Func();
    if (name == FsmLine_None) {
        return False;
    }
    for (; i < fsm->currNode->lineSize; ++i) {
        if (fsm->currNode != 0
            && fsm->currNode->lines[i] != 0
            && fsm->currNode->lines[i]->name == name
        ) {
            if (fsm->currNode->lines[i]->Func != 0) {
                fsm->currNode->lines[i]->Func();
            }
            fsm->currNode = fsm->currNode->lines[i]->nextNode;
            fsm->currNode->Func();
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
void Fsm_Init(Fsm* fsm) {
    u8 i = 0;
    fsm->currNode = 0;
    for (; i < Fsm_MaxNodeNum; ++i) {
        fsm->nodes[i] = 0;
    }
    fsm->size = 0;
    fsm->ops = FsmOps();
}
