#include "Examples.h"
#include <NfLib/TaskRevolver.h>
#include <NfLib/R2L.h>
#include <stdio.h>

void F1(TaskArgs args) { printf("SHOOT THE FIRE!: %d\n", args.i); }
void F2(TaskArgs args) { printf("--> SHOOT THE FIRE!: %d\n", args.i); }
void F3(TaskArgs args) { printf("----> SHOOT THE FIRE!: %d\n", args.i); }

One_DEF(int);
R2L_IMPL(int);

void TaskRevolverExample() {
    TaskRevolver t;
    TaskArgs args;

    TaskRevolver_Init(&t, 1000);

    args.i = 1; t.Ops()->Loading(&t, F1, args);
    args.i = 2; t.Ops()->Loading(&t, F2, args);
    args.i = 3; t.Ops()->Loading(&t, F3, args);

    while (1) {
        switch (t.Ops()->Shoot(&t)) {
        case TaskRevolver_NoBullet: printf("û���ӵ���!?\n"); break;
        case TaskRevolver_HoldOn  : printf("�Ȼ��...   \n"); break;
        case TaskRevolver_Shoot   : printf("����!!      \n"); break;
        case TaskRevolver_Dud     : printf("�Ƶ�?!      \n"); break;
        }
        Sleep(500);
    }
}
