#include "Examples.h"
#include <NfLib/TaskRevolver.h>
#include <stdio.h>

void F1(TaskArgs args) { printf("F1 子弹: %d\n", args.i); }
void F2(TaskArgs args) { printf("F2 子弹: %d\n", args.i); }
void F3(TaskArgs args) { printf("F3 子弹: %d\n", args.i); }

void TaskRevolverExample() {
    TaskRevolver t;
    TaskArgs a;

    TaskRevolver_Init(&t, 1000);

    // 填装三发子弹（指任务函数F + 任务函数参数a）
    a.i = 1; t.Ops()->Loading(&t, F1, a);
    a.i = 2; t.Ops()->Loading(&t, F2, a);
    a.i = 3; t.Ops()->Loading(&t, F3, a);

    while (1) {
        switch (t.Ops()->Shoot(&t)) {
        case TaskRevolver_NoBullet: printf("没子弹了!  \n"); break; // 列表中无任务函数
        case TaskRevolver_HoldOn  : printf("等会儿...  \n"); break; // 未到周期时间
        case TaskRevolver_Shoot   : printf("发射——!\n\n"); break; // 执行任务函数
        case TaskRevolver_Dud     : printf("哑弹?!     \n"); break; // 任务函数为NULL
        }
        Sleep(500); // 一般可以不用加Sleep的，这里只是为了演示效果，减慢了刷新速度...
    }
}
