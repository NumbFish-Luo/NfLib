#ifndef _NFLIB_TASK_GUN_H
#define _NFLIB_TASK_GUN_H

#include <NfLib/Base.h>
#include <NfLib/Ring.h>
#include <NfLib/Array.h>

// B: Bullet
// S: Size

typedef struct { u32 preTime, nowTime, cd; } TaskTimer; // cd: cool down time

typedef enum {
    TaskGun_NoBullet,
    TaskGun_HoldOn,
    TaskGun_Shoot,
    TaskGun_Dud
} TaskGun_State;

#define _TaskGun(B, S, ...) TaskGun$_##B##_$$_##S##_$##__VA_ARGS__
#define TaskGun(B, S, ...) _TaskGun(B, S, __VA_ARGS__)

#define _TaskGun_DEF(B, S)                                                      \
/* typedef */                                                                   \
typedef struct TaskGun(B, S)       TaskGun(B, S);                               \
typedef struct TaskGun(B, S, _ops) TaskGun(B, S, _ops);                         \
/* def */                                                                       \
Ring_DEF(B, S);                                                                 \
/* struct */                                                                    \
struct TaskGun(B, S) {                                                          \
    Ring(B, S) _magazine;                                                       \
    TaskTimer timer;                                                            \
    void (*TaskCall)(B bullet);                                                 \
    const TaskGun(B, S, _ops)* (*Ops) (void);                                   \
};                                                                              \
struct TaskGun(B, S, _ops) {                                                    \
    void          (*SetCD) (TaskGun(B, S)* this, u32 cd);                       \
    bool          (*Load ) (TaskGun(B, S)* this, B bullet);                     \
    TaskGun_State (*Shoot) (TaskGun(B, S)* this);                               \
};                                                                              \
void TaskGun(B, S, _Init) (TaskGun(B, S)* this, void (*TaskCall)(B bullet), u32 cd);
#define TaskGun_DEF(B, S) _TaskGun_DEF(B, S)

#define _TaskGun_IMPL(B, S)                                                     \
Ring_IMPL(B, S);                                                                \
inline static void TaskGun(B, S, _SetCD) (TaskGun(B, S)* this, u32 cd) {        \
    this->timer.cd = cd;                                                        \
}                                                                               \
inline static bool TaskGun(B, S, _Load) (TaskGun(B, S)* this, B bullet) {       \
    Ring(B, S)* m = &this->_magazine;                                           \
    return m->Ops()->PushBack(m, bullet);                                       \
}                                                                               \
inline static TaskGun_State TaskGun(B, S, _Shoot) (TaskGun(B, S)* this) {       \
    Ring(B, S)* m = &this->_magazine;                                           \
    TaskTimer* t = &this->timer;                                                \
    B b;                                                                        \
    if (m->Ops()->Size(m) == 0) { return TaskGun_NoBullet; }                    \
    t->nowTime = GET_TICK_COUNT();                                              \
    if (t->nowTime - t->preTime > t->cd) {                                      \
        t->preTime = t->nowTime;                                                \
        if (m->Ops()->PopFront(m, &b) == true) {                                \
            if (this->TaskCall != 0) {                                          \
                this->TaskCall(b);                                              \
                return TaskGun_Shoot;                                           \
            } return TaskGun_Dud;                                               \
        } return TaskGun_NoBullet;                                              \
    } return TaskGun_HoldOn;                                                    \
}                                                                               \
inline static const TaskGun(B, S, _ops)* TaskGun(B, S, _Ops) (void) {           \
    static TaskGun(B, S, _ops) ops;                                             \
    bool init = false;                                                          \
    if (init == false) {                                                        \
        init = true;                                                            \
        ops.SetCD = TaskGun(B, S, _SetCD);                                      \
        ops.Load  = TaskGun(B, S, _Load );                                      \
        ops.Shoot = TaskGun(B, S, _Shoot);                                      \
    }                                                                           \
    return &ops;                                                                \
}                                                                               \
inline void TaskGun(B, S, _Init) (TaskGun(B, S)* this, void (*TaskCall)(B bullet), u32 cd) { \
    Ring(B, S, _Init) (&this->_magazine);                                       \
    this->TaskCall = TaskCall;                                                  \
    this->timer.nowTime = this->timer.preTime = 0;                              \
    this->timer.cd = cd;                                                        \
    this->Ops = TaskGun(B, S, _Ops);                                            \
}
#define TaskGun_IMPL(B, S) _TaskGun_IMPL(B, S)

#endif // _NFLIB_TASK_GUN_H
