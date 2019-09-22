#ifndef NFLIB_FOR_EACH_H
#define NFLIB_FOR_EACH_H

// ForEach /////////////////////////////////////////////////////////////////////
#define _ForEach(ITER, FUNC) ForEach$_##ITER##_$$_##FUNC##_$
#define ForEach(ITER, FUNC) _ForEach(ITER, FUNC)

// DEF /////////////////////////////////////////////////////////////////////////
#define _ForEach_DEF(ITER, FUNC) void ForEach(ITER, FUNC) (ITER begin, ITER end, FUNC Func)
#define ForEach_DEF(ITER, FUNC) _ForEach_DEF(ITER, FUNC)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _ForEach_IMPL(ITER, FUNC) void ForEach(ITER, FUNC) (ITER begin, ITER end, FUNC Func) { \
    for (; begin != end; ++begin) { Func(begin); }                              \
}
#define ForEach_IMPL(ITER, FUNC) _ForEach_IMPL(ITER, FUNC)

#endif // NFLIB_FOR_EACH_H
