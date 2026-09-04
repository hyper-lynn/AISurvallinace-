/*
* Copyright (c) 2008, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：osIndependent.h
* 摘　　要：方便Linux移植。
*
*
* 取代版本：0.1
* 原作者　：周善存
* 完成日期：2008年8月14日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#ifndef DH_OSINDEPENDENT_H
#define DH_OSINDEPENDENT_H

#if defined(WIN32) || defined(WIN64)

#include <windows.h>

#else

#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dlfcn.h> 
#ifdef MAC
#include <mach/semaphore.h>
#include <mach/task.h>
#include <mach/mach.h>
typedef struct sem_t {

    semaphore_t msem;

    int value;

}  sem_t;
#else
#include <semaphore.h>
#endif
#include "dh_atomic.h"

#endif

#include "platform.h"
#include "globaldef.h"
#include <list>
#include <string>
#include <vector>
#include <map>

#if !(defined(WIN32))
/*
//  WINDOWS中的宏定义
#define DWORD           unsigned int
#define BOOL            int
#define TRUE            1
#define FALSE           0
#define LONG            DWORD
#define WORD            unsigned short
#define BYTE            unsigned char
#define UINT            unsigned int
#define __int64         long long int
#define HANDLE          void*
#define HWND            void*
#define INFINITE        0xFFFFFFFF
#define HDC             void*
#define LPVOID          void*
#define LPDWORD         DWORD*
#define LPBYTE          BYTE*
#define STATUS_WAIT_0   ((DWORD)0x00000000L)
#define WAIT_OBJECT_0   ((STATUS_WAIT_0) + 0)
#define SOCKET          unsigned int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR    (-1)
#define SD_RECEIVE      SHUT_RD
#define SD_SEND         SHUT_WR
#define SD_BOTH         SHUT_RDWR
#ifndef NULL
#define NULL            0
#endif
#define closesocket(S)  close(S)
#define WINAPI
#define Sleep(x)        usleep(x*1000)
#define HINSTANCE       void*
#define LPCSTR          const char*
#define __stdcall
#define CALLBACK

typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
*/
#endif

//////////////////////////////////////////////////////////////////////////

namespace MobileApi
{
    
class INTERFACE_API_CLASS COSEvent
{
public:
    COSEvent();
    virtual ~COSEvent();

#if defined(WIN32) || defined(WIN64)
    HANDLE      m_hEvent;
#elif defined(IOS)
    sem_t*      m_hEvent;
    char        szName[12];
#else
    sem_t       m_hEvent;
#endif
    BOOL        m_bCreate;
    BOOL        m_bManualReset;
};

class INTERFACE_API_CLASS COSThread
{
public:
    COSThread();
    virtual ~COSThread();

#if defined(WIN32) || defined(WIN64)
    HANDLE      m_hThread;
#else
    pthread_t   m_hThread;
#endif
    BOOL        m_bCreate;
};


//////////////////////////////////////////////////////////////////////////
//  定义WINDOWS与LINUX通用的库函数，避免代码太多的#ifdef...#else...#endif，影响可读性。

#define OS_EVENT        COSEvent
#define OS_THREAD       COSThread

#if defined(WIN32) || defined(WIN64)
    #define OS_THREAD_ID    DWORD
#else
    #define OS_THREAD_ID    pthread_t
#endif


#if defined(WIN32) || defined(WIN64)

#define LN_LIFECOUNT    LONG

#else

#define LN_LIFECOUNT    atomic_t

#endif

#ifdef __cplusplus  
extern "C" {    
#endif
//  库函数，返回值：>=0：成功；<0：失败

INTERFACE_API int   CreateEventEx(OS_EVENT &event, BOOL bManualReset, BOOL bInitialState);

INTERFACE_API void  CloseEventEx(OS_EVENT &event);

INTERFACE_API BOOL  SetEventEx(OS_EVENT &event);

BOOL        ResetEventEx(OS_EVENT &event);

INTERFACE_API DWORD WaitForSingleObjectEx_Event(OS_EVENT &event,  DWORD dwMilliseconds);

INTERFACE_API DWORD WaitForSingleObjectEx_Thread(OS_THREAD &thread, DWORD dwMilliseconds);


INTERFACE_API int   CreateThreadEx(OS_THREAD &thread, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

INTERFACE_API void  CloseThreadEx(OS_THREAD &thread);

INTERFACE_API BOOL  TerminateThreadEx(OS_THREAD &thread, DWORD dwExitCode);

OS_THREAD_ID GetCurrentThreadIdEx();

INTERFACE_API DWORD GetTickCountEx();

INTERFACE_API LONG  InterlockedIncrementEx(LN_LIFECOUNT *lpAddend);

INTERFACE_API LONG  InterlockedDecrementEx(LN_LIFECOUNT *lpAddend);

INTERFACE_API void  InterlockedSetEx(LN_LIFECOUNT *lpAddend, int value);

/*
    获取MD5值
*/
INTERFACE_API void  md5_hexstr_Low(const char* input, size_t len, char* output);

#ifdef __cplusplus  
}  
#endif

INTERFACE_API HINSTANCE LoadLibraryEx(LPCSTR lpLibFileName);

INTERFACE_API void*     GetProcAddressEx(HINSTANCE hModule, LPCSTR lpProcName);

BOOL        FreeLibraryEx(HINSTANCE hLibModule);

char*       __rfind(char *string, const char *strCharSet);

void        Change_Utf8_Assic(unsigned char * pUTF8, char *destbuf);

void        Change_Assic_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);

DWORD       AlarmTypeToInt(char* szBuf);

void        AlarmTypeToString(DWORD dwAlarmType, char* szBuf, int nType = 0);

DWORD       EventStrToCode(const char* szBuf);
void        EventCodeToStr(DWORD dwAlarmType, char* szBuf);

int         TranslateAlarmType(int nDevAlarmType);

int         ConvertUtf8ToAnsi(const char* lpszUtf8, int nUtf8Len, char* lpszAnsi, int nAnsiLen);
int         ConvertAnsiToUtf8(const char* lpszAnsi, int nAnsiLen, char* lpszUtf8, int nUtf8Len);
std::string ConvertUtf8ToAnsi(const std::string& strUtf8);
void        ConvertUtf8ToAnsi( const std::string& strUtf8, char* szRetAnsi, int nMaxRetLen);
std::string ConvertAnsiToUtf8(const std::string& strAnsi);

char*       GetProtocolValue(const char *szBuf, const char *szKey1, const char *szKey2, char *szOutBuf, int nOutLen);

int GetModulePathLen(char* cFileName);

void        md5_hexstr(const char* input, size_t len, char* output);


DWORD ParseStreamType(char *pszVideoStream);
std::string PacketStreamType(const DWORD &dwVideoStream);

// 清除指针内容的List
template<class T>
void ClearPointList( std::list<T*>& ls )
{
    typename std::list<T*>::iterator it = ls.begin();
    for (; it != ls.end(); ++it)
    {
        if (*it)
        {
            delete *it;
        }
    }
    ls.clear();
}

void Trace( const char* pszFmt, ... );
void WriteLog(const char* pszFmt, ...);

#ifndef TRACE
#   ifdef _DEBUG
#       define TRACE Trace
#   else
#       define TRACE  1 ? (void)0 : Trace
#   endif
#endif

// 将IPC厂商字符串转换为相应类型
BYTE TranslateIPCType(const char* szType);

// 将IPC厂商类型转换为相应字符串
void TranslateIPCTypeTostr(BYTE byType, char* szType);

//  WINDOWS中有，LINUX中没有的库函数
#if defined(WIN32) || defined(WIN64)
#else

char*       _strupr(char *string);
char*       _strlwr(char *string);
int         _stricmp(const char *string1, const char *string2);
char*       _strrev(char *string);
char*       itoa(int value, char *string, int radix);

#endif

//////////////////////////////////////////////////////////////////////////

#define GLOBAL_SINGLETON_DECLARE(classname)     \
static classname * instance();

#define GLOBAL_SINGLETON_IMPLEMENT(classname)   \
classname * classname::instance()               \
{                                               \
    static classname * _instance = 0;           \
    if(0 == _instance)                          \
    {                                           \
        _instance = new classname;              \
    }                                           \
    return _instance;                           \
}

#define GLOBAL_SINGLETON_DELETE

//////////////////////////////////////////////////////////////////////////
//  大小端转换

//  IN_LINE 宏定义来决定是否使用inline, inline可能使得可执行文件变大，但提升速度
#ifdef  IN_LINE
#define INLINE_CALL inline
#else
#define INLINE_CALL
#endif

void INLINE_CALL DHTIME_LittleToBig(unsigned char *src, unsigned char *des);
void INLINE_CALL DHTIME_BigToLittle(unsigned char *src, unsigned char *des);
void INLINE_CALL INT_LittleToBig(unsigned char *src, unsigned char *des);
void INLINE_CALL INT_BigToLittle(unsigned char *src, unsigned char *des);
void INLINE_CALL FS_LittleToBig(unsigned char *src, unsigned char *des);
void INLINE_CALL FS_BigToLittle(unsigned char *src, unsigned char *des);
void INLINE_CALL WORD_LittleToBig(unsigned char *src, unsigned char *des);
void INLINE_CALL WORD_BigToLittle(unsigned char *src, unsigned char *des);
void INLINE_CALL WORD_INT_LittleToBig(unsigned char *src, unsigned char *des);
void INLINE_CALL INT_WORD_BigToLittle(unsigned char *src, unsigned char *des);



//_SELF,表示转化的src和des是相同地址，那么在没有BIG_ENDIAN定义的时候不需要做什么
#ifdef __BIG_ENDIAN__
        #define ECM_INT_L2B(src, des)       INT_LittleToBig(src, des)
        #define ECM_INT_B2L(src, des)       INT_BigToLittle(src, des)
        #define ECM_INT_L2B_SELF(src, des)  INT_LittleToBig(src, des)
        #define ECM_INT_B2L_SELF(src, des)  INT_BigToLittle(src, des)
        #define ECM_DWORD_L2B(src, des)     ECM_INT_L2B(src, des)
        #define ECM_DWORD_B2L(src, des)     ECM_INT_B2L(src, des)
        #define ECM_WORD_L2B(src, des)      WORD_LittleToBig(src, des)
        #define ECM_WORD_B2L(src, des)      WORD_BigToLittle(src, des)
        #define ECM_WORD_INT_L2B(src, des)  WORD_INT_LittleToBig(src, des)
        #define ECM_INT_WORD_B2L(src, des)  INT_WORD_BigToLittle(src, des)
        #define ECM_ULONG_B2L(src, des)         ECM_INT_B2L(src, des)
        #define ECM_ULONG_L2B(src, des)         ECM_INT_L2B(src, des)
        #define ECM_USHORT_B2L(src, des)        ECM_WORD_B2L(src, des)
        #define ECM_USHORT_L2B(src, des)        ECM_WORD_L2B(src, des)

        //DH data type
        #define ECM_DHTIME_L2B(src, des)        DHTIME_LittleToBig(src, des)
        #define ECM_DHTIME_B2L(src, des)        DHTIME_BigToLittle(src, des)
        #define ECM_DHTIME_L2B_SELF(src, des)   ECM_DHTIME_L2B(src, des)
        #define ECM_DHTIME_B2L_SELF(src, des)   ECM_DHTIME_B2L(src, des)
        #define ECM_FS_L2B(src, des)            FS_LittleToBig(src, des)
        #define ECM_FS_B2L(src, des)            FS_BigToLittle(src, des)
        #define ECM_FS_L2B_SELF(src, des)       ECM_FS_L2B(src, des)
        #define ECM_FS_B2L_SELF(src, des)       ECM_FS_B2L(src, des)
#else

        #define ECM_INT_L2B(src, des)       {(*(int*)(des))   = (*(int*)(src));}
        #define ECM_INT_B2L(src, des)       {(*(int*)(des))   = (*(int*)(src));}
        #define ECM_INT_L2B_SELF(src, des)
        #define ECM_INT_B2L_SELF(src, des)
        #define ECM_DWORD_L2B(src, des)     {(*(DWORD*)(des)) = (*(DWORD*)(src));}
        #define ECM_DWORD_B2L(src, des)     {(*(DWORD*)(des)) = (*(DWORD*)(src));}
        #define ECM_WORD_L2B(src, des)      {(*(WORD*)(des))  = (*(WORD*)(src));}
        #define ECM_WORD_B2L(src, des)      {(*(WORD*)(des))  = (*(WORD*)(src));}
        #define ECM_WORD_INT_L2B(src, des)  {(*(int*)(des))   = (*(WORD*)(src));}
        #define ECM_INT_WORD_B2L(src, des)  {(*(WORD*)(des))  = (*(int*)(src));}
        #define ECM_ULONG_B2L(src, des)     {(*(unsigned long*)(des))  = (*(unsigned long*)(src));}
        #define ECM_ULONG_L2B(src, des)     {(*(unsigned long*)(des))  = (*(unsigned long*)(src));}
        #define ECM_USHORT_B2L(src, des)    {(*(short*)(des))  = (*(short*)(src));}
        #define ECM_USHORT_L2B(src, des)    {(*(short*)(des))  = (*(short*)(src));}

        //DH data type
        #define ECM_DHTIME_L2B(src, des)        {memcpy((des),(src), sizeof(DHTIME));}
        #define ECM_DHTIME_B2L(src, des)        {memcpy((des),(src), sizeof(DHTIME));}
        #define ECM_DHTIME_L2B_SELF(src, des)
        #define ECM_DHTIME_B2L_SELF(src, des)
        #define ECM_FS_L2B(src, des)            {memcpy((des),(src), sizeof(FS));}
        #define ECM_FS_B2L(src, des)            {memcpy((des),(src), sizeof(FS));}
        #define ECM_FS_L2B_SELF(src, des)
        #define ECM_FS_B2L_SELF(src, des)
#endif
    
}

//////////////////////////////////////////////////////////////////////////


#endif  //  DH_OSINDEPENDENT_H



