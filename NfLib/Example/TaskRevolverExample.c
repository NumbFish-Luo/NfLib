#include "Examples.h"
#include <NfLib/TaskRevolver.h>
#include <stdio.h>

void F1(TaskArgs args) { printf("F1 �ӵ�: %d\n", args.i); }
void F2(TaskArgs args) { printf("F2 �ӵ�: %d\n", args.i); }
void F3(TaskArgs args) { printf("F3 �ӵ�: %d\n", args.i); }

void TaskRevolverExample() {
    TaskRevolver t;
    TaskArgs a;

    TaskRevolver_Init(&t, 1000);

    // ��װ�����ӵ���ָ������F + ����������a��
    a.i = 1; t.Ops()->Loading(&t, F1, a);
    a.i = 2; t.Ops()->Loading(&t, F2, a);
    a.i = 3; t.Ops()->Loading(&t, F3, a);

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
