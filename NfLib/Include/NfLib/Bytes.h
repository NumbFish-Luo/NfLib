#ifndef _NFLIB_BYTES_H
#define _NFLIB_BYTES_H

#include <NfLib/Array.h>

// S: Size

#define _Bytes(S, ...) Array(u8, S, __VA_ARGS__)
#define Bytes(S, ...) _Bytes(S, __VA_ARGS__)

#define _Bytes_DEF(S) Array_DEF(u8, S)
#define Bytes_DEF(S) _Bytes_DEF(S)

#define _Bytes_IMPL(S) Array_IMPL(u8, S)
#define Bytes_IMPL(S) _Bytes_IMPL(S)

#endif // _NFLIB_BYTES_H
