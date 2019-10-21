#ifndef _NFLIB_FUNC_H
#define _NFLIB_FUNC_H

typedef void (*Func_A) (int i);
typedef int (*Func_B) (void);
typedef int (*Func_C) (int a, int b);

typedef struct { int a, b; } Args_C;

typedef enum {
    FuncType_A,
    FuncType_B,
    FuncType_C
} FuncType;

typedef void* VoidP;

void CallFunc(FuncType t, VoidP Func, VoidP args, VoidP* result);
void CallFunc_A(Func_A Fa, int a);
void CallFunc_B(Func_B Fb, int* result);
void CallFunc_C(Func_C Fc, int a, int b, int* result);

#endif // _NFLIB_FUNC_H
