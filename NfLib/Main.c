#include <stdio.h>
#include "Example/Examples.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
int main() {
    int i;
    while (1) {
        printf(
            " 0. EXIT               \n"
            " 1. BaseExample        \n"
            " 2. ArrayExample       \n"
            " 3. FsmExample_1       \n"
            " 4. FsmExample_2       \n"
            " 5. TaskGunExample     \n"
            " 6. TaskGun_Fsm_Example\n"
            " 7. LogExample         \n"
            " 8. QuickSortExample   \n"
            " 9. PoolExample        \n"
            "10. RingExample        \n"
            "11. OOP_Example        \n"
            ">> "
        );
        scanf("%d", &i);
        if (i == 0) { break; }
        switch(i) {
        case  1: BaseExample();         break;
        case  2: ArrayExample();        break;
        case  3: FsmExample_1();        break;
        case  4: FsmExample_2();        break;
        case  5: TaskGunExample();      break;
        case  6: TaskGun_Fsm_Example(); break;
        case  7: LogExample();          break;
        case  8: QuickSortExample();    break;
        case  9: PoolExample();         break;
        case 10: RingExample();         break;
        case 11: OOP_Example();         break;
        default: break;
        }
    }
    return 0;
}
