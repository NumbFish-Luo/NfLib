#include "Examples.h"
#include <stdio.h>

struct Base { // ����Base
    void (*Print) (struct Base* this); // ��ӡ����
    int v; // ���õĳ�Ա
};

struct Derived_A { // ������A
    struct Base base; // �̳���Base
    char va; // A���еĳ�Ա
};

struct Derived_B { // ������B
    struct Base base; // �̳���Base
    float vb; // B���еĳ�Ա
};

void PrintA(struct Base* a) { // ��ӡA��ֵ
    struct Derived_A* pa = (struct Derived_A*)a; // Baseǿ��ת��ΪA, �Ի�ȡA���еĳ�Ա
    printf("A: %d, %c\n", pa->base.v, pa->va);
}

void FB(struct Derived_B* b) {
    printf("FB: %f\n", (double)b->vb + (double)b->base.v);
}

void PrintB(struct Base* b) { // ��ӡB��ֵ
    struct Derived_B* pb = (struct Derived_B*)b; // Baseǿ��ת��ΪB, �Ի�ȡB���еĳ�Ա
    printf("B: %d, %f\n", pb->base.v, pb->vb);
    FB(pb);
}

void InitA(struct Derived_A* a) { // ��ʼ��A
    a->base.Print = PrintA; // ��ӡA�ĺ���
    a->base.v = 0; // ���õĳ�Ա
    a->va = 'a';
}

void InitB(struct Derived_B* b) { // ��ʼ��B
    b->base.Print = PrintB; // ��ӡB�ĺ���
    b->base.v = 1;
    b->vb = 3.14f;
}

void PolymorphismExample(void) { // ��̬ʹ��ʾ��
    struct Base* p; // Baseָ��
    struct Derived_A a;
    struct Derived_B b;

    InitA(&a); // ��ʼ��a����
    InitB(&b); // ��ʼ��b����

    p = &a.base; // ��ָ��a
    p->Print(p); // �ù��ýӿڵ��ú���, ��� A: 0, a

    p = &b.base; // ��ָ��b
    p->Print(p); // �ù��ýӿڵ��ú���, ��� B: 1, 3.140000
                 //                          FB: 4.140000
}
