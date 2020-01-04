#include "Examples.h"
#include <NfLib/Ring.h>

Ring_DEF(int, 5);
Ring_IMPL(int, 5);

static void PrintRing(Ring(int, 5)* ring) {
    int i;
    printf("... ");
    for (i = 0; i < 5; ++i) {
        if (i == ring->_head) { printf("|> "); }
        if (i == ring->_tail) { printf("<| "); }
        printf("%d, ", ring->_data[i]);
    }
    printf("...\n");
}

void RingExample(void) {
    int i, j;
    Ring(int, 5) ring;

    Ring(int, 5, _Init) (&ring);
    for (i = 0; i < 5; ++i) { ring._data[i] = 0; }

    while (1) {
        printf("\n");
        PrintRing(&ring);
        printf("0. EXIT      \n"
               "1. push back \n"
               "2. push front\n"
               "3. pop  back \n"
               "4. pop  front\n"
               "5. get       \n"
               "6. set       \n"
               ">> ");
        scanf("%d", &i);
        if (i == 0) { printf("\n--------------------------------\n\n"); break; }
        switch (i) {
        case 1:
            printf("push >> "); scanf("%d", &i);
            ring.Ops()->PushBack (&ring, i);
            break;
        case 2:
            printf("push >> "); scanf("%d", &i);
            ring.Ops()->PushFront(&ring, i);
            break;
        case 3: 
            if (ring.Ops()->PopBack (&ring, &i)) { printf("pop back: %d \n", i); }
            break;
        case 4:
            if (ring.Ops()->PopFront(&ring, &i)) { printf("pop front: %d\n", i); }
            break;
        case 5:
            printf("i >> "); scanf("%d", &i);
            if (ring.Ops()->Get(&ring, i, &i)) { printf("get: %d\n", i); }
            else { printf("get: error!\n"); }
            break;
        case 6:
            printf("i >> "); scanf("%d", &i);
            printf("set >> "); scanf("%d", &j);
            if (!ring.Ops()->Set(&ring, i, j)) { printf("set: error!\n"); }
            break;
        default: break;
        }
    }
}
