#ifndef NFLIB_BASE_H
#define NFLIB_BASE_H

#include "Type.h"

#define ToStr(_) #_ // ������ת���ַ���
HashType StrHash(CStr str); // �ַ�����ϣֵ
void Delay(u32 delay); // ����ʱ
void WarnKiller(void* anything, ...); // ���Զ��嵫δ���þ���

#endif // NFLIB_BASE_H
