#include "Examples.h"
#include <NfLib/TaskGun.h>

static void F1(int a, int b) { printf("F1 { a: %d, b: %d }", a, b); }
static void F2(int a, int b) { printf("F2 { a: %d, b: %d }", a, b); }
static void F3(int a, int b) { printf("F3 { a: %d, b: %d }", a, b); }

typedef void (*Fn) (int a, int b); // ��һ��, ���Ҫ���õĺ����ĸ�ʽ
typedef struct { Fn F; int a; int b; } Args; // �ڶ���, ����ʽ�Ͳ��������һ��
static void Call_Fn(Args args) { if (args.F != 0) { args.F(args.a, args.b); } } // ������, �����������

TaskGun_DEF(Args, 6);
TaskGun_IMPL(Args, 6);

void TaskGunExample() {
    Args args;
    TaskGun(Args, 6) gun;
    TaskGun(Args, 6, _Init) (&gun, 1000);

    args.F = F1; args.a = 111; args.b = 222;
    gun.Ops()->Load(&gun, Call_Fn, args);

    args.F = F2; args.a = 333; args.b = 444;
    gun.Ops()->Load(&gun, Call_Fn, args);

    args.F = F3; args.a = 555; args.b = 666;
    gun.Ops()->Load(&gun, Call_Fn, args);

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
