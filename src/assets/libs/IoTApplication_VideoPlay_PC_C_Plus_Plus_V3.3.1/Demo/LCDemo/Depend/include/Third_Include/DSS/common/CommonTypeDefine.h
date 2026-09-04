/*
* Copyright (c) 2012, 浙江大华技术股份有限公司
* All rights reserved.
*
* 摘　　要：数据类型定义
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef __COMMON_TYPE_DEFINE_H_
#define __COMMON_TYPE_DEFINE_H_


//#define SF_BIG_ENDIAN         // 大端宏
//#define WIN32                 // 32位Windows
//#define WIN64                 // 64位Windows
//#define LINUX32               // 32位Linux
//#define LINUX64               // 64位Linux
//#define MACOS32               // 32位MAC
//#define MACOS64               // 64位MAC


#define SF_NAMESPACE_BEGIN      namespace SF_SOFT_BASE {
#define SF_NAMESPACE_END        };


//////////////////////////////////////////////////////////////////////////

#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#else
#ifndef BOOL
#define BOOL    int
#endif

#ifndef INT32
#define INT32   int
#endif

#ifndef UINT32
#define UINT32  unsigned int
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef PBYTE
#define PBYTE unsigned char*
#endif

#ifndef HANDLE
#define HANDLE void*
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#endif




#endif // !__SF_DATADEF_H_



