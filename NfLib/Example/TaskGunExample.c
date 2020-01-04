#include "Examples.h"
#include <NfLib/TaskGun.h>
#include <NfLib/Fsm.h>

////////////////////////////////////////////////////////////////////////////////
// ʾ��: TaskGun����ʹ�÷���                                                  //
////////////////////////////////////////////////////////////////////////////////

static void F1(int a, int b) { printf("F1 { a: %d, b: %d }", a, b); }
static void F2(int a, int b) { printf("F2 { a: %d, b: %d }", a, b); }
static void F3(int a, int b) { printf("F3 { a: %d, b: %d }", a, b); }

// 1. ������ָ��Ͳ��������һ���Ƴ��ӵ�
typedef struct {
    void (*F) (int a, int b);
               int a; int b;
} Bullet_i_i;

// 2. ������ú���
static void Call_i_i(Bullet_i_i b) { if (b.F != 0) { b.F(b.a, b.b); } }

TaskGun_DEF(Bullet_i_i, 6);
TaskGun_IMPL(Bullet_i_i, 6);

void TaskGunExample() {
    Bullet_i_i b;
    TaskGun(Bullet_i_i, 6) gun;
    TaskGun(Bullet_i_i, 6, _Init) (&gun, Call_i_i, 1000);

    b.F = F1; b.a = 111; b.b = 222;
    gun.Ops()->Load(&gun, b);

    b.F = F2; b.a = 333; b.b = 444;
    gun.Ops()->Load(&gun, b);

    b.F = F3; b.a = 555; b.b = 666;
    gun.Ops()->Load(&gun, b);

    while (1) {
        switch (gun.Ops()->Shoot(&gun)) {
        case TaskGun_NoBullet: printf("û�ӵ���!  \n"); break; // �б�����������
        case TaskGun_HoldOn  : printf("�Ȼ��...  \n"); break; // δ������ʱ��
        case TaskGun_Shoot   : printf("���䡪��!\n\n"); break; // ִ��������
        case TaskGun_Dud     : printf("�Ƶ�?!     \n"); break; // ������ΪNULL
        }
        Sleep(200); // һ����Բ��ü�Sleep�ģ�����ֻ��Ϊ����ʾЧ����������ˢ���ٶ�...
    }
}

////////////////////////////////////////////////////////////////////////////////
// ʾ��: ͨ��FSM��TaskGun������ӵ�                                           //
////////////////////////////////////////////////////////////////////////////////

// TaskGun���岿��
typedef struct {
    void (*F) (char port);
    char port;
} Bullet_fsm;
static void Call_fsm(Bullet_fsm b) { if (b.F != 0) { b.F(b.port); } }
TaskGun_DEF(Bullet_fsm, 6);
TaskGun_IMPL(Bullet_fsm, 6);

// TaskGun��̬����
static TaskGun(Bullet_fsm, 6) gun_fsm;

// �ص���������
// ������Ϣ
static void ErrorMsg(char port) { printf("ErrorMsg\n"); }

// �ڵ�n1��Ϣ
static void SendMsg_n1(char port) { printf("SendMsg_n1:%c\n", port); }
static CallNode_IMPL(n1) {
    Bullet_fsm b;
    printf("n1 { name = \"%s\", arg = \"%s\" }\n", this->name, args);
    b.F = SendMsg_n1; b.port = args[5];
    gun_fsm.Ops()->Load(&gun_fsm, b);
}

// �ڵ�n2��Ϣ
static void SendMsg_n2(char port) { printf("SendMsg_n2:%c\n", port); }
static CallNode_IMPL(n2) {
    Bullet_fsm b;
    printf("n2 { name = \"%s\", arg = \"%s\" }\n", this->name, args);
    b.F = SendMsg_n2; b.port = args[5];
    gun_fsm.Ops()->Load(&gun_fsm, b);
}

// �ڵ�n3��Ϣ
static void SendMsg_n3(char port) { printf("SendMsg_n3:%c\n", port); }
static CallNode_IMPL(n3) {
    Bullet_fsm b;
    printf("n3 { name = \"%s\", arg = \"%s\" }\n", this->name, args);
    b.F = SendMsg_n3; b.port = args[5];
    gun_fsm.Ops()->Load(&gun_fsm, b);
}

// ��la, lb, lc
static CallLine_IMPL(la) { printf("la { name = \"%s\", arg = \"%s\" }\n", this->name, args); }
static CallLine_IMPL(lb) { printf("lb { name = \"%s\", arg = \"%s\" }\n", this->name, args); }
static CallLine_IMPL(lc) { printf("lc { name = \"%s\", arg = \"%s\" }\n", this->name, args); }

// ��ʼ��״̬������
static void Init(Fsm* f, const char* args) {
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

// �����¼�
static void SetSomeEvent(FsmEvent* event) {
    static FsmEvent eventList[6];
    static u8 i = 0;
    static bool init = false;
    if (init == false) {
        init = true;

        eventList[0].name = "la"; eventList[0].args = "port:A";
        eventList[1].name = "lb"; eventList[1].args = "port:A";
        eventList[2].name = "lc"; eventList[2].args = "port:A";

        eventList[3].name = "la"; eventList[3].args = "port:B";
        eventList[4].name = "lb"; eventList[4].args = "port:B";
        eventList[5].name = "lc"; eventList[5].args = "port:B";
    }
    *event = eventList[i++];
    i %= 6;
}

// ʾ��
void TaskGun_Fsm_Example(void) {
    static FsmEvent e;
    static Fsm fsm_A, fsm_B;
    static u64 preTime = 0;
    static u64 nowTime = 0;

    Init(&fsm_A, "port:A");
    Init(&fsm_B, "port:B");
    TaskGun(Bullet_fsm, 6, _Init) (&gun_fsm, Call_fsm, 3000);

    printf("start!\n");
    while (1) {
        if (GET_TICK_COUNT() - preTime > 1000) {
            nowTime = preTime = GET_TICK_COUNT();
            SetSomeEvent(&e);
            if (strcmp(e.args, "port:A") == 0) {
                printf("\n[fsm_A]\n");
                fsm_A.Ops()->Run(&fsm_A);
                fsm_A.Ops()->HandleEvent(&fsm_A, e);
            } else if (strcmp(e.args, "port:B") == 0) {
                printf("\n[fsm_B]\n");
                fsm_B.Ops()->Run(&fsm_B);
                fsm_B.Ops()->HandleEvent(&fsm_B, e);
            } else {

            }
            switch (gun_fsm.Ops()->Shoot(&gun_fsm)) {
            case TaskGun_NoBullet: printf("û�ӵ���!  \n"); break; // �б�����������
            case TaskGun_HoldOn  : printf("�Ȼ��...  \n"); break; // δ������ʱ��
            case TaskGun_Shoot   : printf("���䡪��!\n\n"); break; // ִ��������
            case TaskGun_Dud     : printf("�Ƶ�?!     \n"); break; // ������ΪNULL
            }
        }
    }
}
