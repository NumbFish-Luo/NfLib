#include <NfLib/Func.h>
#include <stdio.h>

static void Fa(int i) { printf("Fa: %d\n", i); }
static int Fb(void) { printf("Fb: "); return 321; }
static int Fc(int a, int b) { printf("Fc: %d + %d = ", a, b); return a + b; }

void FuncExample() {
    int aa = 123;
    int ra = 123;
    Args_C ac = { 123, 321 };
    int rc = 123;
    CallFunc(FuncType_A, Fa, (VoidP)&aa, 0);
    CallFunc(FuncType_B, Fb, 0, (VoidP)&ra);
    printf("%d\n", ra);
    CallFunc(FuncType_C, Fc, (VoidP)&ac, (VoidP)&rc);
    printf("%d\n", rc);
}
