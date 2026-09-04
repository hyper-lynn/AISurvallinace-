#ifndef _LCOPENAPI_CLIENT_BASEDEF_H_
#define _LCOPENAPI_CLIENT_BASEDEF_H_

#include <stdio.h>

#ifdef LCOPENAPICLIENT_EXPORTS
    #ifdef __cplusplus
    #define C_API extern "C" _declspec(dllexport)
    #else
    #define C_API _declspec(dllexport)
    #endif
#else
    #ifdef __cplusplus
    #define C_API extern "C"
    #else
    #define C_API
    #endif
#endif

#if defined(WIN32) || defined(WIN64)
typedef long long int64;
#else
#include <inttypes.h>
typedef int64_t int64;
#endif


// ²¼¶ûÐÍ BOOL
typedef int BOOL;

#endif
