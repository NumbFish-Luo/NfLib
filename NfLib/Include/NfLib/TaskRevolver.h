#ifndef _NFLIB_TASK_REVOLVER_H
#define _NFLIB_TASK_REVOLVER_H

#include <NfLib/Array.h>
#include <Windows.h>

#define TASK_BULLET_NUM 6
#define GET_TICK_COUNT() (u32)GetTickCount64()

typedef struct TaskBullet       TaskBullet;
typedef struct TaskTimer        TaskTimer;
typedef struct TaskRevolver     TaskRevolver;
typedef struct TaskRevolver_ops TaskRevolver_ops;
typedef void (*TaskFunc) (void* args);

struct TaskBullet {
    TaskFunc Func;
    void* args;
};

Array_DEF(TaskBullet, TASK_BULLET_NUM);
typedef Array(TaskBullet, TASK_BULLET_NUM) TaskMagazine;
#define TaskMagazine_Init Array(TaskBullet, TASK_BULLET_NUM, _Init)

struct TaskTimer { u32 preTime, nowTime, coolDownTime; };

struct TaskRevolver {
    TaskMagazine magazine;
    TaskTimer    timer;
    const TaskRevolver_ops* (*Ops) (void);
};

typedef enum {
    TaskRevolver_NoBullet,
    TaskRevolver_HoldOn,
    TaskRevolver_Shoot,
    TaskRevolver_Dud
} TaskRevolverState;

struct TaskRevolver_ops {
    void              (*SetCoolDownTime) (TaskRevolver* this, u32 coolDownTime);
    bool              (*Loading        ) (TaskRevolver* this, TaskFunc Func, void* args);
    TaskRevolverState (*Shoot          ) (TaskRevolver* this);
};

void TaskRevolver_Init(TaskRevolver* this, u32 coolDownTime);

#endif // _NFLIB_TASK_REVOLVER_H
