#include <NfLib/TaskRevolver.h>

Array_IMPL(TaskBullet, TASK_BULLET_NUM);

static void SetCoolDownTime(TaskRevolver* this, u32 coolDownTime) {
    this->timer.coolDownTime = coolDownTime;
}

static bool Loading(TaskRevolver* this, TaskFunc Func, TaskArgs args) {
    TaskMagazine* magazine = &this->magazine;
    TaskBullet bullet;
    bullet.Func = Func;
    bullet.args = args;
    return magazine->ops->PushBack(magazine, bullet);
    return 0;
}

static TaskRevolverState Shoot(TaskRevolver* this) {
    TaskBullet bullet;
    if (this->magazine._size == 0) { return TaskRevolver_NoBullet; }
    this->timer.nowTime = GET_TICK_COUNT();
    if (this->timer.nowTime - this->timer.preTime > this->timer.coolDownTime) {
        this->timer.preTime = this->timer.nowTime;
        if (this->magazine.ops->PopFront(&this->magazine, &bullet)) {
            if (bullet.Func) {
                bullet.Func(bullet.args);
                return TaskRevolver_Shoot;
            }
            return TaskRevolver_Dud;
        }
        return TaskRevolver_NoBullet;
    }
    return TaskRevolver_HoldOn;
}

static const TaskRevolver_ops* Ops() {
    TaskRevolver_ops ops;
    bool init = false;
    if (init == false) {
        init = true;
        ops.SetCoolDownTime = SetCoolDownTime;
        ops.Loading         = Loading;
        ops.Shoot           = Shoot;
    }
    return &ops;
}

void TaskRevolver_Init(TaskRevolver* this, u32 coolDownTime) {
    TaskMagazine_Init(&this->magazine);
    this->timer.nowTime = this->timer.preTime = 0;
    this->timer.coolDownTime = coolDownTime;
    this->Ops = Ops;
}
