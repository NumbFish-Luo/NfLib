#ifndef NFLIB_SWAP_H
#define NFLIB_SWAP_H

// Swap ////////////////////////////////////////////////////////////////////////
#define _Swap(T) Swap$_##T##_$
#define Swap(T) _Swap(T)

// DEF /////////////////////////////////////////////////////////////////////////
#define _Swap_DEF(T) void Swap(T)(T* lhs, T* rhs)
#define Swap_DEF(T) _Swap_DEF(T)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _Swap_IMPL(T) void Swap(T)(T* lhs, T* rhs) {                            \
    T tmp;                                                                      \
    tmp = *lhs;                                                                 \
    *lhs = *rhs;                                                                \
    *rhs = tmp;                                                                 \
}
#define Swap_IMPL(T) _Swap_IMPL(T)

#endif // NFLIB_SWAP_H
