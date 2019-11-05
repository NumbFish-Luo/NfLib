#include <NfLib/Log.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

_Log _g_log;

#define data     _g_log._data
#define lineLen  _g_log._lineLen
#define lineSize _g_log._lineSize
#define clear    _g_log.clear

static inline _Log* EndLine(void) {
    u8 i;

#if LOG_NEW_LINE_AT_TOP

    if ((++lineSize) >= LOG_SIZE) {
        lineSize = LOG_SIZE - 1;
    }
    for (i = 0; i < lineSize; ++i) {
        memcpy(&data[lineSize - i], &data[lineSize - i - 1], LOG_LEN);
    }
    memset(&data[0], 0, LOG_LEN);

#else

    if ((++lineSize) >= LOG_SIZE) {
        lineSize = LOG_SIZE - 1;
        for (i = 0; i < LOG_SIZE - 1; ++i) {
            memcpy(&data[i], &data[i + 1], LOG_LEN);
        }
        memset(&data[LOG_SIZE - 1], 0, LOG_LEN);
    }

#endif

    lineLen = 0;

    return &_g_log;
}

static inline _Log* Add(const char* format, ...) {
    char    log[LOG_LEN];
    va_list va;
    int     result = -1;
    u8      i = 0;

    memset(log, 0, LOG_LEN);
    va_start(va, format);
    result = vsprintf(log, format, va);
    va_end(va);

    if (result < 0) {
        strcpy(log, " <?> ");
    }
    while (log[i] != '\0') {
        if (lineLen == (LOG_LEN - 1)) {
            EndLine(); continue;
        }
        if (log[i] == '\n') {
            ++i; EndLine(); continue;
        }

#if LOG_NEW_LINE_AT_TOP
        data[0][lineLen++] = log[i++];
#else
        data[lineSize][lineLen++] = log[i++];
#endif
    }

    return &_g_log;
}

static inline void Clear(void) {
    u8 i;

    for (i = 0; i < LOG_SIZE; ++i) {
        memset(data[i], 0, LOG_LEN);
    }
    lineSize = 0;
    lineLen = 0;
    clear = false;
}

static inline void HandleClear(void) {
    if (clear) {
        clear = false; Clear();
    }
}

_Log* Log(void) {
    static bool init = false;

    if (init == false) {
        init = true;

        _g_log.Clear = Clear;
        _g_log.HandleClear = HandleClear;
        _g_log.EndLine = EndLine;
        _g_log.Add = Add;

        Clear();
    }

    HandleClear();

    return &_g_log;
}

#undef data
#undef strSize
#undef lineSize
#undef clear
