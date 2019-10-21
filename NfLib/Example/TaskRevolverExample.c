#include "Examples.h"
#include <NfLib/TaskRevolver.h>
#include <NfLib/R2L.h>
#include <stdio.h>

/*******************************************************************************
    存在bug, 请勿使用!!
    There are bugs, please do not use!!
*******************************************************************************/

void F1(void* args) { printf("F1 子弹: %d\n", *(int*)args); }
void F2(void* args) { printf("F2 子弹: %d\n", *(int*)args); }
void F3(void* args) { printf("F3 子弹: %d\n", *(int*)args); }

R2L_DEF(int);
R2L_IMPL(int);

void TaskRevolverExample() {
    TaskRevolver t;

    TaskRevolver_Init(&t, 1000);

    // 填装三发子弹（指任务函数F + 任务函数参数a）
    t.Ops()->Loading(&t, F1, (void*)R2L(int)(1).data);
    t.Ops()->Loading(&t, F2, (void*)R2L(int)(2).data);
    t.Ops()->Loading(&t, F3, (void*)R2L(int)(3).data);

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
