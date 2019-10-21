#include "Examples.h"
#include <NfLib/TaskRevolver.h>
#include <NfLib/R2L.h>
#include <stdio.h>

/*******************************************************************************
    ����bug, ����ʹ��!!
    There are bugs, please do not use!!
*******************************************************************************/

void F1(void* args) { printf("F1 �ӵ�: %d\n", *(int*)args); }
void F2(void* args) { printf("F2 �ӵ�: %d\n", *(int*)args); }
void F3(void* args) { printf("F3 �ӵ�: %d\n", *(int*)args); }

R2L_DEF(int);
R2L_IMPL(int);

void TaskRevolverExample() {
    TaskRevolver t;

    TaskRevolver_Init(&t, 1000);

    // ��װ�����ӵ���ָ������F + ����������a��
    t.Ops()->Loading(&t, F1, (void*)R2L(int)(1).data);
    t.Ops()->Loading(&t, F2, (void*)R2L(int)(2).data);
    t.Ops()->Loading(&t, F3, (void*)R2L(int)(3).data);

    while (1) {
        switch (t.Ops()->Shoot(&t)) {
        case TaskRevolver_NoBullet: printf("û�ӵ���!  \n"); break; // �б�����������
        case TaskRevolver_HoldOn  : printf("�Ȼ��...  \n"); break; // δ������ʱ��
        case TaskRevolver_Shoot   : printf("���䡪��!\n\n"); break; // ִ��������
        case TaskRevolver_Dud     : printf("�Ƶ�?!     \n"); break; // ������ΪNULL
        }
        Sleep(500); // һ����Բ��ü�Sleep�ģ�����ֻ��Ϊ����ʾЧ����������ˢ���ٶ�...
    }
}
