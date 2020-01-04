#include "Examples.h"
#include <NfLib/Pool.h>

#define POOL_SIZE 50
Pool_DEF(int, POOL_SIZE);
Pool_IMPL(int, POOL_SIZE);

void PrintPool(const Pool(int, POOL_SIZE)* pool) {
    size_t i, j = 0;
    for (i = 0; i < POOL_SIZE; ++i) {
        if (j != 0 && j--) { printf("[] "); }
        else if (pool->_size[i] == 0) { printf("__ "); }
        else {
            printf("%2lld ", pool->_size[i]);
            j = pool->_size[i] - 1;
        }
    }
    printf("\n");
}

void PoolExample(void) {
    Pool(int, POOL_SIZE) pool;
    int* p[POOL_SIZE] = {0};
    bool r = false;
    char c;
    int i;
    size_t s;

    Pool(int, POOL_SIZE, _Init) (&pool);

#pragma warning(disable:6031)
    while (1) {
        printf("\nn. new\nd. delete\ne. exit\n>> ");
        scanf(" %c", &c);
        if (c == 'e') { break; }
        printf("p[?]\n>> ");
        scanf("%d", &i);
        if (i < 0 || i >= POOL_SIZE) {
            printf("[E] out of bound of array!\n");
            continue;
        }
        if (c == 'n') {
            printf("size = ?\n>> ");
            scanf("%lld", &s);
            p[i] = pool.Ops()->New(&pool, s);
        } else if (c == 'd') {
            if (pool.Ops()->Delete(&pool, &p[i])) { printf("[S] delete ok\n"); }
            else { printf("[E] delete fail\n"); }
        }
        PrintPool(&pool);
        printf("p[%d]: %p\n", i, p[i]);
    }
}
