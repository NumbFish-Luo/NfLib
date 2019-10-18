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
    strcpy(this->name, name); // ���ýڵ�����
    for (i = 0; i < FsmNode_MaxLineNum; ++i) {
        this->lines[i] = 0;
    } // ��ʼ����ȫΪ0
    this->lineSize = 0; // ������Ϊ0
    this->Func = Func; // ���ô��ڸĽڵ�ʱִ�еĺ���
    for (i = 0; i < FsmNode_Period_MaxNum; ++i) {
        FsmNode_Period_Init(&this->period[i]);
    }
    return this;
}
