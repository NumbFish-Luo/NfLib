#include "Examples.h"
#include <NfLib/Fsm.h>
#include <stdio.h>
#include <Windows.h>

CallNode_IMPL(n1) { printf("n1 { name = \"%s\", arg = %d }\n", this->name, arg); }
CallNode_IMPL(n2) { printf("n2 { name = \"%s\", arg = %d }\n", this->name, arg); }
CallNode_IMPL(n3) { printf("n3 { name = \"%s\", arg = %d }\n", this->name, arg); }

CallLine_IMPL(la) { printf("la { name = \"%s\", arg = %d }\n", this->name, arg); }
CallLine_IMPL(lb) { printf("lb { name = \"%s\", arg = %d }\n", this->name, arg); }
CallLine_IMPL(lc) { printf("lc { name = \"%s\", arg = %d }\n", this->name, arg); }

static void SetSomeEvent(FsmEvent* event) {
    static FsmEvent eventList[6];
    static u8 i = 0;
    static bool init = false;
    if (init == false) {
        init = true;

        eventList[0].name = "la"; eventList[0].arg = 1;
        eventList[1].name = "lb"; eventList[1].arg = 1;
        eventList[2].name = "lc"; eventList[2].arg = 1;

        eventList[3].name = "la"; eventList[3].arg = 2;
        eventList[4].name = "lb"; eventList[4].arg = 2;
        eventList[5].name = "lc"; eventList[5].arg = 2;
    }
    *event = eventList[i++];
    i %= 6;
}

static void Init(Fsm* f, FsmArgType arg) {
    static FsmNode n1, n2, n3;
    static FsmLine la, lb, lc;

    Fsm_Init(f, arg);

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
    static u64 preTime = 0;
    static u64 nowTime = 0;

    Init(&f1, 1);
    Init(&f2, 2);

    printf("start!\n");
    while (1) {
        if (GetTickCount64() - preTime > 1000) {
            nowTime = preTime = GetTickCount64();
            SetSomeEvent(&e1);
            if (e1.arg == 1) {
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
    e2.name = "NOTHING :-)"; e2.arg = 0;

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
