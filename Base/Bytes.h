#ifndef NFLIB_BYTES_H
#define NFLIB_BYTES_H

#include "Array.h"

// Bytes ///////////////////////////////////////////////////////////////////////
#define _Bytes(SIZE, ...) Array(Byte, SIZE, __VA_ARGS__)
#define Bytes(SIZE, ...) _Bytes(SIZE, __VA_ARGS__)

// DEF /////////////////////////////////////////////////////////////////////////
#define _Bytes_DEF(SIZE) Array_DEF(Byte, SIZE)
#define Bytes_DEF(SIZE) _Bytes_DEF(SIZE)

// IMPL ////////////////////////////////////////////////////////////////////////
#define _Bytes_IMPL(SIZE) Array_IMPL(Byte, SIZE)
#define Bytes_IMPL(SIZE) _Bytes_IMPL(SIZE)

#endif // NFLIB_BYTES_H
