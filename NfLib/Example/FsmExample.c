#include "Examples.h"
#include <NfLib/Fsm.h>
#include <stdio.h>
#include <Windows.h>

#define FSM_NODE_INIT(NODE) FsmNode_Init(&NODE, #NODE, Call_##NODE)
#define FSM_LINE_INIT(LINE, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE, &PREV_NODE, &NEXT_NODE, #LINE, Call_##LINE)

#define CallNode_IMPL(NODE) void Call_##NODE(FsmNode* this, void* args)
#define CallLine_IMPL(LINE) void Call_##LINE(FsmLine* this, void* args)

CallNode_IMPL(n1) { printf("n1 { name = \"%s\", args = %d }\n", this->name, *(int*)args); }
CallNode_IMPL(n2) { printf("n2 { name = \"%s\", args = %d }\n", this->name, *(int*)args); }
CallNode_IMPL(n3) { printf("n3 { name = \"%s\", args = %d }\n", this->name, *(int*)args); }

CallLine_IMPL(la) { printf("la { name = \"%s\", args = %d }\n", this->name, *(int*)args); }
CallLine_IMPL(lb) { printf("lb { name = \"%s\", args = %d }\n", this->name, *(int*)args); }
CallLine_IMPL(lc) { printf("lc { name = \"%s\", args = %d }\n", this->name, *(int*)args); }

static void SetSomeEvent(FsmEvent* event) {
    static bool init = false;
    static const char* name[3] = { "la", "lb", "lc" };
    static int arg[2] = { 1, 2 };
    static FsmEvent eventList[6];
    static u8 i = 0;
    if (init == false) {
        init = true;

        eventList[0].name = name[0]; eventList[0].args = &arg[0];
        eventList[1].name = name[1]; eventList[1].args = &arg[0];
        eventList[2].name = name[2]; eventList[2].args = &arg[0];

        eventList[3].name = name[0]; eventList[3].args = &arg[1];
        eventList[4].name = name[1]; eventList[4].args = &arg[1];
        eventList[5].name = name[2]; eventList[5].args = &arg[1];
    }
    *event = eventList[i++];
    i %= 6;
}

static void Init(Fsm* f, void* args) {
    static FsmNode n1, n2, n3;
    static FsmLine la, lb, lc;

    Fsm_Init(f, args);

    f->ops->AddNode(f, FSM_NODE_INIT(n1));
    f->ops->AddNode(f, FSM_NODE_INIT(n2));
    f->ops->AddNode(f, FSM_NODE_INIT(n3));

    f->ops->AddLine(f, FSM_LINE_INIT(la, n1, n2));
    f->ops->AddLine(f, FSM_LINE_INIT(lb, n2, n3));
    f->ops->AddLine(f, FSM_LINE_INIT(lc, n3, n1));

    f->ops->Start(f, "n1");
}

void FsmExample() {
    static FsmEvent e;
    static Fsm f1, f2;
    static int arg1 = 1;
    static int arg2 = 2;
    static u64 preTime = 0;
    static u64 nowTime = 0;

    Init(&f1, &arg1);
    Init(&f2, &arg2);

    printf("start!\n");
    while (1) {
        if (GetTickCount64() - preTime > 1000) {
            nowTime = preTime = GetTickCount64();
            SetSomeEvent(&e);
            if (*(int*)e.args == 1) {
                printf("\n[f1]\n");
                f1.ops->HandleEvent(&f1, e);
            } else {
                printf("\n[f2]\n");
                f2.ops->HandleEvent(&f2, e);
            }
        }
    }
}
