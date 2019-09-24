#ifndef NFLIB_BASE_H
#define NFLIB_BASE_H

#include "Type.h"

#define ToStr(_) #_ // 变量名转成字符串
HashType StrHash(CStr str); // 字符串哈希值
void Delay(u32 delay); // 简单延时
void WarnKiller(void* anything, ...); // 忽略定义但未引用警告

#endif // NFLIB_BASE_H
