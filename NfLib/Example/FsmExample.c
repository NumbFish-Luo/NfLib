#include "Examples.h"
#include <NfLib/Fsm.h>
#include <stdio.h>
#include <Windows.h>

#define FSM_NODE_INIT(NODE) FsmNode_Init(&NODE, #NODE, Call_##NODE)
#define FSM_LINE_INIT(LINE, PREV_NODE, NEXT_NODE) FsmLine_Init(&LINE, &PREV_NODE, &NEXT_NODE, #LINE, Call_##LINE)

#define CallNode_IMPL(NODE) void Call_##NODE(FsmNode* this, void* args)
#define CallLine_IMPL(LINE) void Call_##LINE(FsmLine* this, void* args)

////////////////////////////////////////////////////////////////////////////////

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

    f->Ops()->AddNode(f, FSM_NODE_INIT(n1));
    f->Ops()->AddNode(f, FSM_NODE_INIT(n2));
    f->Ops()->AddNode(f, FSM_NODE_INIT(n3));

    f->Ops()->AddLine(f, FSM_LINE_INIT(la, n1, n2));
    f->Ops()->AddLine(f, FSM_LINE_INIT(lb, n2, n3));
    f->Ops()->AddLine(f, FSM_LINE_INIT(lc, n3, n1));

    f->Ops()->Start(f, "n1");
}

void FsmExample_1() {
    static FsmEvent e1;
    static Fsm f1, f2;
    static int a1 = 1;
    static int a2 = 2;
    static u64 preTime = 0;
    static u64 nowTime = 0;

    Init(&f1, &a1);
    Init(&f2, &a2);

    printf("start!\n");
    while (1) {
        if (GetTickCount64() - preTime > 1000) {
            nowTime = preTime = GetTickCount64();
            SetSomeEvent(&e1);
            if (*(int*)e1.args == 1) {
                printf("\n[f1]\n");
                f1.Ops()->Run(&f1);
                f1.Ops()->HandleEvent(&f1, e1);
            } else {
                printf("\n[f2]\n");
                f2.Ops()->Run(&f2);
                f2.Ops()->HandleEvent(&f2, e1);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

static FsmEvent e2;

CallNode_IMPL(n4) {
    switch (this->UpdateTimer(this, 0, 2000, 4)) {
    case FsmNode_UpdateTimer_Wait: printf("."); break;
    case FsmNode_UpdateTimer_TimesUp: printf("\n%s", this->name); break;
    case FsmNode_UpdateTimer_Timeout: printf("\nTimeout!\n"); e2.name = "ld"; break;
    }
}

CallNode_IMPL(n5) {
    switch (this->UpdateTimer(this, 0, 500, 6)) {
    case FsmNode_UpdateTimer_Wait: printf("."); break;
    case FsmNode_UpdateTimer_TimesUp: printf("\n%s", this->name); break;
    case FsmNode_UpdateTimer_Timeout: printf("\nTimeout!\n"); e2.name = "le"; break;
    }
}

CallNode_IMPL(n6) {
    switch (this->UpdateTimer(this, 0, 4000, 5)) {
    case FsmNode_UpdateTimer_Wait: printf("."); break;
    case FsmNode_UpdateTimer_TimesUp: printf("\n%s", this->name); break;
    case FsmNode_UpdateTimer_Timeout: printf("\nTimeout!\n"); e2.name = "lf"; break;
    }
}

CallLine_IMPL(ld) {}
CallLine_IMPL(le) {}
CallLine_IMPL(lf) {}

void FsmExample_2() {
    static Fsm f3;
    static FsmNode n4, n5, n6;
    static FsmLine ld, le, lf;
    e2.name = "NOTHING :-)"; e2.args = 0;

    Fsm_Init(&f3, 0);

    f3.Ops()->AddNode(&f3, FSM_NODE_INIT(n4));
    f3.Ops()->AddNode(&f3, FSM_NODE_INIT(n5));
    f3.Ops()->AddNode(&f3, FSM_NODE_INIT(n6));

    f3.Ops()->AddLine(&f3, FSM_LINE_INIT(ld, n4, n5));
    f3.Ops()->AddLine(&f3, FSM_LINE_INIT(le, n5, n6));
    f3.Ops()->AddLine(&f3, FSM_LINE_INIT(lf, n6, n4));

    f3.Ops()->Start(&f3, "n4");

    while (1) {
        f3.Ops()->Run(&f3);
        f3.Ops()->HandleEvent(&f3, e2);
        Sleep(100);
    }
}
