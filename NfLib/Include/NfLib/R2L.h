#ifndef _NFLIB_R2L_H
#define _NFLIB_R2L_H

#include <NfLib/One.h>

// right value to left value
#define _R2L(T) R2L$_##T##_$
#define R2L(T) _R2L(T)

#define _R2L_DEF(T) One(T) R2L(T) (T rv)
#define R2L_DEF(T) _R2L_DEF(T)

#define _R2L_IMPL(T) R2L_DEF(T) { One(T) tmp; tmp.data[0] = rv; return tmp; }
#define R2L_IMPL(T) _R2L_IMPL(T)

#endif // _NFLIB_R2L_H
