# NfLib

一个不用动态内存管理的C语言工具库，探索C语言的各种奇妙写法 :-D，使用方法见Main.c和各个Example文件

### 1. Base -- 基础类型

- _LAYER(layer, name) -- 使用#if和#endif来方便折叠代码

- u8x2, u8x4, u8x8 -- 方便将word, dword, qword拆成对应的n个byte
### 2. Array -- 增强型数组

- 支持双向的Push和Pop操作

### 3. Fsm -- 有限状态机

- 有限状态机:-D

### 4. TaskGun -- 任务手枪

- 完成“周期检查弹仓中是否有子弹，有的话就发射一发子弹”的逻辑，使用者可以在任意时刻往“弹仓”内添加“子弹”

### 5. QuickSort -- 快速排序

- 快速排序模板函数

### 6. Ring -- 环形队列

- 一条首尾相连的队列
