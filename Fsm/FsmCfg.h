#ifndef FSM_CFG_H
#define FSM_CFG_H

#include "../Base/Type.h"

// 声明 ////////////////////////////////////////////////////////////////////////
typedef struct FsmNode     FsmNode;                   // 节点
typedef enum   FsmNodeName FsmNodeName;               // 节点名称

typedef struct FsmLine     FsmLine;                   // 线
typedef enum   FsmLineName FsmLineName, FsmEventName; // 线名称, 同时也是事件名称

typedef struct Fsm         Fsm;                       // 有限状态机
typedef struct Fsm_ops     Fsm_ops;                   // 有限状态机成员函数列表

typedef void (*FsmCall)(void);                        // 状态执行函数

// 重要常量设置, 请根据需要设置合适的大小, 防止浪费内存 ////////////////////////
enum {
    FsmNode_MaxLineNum = 8, // 一个节点可存储的线的最大数量
    Fsm_MaxNodeNum     = 64 // 状态机内可存储的节点的最大数量
};

// 【暂时】用这种方法存储节点名称以及线名称, 后续将改用map去记录 ///////////////
// 节点名称
enum FsmNodeName {
    FsmNode_None = 0, // 无
    FsmNode_A    = 1, // A
    FsmNode_B    = 2, // B
    FsmNode_C    = 3  // C
};

// 线名称
enum FsmLineName {
    FsmLine_None = 0, // 无
    FsmLine_1    = 1, // 1
    FsmLine_2    = 2, // 2
    FsmLine_3    = 3  // 3
};

#endif // FSM_CFG_H
