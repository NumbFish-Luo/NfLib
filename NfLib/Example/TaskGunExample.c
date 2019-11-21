#include "Examples.h"
#include <NfLib/TaskGun.h>

static void F1(int a, int b) { printf("F1 { a: %d, b: %d }", a, b); }
static void F2(int a, int b) { printf("F2 { a: %d, b: %d }", a, b); }
static void F3(int a, int b) { printf("F3 { a: %d, b: %d }", a, b); }

typedef void (*Fn) (int a, int b); // 第一步, 抽出要调用的函数的格式
typedef struct { Fn F; int a; int b; } Args; // 第二步, 将格式和参数打包到一起
static void Call_Fn(Args args) { if (args.F != 0) { args.F(args.a, args.b); } } // 第三步, 定义参数函数

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
        case TaskGun_NoBullet: printf("没子弹了!  \n"); break; // 列表中无任务函数
        case TaskGun_HoldOn  : printf("等会儿...  \n"); break; // 未到周期时间
        case TaskGun_Shoot   : printf("发射——!\n\n"); break; // 执行任务函数
        case TaskGun_Dud     : printf("哑弹?!     \n"); break; // 任务函数为NULL
        }
        Sleep(200); // 一般可以不用加Sleep的，这里只是为了演示效果，减慢了刷新速度...
    }
}
