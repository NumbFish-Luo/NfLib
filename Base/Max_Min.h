#ifndef NFLIB_MAX_MIN_H
#define NFLIB_MAX_MIN_H

#define _Max(T) Max$_##T##_$
#define _Min(T) Min$_##T##_$
#define Max(T) _Max(T)
#define Min(T) _Min(T)

#define _Max_DEF(T) T Max(T) (T lhs, T rhs)
#define _Min_DEF(T) T Min(T) (T lhs, T rhs)
#define Max_DEF(T) _Max_DEF(T)
#define Min_DEF(T) _Min_DEF(T)

#define _Max_IMPL(T) Max_DEF(T) { return lhs > rhs ? lhs : rhs; }
#define _Min_IMPL(T) Min_DEF(T) { return lhs < rhs ? lhs : rhs; }
#define Max_IMPL(T) _Max_IMPL(T)
#define Min_IMPL(T) _Min_IMPL(T)

#endif // NFLIB_MAX_MIN_H
