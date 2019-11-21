#include "Examples.h"
#include <stdio.h>

struct Base { // 基类Base
    void (*Print) (struct Base* this); // 打印函数
    int v; // 公用的成员
};

struct Derived_A { // 派生类A
    struct Base base; // 继承自Base
    char va; // A特有的成员
};

struct Derived_B { // 派生类B
    struct Base base; // 继承自Base
    float vb; // B特有的成员
};

void PrintA(struct Base* a) { // 打印A的值
    struct Derived_A* pa = (struct Derived_A*)a; // Base强制转换为A, 以获取A特有的成员
    printf("A: %d, %c\n", pa->base.v, pa->va);
}

void FB(struct Derived_B* b) {
    printf("FB: %f\n", (double)b->vb + (double)b->base.v);
}

void PrintB(struct Base* b) { // 打印B的值
    struct Derived_B* pb = (struct Derived_B*)b; // Base强制转换为B, 以获取B特有的成员
    printf("B: %d, %f\n", pb->base.v, pb->vb);
    FB(pb);
}

void InitA(struct Derived_A* a) { // 初始化A
    a->base.Print = PrintA; // 打印A的函数
    a->base.v = 0; // 公用的成员
    a->va = 'a';
}

void InitB(struct Derived_B* b) { // 初始化B
    b->base.Print = PrintB; // 打印B的函数
    b->base.v = 1;
    b->vb = 3.14f;
}

void PolymorphismExample(void) { // 多态使用示例
    struct Base* p; // Base指针
    struct Derived_A a;
    struct Derived_B b;

    InitA(&a); // 初始化a数据
    InitB(&b); // 初始化b数据

    p = &a.base; // 可指向a
    p->Print(p); // 用公用接口调用函数, 输出 A: 0, a

    p = &b.base; // 或指向b
    p->Print(p); // 用公用接口调用函数, 输出 B: 1, 3.140000
                 //                          FB: 4.140000
}
