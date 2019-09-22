#ifndef NFLIB_PAIR_H
#define NFLIB_PAIR_H

// Pair ////////////////////////////////////////////////////////////////////////
#define _Pair(T1, T2) Pair$_##T1##_$$_##T2##_$
#define Pair(T1, T2) _Pair(T1, T2)

// DEF /////////////////////////////////////////////////////////////////////////
#define _Pair_DEF(T1, T2) typedef struct Pair(T1, T2) { T1 t1; T2 t2; } Pair(T1, T2)
#define Pair_DEF(T1, T2) _Pair_DEF(T1, T2)

#endif // NFLIB_PAIR_H
