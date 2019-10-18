#ifndef _NFLIB_SWAP_H
#define _NFLIB_SWAP_H

#define _Swap(T) Swap$_##T##_$
#define Swap(T) _Swap(T)

#define _Swap_DEF(T) void Swap(T) (T* a, T* b)
#define Swap_DEF(T) _Swap_DEF(T)

#define _Swap_IMPL(T) Swap_DEF(T) { T tmp; tmp = *a; *a = *b; *b = tmp; }
#define Swap_IMPL(T) _Swap_IMPL(T)

#endif // _NFLIB_SWAP_H
