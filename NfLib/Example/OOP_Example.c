#include <stdio.h>

/************ Base *************/
typedef struct Base Base;
struct Base {
    const char* name;
    int value;
    void (*Fun)(Base* this);
};

/********** Derived_F **********/
typedef struct {
    Base base;
    float f;
} Derived_F;

static inline void Fun_F(Base* this) {
    Derived_F* f = (Derived_F*)this;
    printf("name  = %s\n", f->base.name);
    printf("value = %d\n", f->base.value);
    printf("f     = %f\n", f->f);
    printf("\n");
}

static inline void Init_F(Derived_F* this) { this->base.Fun = Fun_F; }

/********** Derived_C **********/
typedef struct {
    Base base;
    char c;
} Derived_C;

static inline void Fun_C(Base* this) {
    Derived_C* c = (Derived_C*)this;
    printf("name  = %s\n", c->base.name);
    printf("value = %d\n", c->base.value);
    printf("c     = %c\n", c->c);
    printf("\n");
}

static inline void Init_C(Derived_C* this) { this->base.Fun = Fun_C; }

/*********** Example ***********/
void OOP_Example(void) {
    Base* b;
    Derived_F f;
    Derived_C c;

    Init_F(&f);
    Init_C(&c);

    f.base.name = "I'm f :-)";
    f.base.value = 123;
    f.f = 3.14f;

    c.base.name = "I'm c :-D";
    c.base.value = 321;
    c.c = 'a';

    b = (Base*)&f;
    b->Fun(b);

    b = (Base*)&c;
    b->Fun(b);
}
