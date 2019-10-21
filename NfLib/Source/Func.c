#include <NfLib/Func.h>

void CallFunc(FuncType t, VoidP Func, VoidP args, VoidP* result) {
    switch (t) {
    case FuncType_A: CallFunc_A((Func_A)Func, *(int*)args); break;
    case FuncType_B: CallFunc_B((Func_B)Func, (int**)result); break;
    case FuncType_C: CallFunc_C((Func_C)Func, ((Args_C*)args)->a, ((Args_C*)args)->b, (int**)result); break;
    default: break;
    }
}

void CallFunc_A(Func_A Fa, int a) { Fa(a); }
void CallFunc_B(Func_B Fb, int* result) { *result = Fb(); }
void CallFunc_C(Func_C Fc, int a, int b, int* result) { *result = Fc(a, b); }
