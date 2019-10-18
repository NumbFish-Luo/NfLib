#include "Examples.h"

#include <NfLib/Array.h>
#include <stdio.h>

static void Print(const int* data, unsigned short len) {
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
    int i;

    printf("MaxSize = %d\n", Array(int, 123, _Init)(&a)->ops->MaxSize());

    a.ops->PushBack(&a, 111);
    a.ops->PushBack(&a, 222);
    a.ops->PushBack(&a, 333);
    Print(a._data, a._size);

    a.ops->PopBack(&a, &i);
    Print(a._data, a._size);
    printf("%d\n", i);
}
