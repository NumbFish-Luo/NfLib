#ifndef _NFLIB_TASK_GUN_H
#define _NFLIB_TASK_GUN_H

#include <NfLib/Base.h>
#include <NfLib/Array.h>

// A: Args
// S: Size

typedef struct { u32 preTime, nowTime, cd; } TaskTimer;

typedef enum {
    TaskGun_NoBullet,
    TaskGun_HoldOn,
    TaskGun_Shoot,
    TaskGun_Dud
} TaskGun_State;

#define _TaskFunc(A) TaskFunc$_##A##_$
#define TaskFunc(A) _TaskFunc(A)

#define _TaskBullet(A) TaskBullet$_##A##_$
#define TaskBullet(A) _TaskBullet(A)

#define _TaskGun(A, S, ...) TaskGun$_##A##_$$_##S##_$##__VA_ARGS__
#define TaskGun(A, S, ...) _TaskGun(A, S, __VA_ARGS__)

#define _TaskBullet_DEF(A)                                                      \
typedef void (*TaskFunc(A)) (A args);                                           \
typedef struct { TaskFunc(A) Func; A args; } TaskBullet(A)
#define TaskBullet_DEF(A) _TaskBullet_DEF(A)

#define _TaskGun_DEF(A, S)                                                      \
/* typedef */                                                                   \
typedef struct TaskGun(A, S)       TaskGun(A, S);                               \
typedef struct TaskGun(A, S, _ops) TaskGun(A, S, _ops);                         \
/* def */                                                                       \
TaskBullet_DEF(A);                                                              \
Array_DEF(TaskBullet(A), S);                                                    \
/* struct */                                                                    \
struct TaskGun(A, S) {                                                          \
    Array(TaskBullet(A), S) _magazine;                                          \
    TaskTimer timer;                                                            \
    const TaskGun(A, S, _ops)* (*Ops) (void);                                   \
};                                                                              \
struct TaskGun(A, S, _ops) {                                                    \
    void          (*SetCD) (TaskGun(A, S)* this, u32 cd);                       \
    bool          (*Load ) (TaskGun(A, S)* this, TaskFunc(A) Func, A args);     \
    TaskGun_State (*Shoot) (TaskGun(A, S)* this);                               \
};                                                                              \
void TaskGun(A, S, _Init) (TaskGun(A, S)* this, u32 cd);
#define TaskGun_DEF(A, S) _TaskGun_DEF(A, S)

#define _TaskGun_IMPL(A, S)                                                     \
Array_IMPL(TaskBullet(A), S);                                                   \
inline static void TaskGun(A, S, _SetCD) (TaskGun(A, S)* this, u32 cd) {        \
    this->timer.cd = cd;                                                        \
}                                                                               \
inline static bool TaskGun(A, S, _Load) (TaskGun(A, S)* this, TaskFunc(A) Func, A args) { \
    Array(TaskBullet(A), S)* _magazine = &this->_magazine;                      \
    TaskBullet(A) bullet;                                                       \
    bullet.Func = Func;                                                         \
    bullet.args = args;                                                         \
    return _magazine->Ops()->PushBack(_magazine, bullet);                       \
}                                                                               \
inline static TaskGun_State TaskGun(A, S, _Shoot) (TaskGun(A, S)* this) {       \
    TaskBullet(A) bullet;                                                       \
    if (this->_magazine._size == 0) { return TaskGun_NoBullet; }                \
    this->timer.nowTime = GET_TICK_COUNT();                                     \
    if (this->timer.nowTime - this->timer.preTime > this->timer.cd) {           \
        this->timer.preTime = this->timer.nowTime;                              \
        if (this->_magazine.Ops()->PopFront(&this->_magazine, &bullet) == true) { \
            if (bullet.Func != 0) {                                             \
                bullet.Func(bullet.args);                                       \
                return TaskGun_Shoot;                                           \
            } return TaskGun_Dud;                                               \
        } return TaskGun_NoBullet;                                              \
    } return TaskGun_HoldOn;                                                    \
}                                                                               \
inline static const TaskGun(A, S, _ops)* TaskGun(A, S, _Ops) (void) {           \
    static TaskGun(A, S, _ops) ops;                                             \
    bool init = false;                                                          \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.SetCD = TaskGun(A, S, _SetCD);                                      \
        ops.Load  = TaskGun(A, S, _Load );                                      \
        ops.Shoot = TaskGun(A, S, _Shoot);                                      \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
inline void TaskGun(A, S, _Init) (TaskGun(A, S)* this, u32 cd) {                \
    Array(TaskBullet(A), S, _Init) (&this->_magazine);                          \
    this->timer.nowTime = this->timer.preTime = 0;                              \
    this->timer.cd = cd;                                                        \
    this->Ops = TaskGun(A, S, _Ops);                                            \
}
#define TaskGun_IMPL(A, S) _TaskGun_IMPL(A, S)

#endif // _NFLIB_TASK_GUN_H
