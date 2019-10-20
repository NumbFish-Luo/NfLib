#include <NfLib/FsmNode.h>
#include <string.h>

#pragma warning(disable : 4996)

FsmNode_Timer* FsmNode_Timer_Init(FsmNode_Timer* this) {
    this->nowTime = this->preTime = this->runTimes = 0;
    return this;
}

bool UpdateTimer(
    FsmNode*        this,
    u8              timerId,
    u32             period,
    u32             maxRunTimes,
    FsmEvent*       event,
    const FsmEvent* nextEvent)
{
    u32* nowTime  = &this->timer->nowTime ;
    u32* preTime  = &this->timer->preTime ;
    u32* runTimes = &this->timer->runTimes;
    *nowTime = GET_TICK_COUNT();
    if (*nowTime - *preTime > period) {
        *preTime = *nowTime;
        if (maxRunTimes != 0 && ++(*runTimes) > maxRunTimes) {
            *event = *nextEvent;
            return false;
        }
        return true;
    }
    return false;
}

FsmNode* FsmNode_Init(
    FsmNode*    this,
    const char  name[FsmName_MaxLen],
    FsmNodeCall Func
) {
    u8 i = 0;
    strcpy(this->name, name);
    for (i = 0; i < FsmNode_MaxLineNum; ++i) {
        this->lines[i] = 0;
    }
    this->lineSize = 0;
    this->Func = Func;
    for (i = 0; i < FsmNode_Timer_MaxNum; ++i) {
        FsmNode_Timer_Init(&this->timer[i]);
    }
    this->UpdateTimer = UpdateTimer;
    return this;
}
