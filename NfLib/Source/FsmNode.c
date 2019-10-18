#include <NfLib/FsmNode.h>
#include <string.h>

#pragma warning(disable : 4996)

FsmNode_Period* FsmNode_Period_Init(FsmNode_Period* this) {
    this->nowTime = this->preTime = this->runTimes = 0;
}

FsmNode* FsmNode_Init(
    FsmNode*    this,
    const char  name[FsmName_MaxLen],
    FsmNodeCall Func
) {
    u8 i = 0;
    strcpy(this->name, name); // 设置节点名称
    for (i = 0; i < FsmNode_MaxLineNum; ++i) {
        this->lines[i] = 0;
    } // 初始化线全为0
    this->lineSize = 0; // 线数量为0
    this->Func = Func; // 设置处于改节点时执行的函数
    for (i = 0; i < FsmNode_Period_MaxNum; ++i) {
        FsmNode_Period_Init(&this->period[i]);
    }
    return this;
}
