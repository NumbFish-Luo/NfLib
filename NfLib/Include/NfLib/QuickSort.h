#ifndef _NFLIB_QUICK_SORT_H
#define _NFLIB_QUICK_SORT_H

#include <NfLib/Swap.h>

// Patition ////////////////////////////////////////////////////////////////////

#define _Patition(T) Patition$_##T##_$
#define Patition(T) _Patition(T)

#define _Patition_DEF(T)                                                        \
Swap_DEF(T);                                                                    \
int Patition(T) (T a[], int (*Cmp) (const T*, const T*), int l, int r)
#define Patition_DEF(T) _Patition_DEF(T)

#define _Patition_IMPL(T)                                                       \
Swap_IMPL(T);                                                                   \
int Patition(T) (T a[], int (*Cmp) (const T*, const T*), int l, int r) {        \
    int j = l;                                                                  \
    int i = j - 1;                                                              \
    T k = a[r];                                                                 \
    for (; j < r; ++j) { if (Cmp(&a[j], &k) <= 0) { Swap(T) (&a[j], &a[++i]); } } \
    Swap(T) (&a[r], &a[++i]);                                                   \
    return i;                                                                   \
}
#define Patition_IMPL(T) _Patition_IMPL(T)

// QuickSort ///////////////////////////////////////////////////////////////////

#define _QuickSort(T) QuickSort$_##T##_$
#define QuickSort(T) _QuickSort(T)

#define _QuickSort_DEF(T)                                                       \
Patition_DEF(T);                                                                \
void QuickSort(T) (T a[], int (*Cmp) (const T*, const T*), int l, int r)
#define QuickSort_DEF(T) _QuickSort_DEF(T)

#define _QuickSort_IMPL(T)                                                      \
Patition_IMPL(T);                                                               \
void QuickSort(T) (T a[], int (*Cmp) (const T*, const T*), int l, int r) {      \
    int m;                                                                      \
    if (l >= r) { return; }                                                     \
    m = Patition(T) (a, Cmp, l, r);                                             \
    QuickSort(T) (a, Cmp, l, m - 1);                                            \
    QuickSort(T) (a, Cmp, m + 1, r);                                            \
}
#define QuickSort_IMPL(T) _QuickSort_IMPL(T)

#endif // _NFLIB_QUICK_SORT_H
