#ifndef _NFLIB_ONE_H
#define _NFLIB_ONE_H

#define _One(T) One$_##T##_$
#define One(T) _One(T)

#define _One_DEF(T) typedef struct { T data[1]; } One(T)
#define One_DEF(T) _One_DEF(T)

#endif // _NFLIB_ONE_H
