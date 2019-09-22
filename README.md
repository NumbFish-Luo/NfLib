# NfLib
一个不用动态内存管理的C语言工具库，探索C语言的各种奇妙写法 :-D

https://github.com/NumbFish-Luo/NfLib

画风大概如下例所示：

```c
#include "Array.h"
#include <stdio.h>

// 必须要代替编译器手动实现该类型
// 手动实现Array(int, 10)
Array_DEF(int, 10);
Array_IMPL(int, 10);

// 手动实现ForInRange
typedef void (*PrintFunc) (const int*);
ForInRange_IMPL(Array(int, 10), PrintFunc);
static inline void Print(const int* i) {
    printf("%d\n", *i);
}

void Example() {
    Array(int, 10) arr; // 创建容量为10的数组
    Array(int, 10, _Init) (&arr); // 初始化
    arr.ops->Push(&arr, 123);
    arr.ops->Push(&arr, 456);
    ForInRange(Array(int, 10), PrintFunc) (&arr, Print);
}

```

---

Array: 动态记录size的数组（可用，但还在完善中）

Bytes: 等价于Array(Byte, ...)

ForEach: 范围for操作，传入首尾迭代器及要执行的函数

ForInRange: 范围for操作，自动寻找结构体的首尾迭代器Begin和End，然后调用ForEach执行操作

Layer: 方便编辑器折叠代码

Pair: 可存双类型的数据对

Swap: 交换两个数据值

Type: 基础类型定义

---

BaseExample: Base部分使用示例
