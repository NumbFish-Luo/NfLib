#include <NfLib/QuickSort.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
QuickSort_DEF(int);
QuickSort_IMPL(int);

int CmpInt(const int* lhs, const int* rhs) {
    if (*lhs == *rhs) { return 0; }
    return *lhs < *rhs ? -1 : 1;
}

void QuickSortInt(void) {
    int i = 0;
    int arr[10] = { 5, 9, 1, 0, 3, 4, 7, 6, 8, 2 };
    for (i = 0; i < 10; ++i) { printf("%d ", arr[i]); }
    printf("\n---\n");
    QuickSort(int) (arr, CmpInt, 0, 9);
    for (i = 0; i < 10; ++i) { printf("%d ", arr[i]); }
    // Êä³ö 0 1 2 3 4 5 6 7 8 9
    printf("\n---\n");
}

////////////////////////////////////////////////////////////////////////////////
typedef const char* Str;
QuickSort_DEF(Str);
QuickSort_IMPL(Str);

int CmpStr(const Str* lhs, const Str* rhs) { return strcmp(*lhs, *rhs); }

void QuickSortStr(void) {
    int i = 0;
    Str s[4] = { "hello", "hi", "acb", "bla bla..." };
    for (i = 0; i < 4; ++i) { printf("%s\n", s[i]); }
    printf("---\n");
    QuickSort(Str) (s, CmpStr, 0, 3);
    for (i = 0; i < 4; ++i) { printf("%s\n", s[i]); }
    // Êä³ö:
    // acb
    // bla bla...
    // hello
    // hi
    printf("---\n");
}

////////////////////////////////////////////////////////////////////////////////
void QuickSortExample(void) {
    QuickSortInt();
    QuickSortStr();
}
