#include "Examples.h"

#include <NfLib/Array.h>
#include <stdio.h>

static void Print(const int* data, size_t len) {
    printf("{ ");
    while (len--) {
        printf("%d", *(data++));
        printf(len ? ", " : " }\n");
    }
}

Array_DEF(int, 123);
Array_IMPL(int, 123);

void ArrayExample() {
    Array(int, 123) a;
    int i = 444;
    int* p = 0;
    bool ok = false;

    Array(int, 123, _Init)(&a);

    printf("MaxSize = %lld\n", a.Ops()->MaxSize());

    a.Ops()->PushBack(&a, 111);
    a.Ops()->PushBack(&a, 222);
    a.Ops()->PushBack(&a, 333);
    Print(a._data, a._size);

    a.Ops()->Get(&a, 1, &p) == true ?
        printf("a[%d] == %d\n", 1, *p) :
        printf("a[%d] out of range!\n", 1);
    a.Ops()->Get(&a, 3, &p) == true ?
        printf("a[%d] == %d\n", 3, *p) :
        printf("a[%d] out of range!\n", 3);

    a.Ops()->Set(&a, 1, i) == true ?
        printf("a[%d] = %d\n", 1, i) :
        printf("a[%d] out of range!\n", 1);
    a.Ops()->Set(&a, 3, i) == true ?
        printf("a[%d] = %d\n", 3, i) :
        printf("a[%d] out of range!\n", 3);
    Print(a._data, a._size);

    a.Ops()->PopBack(&a, &i);
    Print(a._data, a._size);
    printf("%d\n", i);
}
