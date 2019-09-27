#ifndef NFLIB_FOR_IN_RANGE_H
#define NFLIB_FOR_IN_RANGE_H

#include "ForEach.h"

// ForInRange //////////////////////////////////////////////////////////////////
#define _ForInRange(TYPE, FUNC) ForInRange$_##TYPE##_$$_##FUNC##_$
#define ForInRange(TYPE, FUNC) _ForInRange(TYPE, FUNC)

// DEF /////////////////////////////////////////////////////////////////////////
#define _ForInRange_DEF(TYPE, FUNC)                                             \
ForEach_DEF(TYPE##_Iter, FUNC);                                                 \
void ForInRange(TYPE, FUNC) (TYPE* data, FUNC Func)
#define ForInRange_DEF(TYPE, FUNC) _ForInRange_DEF(TYPE, FUNC)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _ForInRange_IMPL(TYPE, FUNC)                                            \
ForEach_IMPL(TYPE##_Iter, FUNC);                                                \
void ForInRange(TYPE, FUNC) (TYPE* data, FUNC Func) {                           \
    ForEach(TYPE##_Iter, FUNC) (data->ops->Begin(data), data->ops->End(data), data->ops->IterNext, Func); \
}
#define ForInRange_IMPL(TYPE, FUNC) _ForInRange_IMPL(TYPE, FUNC)

#endif // NFLIB_FOR_IN_RANGE_H
