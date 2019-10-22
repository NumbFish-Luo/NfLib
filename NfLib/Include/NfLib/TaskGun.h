#ifndef _NFLIB_TASK_GUN_H
#define _NFLIB_TASK_GUN_H

#include <NfLib/Base.h>
#include <NfLib/Array.h>

typedef struct { u32 preTime, nowTime, cd; } TaskTimer;

typedef enum {
    TaskGun_NoBullet,
    TaskGun_HoldOn,
    TaskGun_Shoot,
    TaskGun_Dud
} TaskGun_State;

#define _TaskFunc(ARGS) TaskFunc$_##ARGS##_$
#define TaskFunc(ARGS) _TaskFunc(ARGS)

#define _TaskBullet(ARGS) TaskBullet$_##ARGS##_$
#define TaskBullet(ARGS) _TaskBullet(ARGS)

#define _TaskGun(ARGS, NUM, ...) TaskGun$_##ARGS##_$$_##NUM##_$##__VA_ARGS__
#define TaskGun(ARGS, NUM, ...) _TaskGun(ARGS, NUM, __VA_ARGS__)

#define _TaskBullet_DEF(ARGS)                                                   \
typedef void (*TaskFunc(ARGS)) (ARGS args);                                     \
typedef struct { TaskFunc(ARGS) Func; ARGS args; } TaskBullet(ARGS)
#define TaskBullet_DEF(ARGS) _TaskBullet_DEF(ARGS)

#define _TaskGun_DEF(ARGS, NUM)                                                 \
/* typedef */                                                                   \
typedef struct TaskGun(ARGS, NUM)       TaskGun(ARGS, NUM);                     \
typedef struct TaskGun(ARGS, NUM, _ops) TaskGun(ARGS, NUM, _ops);               \
/* def */                                                                       \
TaskBullet_DEF(ARGS);                                                           \
Array_DEF(TaskBullet(ARGS), NUM);                                               \
/* struct */                                                                    \
struct TaskGun(ARGS, NUM) {                                                     \
    Array(TaskBullet(ARGS), NUM) magazine;                                      \
    TaskTimer timer;                                                            \
    const TaskGun(ARGS, NUM, _ops)* (*Ops) (void);                              \
};                                                                              \
struct TaskGun(ARGS, NUM, _ops) {                                               \
    void          (*SetCD) (TaskGun(ARGS, NUM)* this, u32 cd);                  \
    bool          (*Load ) (TaskGun(ARGS, NUM)* this, TaskFunc(ARGS) Func, ARGS args); \
    TaskGun_State (*Shoot) (TaskGun(ARGS, NUM)* this);                          \
};                                                                              \
void TaskGun(ARGS, NUM, _Init) (TaskGun(ARGS, NUM)* this, u32 cd);
#define TaskGun_DEF(ARGS, NUM) _TaskGun_DEF(ARGS, NUM)

#define _TaskGun_IMPL(ARGS, NUM)                                                \
Array_IMPL(TaskBullet(ARGS), NUM);                                              \
static void TaskGun(ARGS, NUM, _SetCD) (TaskGun(ARGS, NUM)* this, u32 cd) {     \
    this->timer.cd = cd;                                                        \
}                                                                               \
static bool TaskGun(ARGS, NUM, _Load) (TaskGun(ARGS, NUM)* this, TaskFunc(ARGS) Func, ARGS args) { \
    Array(TaskBullet(ARGS), NUM)* magazine = &this->magazine;                   \
    TaskBullet(ARGS) bullet;                                                    \
    bullet.Func = Func;                                                         \
    bullet.args = args;                                                         \
    return magazine->Ops()->PushBack(magazine, bullet);                         \
}                                                                               \
static TaskGun_State TaskGun(ARGS, NUM, _Shoot) (TaskGun(ARGS, NUM)* this) {    \
    TaskBullet(ARGS) bullet;                                                    \
    if (this->magazine._size == 0) { return TaskGun_NoBullet; }                 \
    this->timer.nowTime = GET_TICK_COUNT();                                     \
    if (this->timer.nowTime - this->timer.preTime > this->timer.cd) {           \
        this->timer.preTime = this->timer.nowTime;                              \
        if (this->magazine.Ops()->PopFront(&this->magazine, &bullet) == true) { \
            if (bullet.Func != 0) {                                             \
                bullet.Func(bullet.args);                                       \
                return TaskGun_Shoot;                                           \
            }                                                                   \
            return TaskGun_Dud;                                                 \
        }                                                                       \
        return TaskGun_NoBullet;                                                \
    }                                                                           \
    return TaskGun_HoldOn;                                                      \
}                                                                               \
static const TaskGun(ARGS, NUM, _ops)* TaskGun(ARGS, NUM, _Ops) (void) {        \
    static TaskGun(ARGS, NUM, _ops) ops;                                        \
    bool init = false;                                                          \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.SetCD = TaskGun(ARGS, NUM, _SetCD);                                 \
        ops.Load  = TaskGun(ARGS, NUM, _Load );                                 \
        ops.Shoot = TaskGun(ARGS, NUM, _Shoot);                                 \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
void TaskGun(ARGS, NUM, _Init) (TaskGun(ARGS, NUM)* this, u32 cd) {             \
    Array(TaskBullet(ARGS), NUM, _Init) (&this->magazine);                      \
    this->timer.nowTime = this->timer.preTime = 0;                              \
    this->timer.cd = cd;                                                        \
    this->Ops = TaskGun(ARGS, NUM, _Ops);                                       \
}
#define TaskGun_IMPL(ARGS, NUM) _TaskGun_IMPL(ARGS, NUM)

#endif // _NFLIB_TASK_GUN_H
