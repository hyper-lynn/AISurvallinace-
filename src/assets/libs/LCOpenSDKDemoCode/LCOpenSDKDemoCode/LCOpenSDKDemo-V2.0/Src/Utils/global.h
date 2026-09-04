#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif //_WIN32

#include <qglobal.h>
#include <string>
#include <QSize>
using namespace std;

#define REST_ERR                (99)
#define HTTP_ERR                (-1000)
#define BUSINESS_ERR            (-1001)

#define RET_OK (0)
#define RET_FAIL (-1)
#define OUT
#define VAR_NAME(x) (#x)
#define LOG_TAG ("LC_OPENSDK_DEMO")

inline void logPrintf(const char *tag, const char *file, int line, const char *function, const char *format, ...)
{
    if (NULL == tag || NULL == file || NULL == line || NULL == function || NULL == format)
    {
        return;
    }

    char buffer[1024] = {0};
    va_list vaList;
    va_start(vaList, format);
    vsprintf_s(buffer, sizeof(buffer), format, vaList);
    va_end(vaList);

#ifdef _WIN32
    char log[1024*2] = {0};
    sprintf_s(log, sizeof(log), "%s|<%s:%d>[%s] %s", LOG_TAG, file, line, function, buffer);
    OutputDebugStringA(log);
#else
    qDebug("%s|<%s:%d>[%s] %s", LOG_TAG, file, line, function, buffer);
#endif //_WIN32
}

#define FILE_NAME(x) {strrchr(x, '\\') ? strrchr(x, '\\')+1 : x}
#define DLOG(FMT, ...)                                                          \
{                                                                               \
    const char *fileName = FILE_NAME(__FILE__);                                 \
    logPrintf(LOG_TAG, fileName, __LINE__, __FUNCTION__, FMT, ## __VA_ARGS__);  \
}

#define SAFE_DELETE(x)                  { if((x) != NULL) { /*DLOG("safe delete %s[0x%08x]\n", VAR_NAME(x), x);*/ delete (x); (x) = NULL; } }
#define SAFE_DELETE_ARRAY(x)            { if((x) != NULL) { delete[] (x); (x) = NULL; } }

#endif //__GLOBAL_H__

