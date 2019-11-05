#ifndef _NFLIB_LOG_H
#define _NFLIB_LOG_H

#include <NfLib/Base.h>

#define LOG_SIZE            32
#define LOG_LEN             32
#define LOG_NEW_LINE_AT_TOP  0

typedef struct _Log _Log;
struct _Log {
    char  _data[LOG_SIZE][LOG_LEN];
    u8    _lineLen;
    u8    _lineSize;
    bool  clear;
    void  (*Clear) (void);
    void  (*HandleClear) (void);
    _Log* (*EndLine) (void);
    _Log* (*Add) (const char* format, ...);
};

extern _Log _g_log;
_Log* Log(void);

#endif // _NFLIB_LOG_H
