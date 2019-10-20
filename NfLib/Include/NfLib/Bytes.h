#ifndef _NFLIB_BYTES_H
#define _NFLIB_BYTES_H

#include <NfLib/Array.h>

#define _Bytes(SIZE, ...) Array(u8, SIZE, ...)
#define Bytes(SIZE, ...) _Bytes(SIZE, ...)

#define _Bytes_DEF(SIZE) Array_DEF(u8, SIZE)
#define Bytes_DEF(SIZE) _Bytes_DEF(SIZE)

#define _Bytes_IMPL(SIZE) Array_IMPL(u8, SIZE)
#define Bytes_IMPL(SIZE) _Bytes_IMPL(SIZE)

#endif // _NFLIB_BYTES_H
