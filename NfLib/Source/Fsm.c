#include <NfLib/Fsm.h>
#include <string.h>

static inline bool At(Fsm* this, const char name[FsmName_MaxLen]) {
    return strcmp(this->currNode->name, name) == 0;
}

static bool AddNode(Fsm* this, FsmNode* node) {
    if (node == 0 || this->size >= Fsm_MaxNodeNum) { return false; }
    this->nodes[this->size++] = node;
    return true;
}

static bool AddLine(Fsm* this, FsmLine* line) {
    u8 i = 0;
    if (line == 0 || line->prevNode == 0) { return false; }
    for (i = 0; i < this->size; ++i) {
        if (this->nodes[i] != 0 && strcmp(line->prevNode->name, this->nodes[i]->name) == 0) {
            if (this->nodes[i]->lineSize >= FsmNode_MaxLineNum) { return false; }
            this->nodes[i]->lines[this->nodes[i]->lineSize++] = line;
            return true;
        }
    }
    return false;
}

static bool Start(Fsm* this, const char name[FsmName_MaxLen]) {
    u8 i = 0;
    for (i = 0; i < this->size; ++i) {
        if (this->nodes[i] != 0 && strcmp(name, this->nodes[i]->name) == 0) {
            this->currNode = this->nodes[i];
            return true;
        }
    }
    this->currNode = 0;
    return false;
}

static bool Run(Fsm* this) {
    if (this->currNode == 0 || this->currNode->Func == 0) { return false; }
    this->currNode->Func(this->currNode, this->args);
    return true;
}

static bool HandleEvent(Fsm* this, FsmEvent event) {
    u8 i = 0;
    u8 j = 0;
    const char* name = event.name;
    if (strcmp(name, "") == 0) { return false; }
    for (i = 0; i < this->currNode->lineSize; ++i) {
        if (this->currNode->lines[i] != 0 && strcmp(this->currNode->lines[i]->name, name) == 0) {
            if (this->currNode->lines[i]->Func != 0) {
                this->currNode->lines[i]->Func(this->currNode->lines[i], this->args);
            }
            this->currNode = this->currNode->lines[i]->nextNode;
            for (j = 0; j < FsmNode_Timer_MaxNum; ++j) {
                FsmNode_Timer_Init(&this->currNode->timer[j]);
            }
            return true;
        }
    }
    return false;
}

static Fsm_ops* Ops(void) {
    static Fsm_ops ops;
    static bool init = false;
    if (init == false) {
        init = true;
        ops.At          = At;
        ops.AddNode     = AddNode;
        ops.AddLine     = AddLine;
        ops.Start       = Start;
        ops.HandleEvent = HandleEvent;
        ops.Run         = Run;
    }
    return &ops;
}

void Fsm_Init(Fsm* this, const char* args) {
    u8 i = 0;
    this->currNode = 0;
    for (i = 0; i < Fsm_MaxNodeNum; ++i) { this->nodes[i] = 0; }
    this->size = 0;
    this->Ops = Ops;
    this->args = args;
}
