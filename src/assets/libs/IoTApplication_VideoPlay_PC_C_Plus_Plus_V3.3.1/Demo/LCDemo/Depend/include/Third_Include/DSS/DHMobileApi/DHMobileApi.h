
#ifndef DHMobileApi_h__
#define DHMobileApi_h__

#include "../globaldef.h"

// base type define
#include "platform.h"

// base system api define
// #include "dh_atomic.h"
#include "dhmutex.h"
#include "ReadWriteMutex.h"
#include "osIndependent.h"

// base version define
#include "versionctl.h"

// base lib define
#include "Md5.h"
#include "Base64.h"
#include "Des.h"

// base func define
#include "atomiccount.h"
#include "Referable.h"
#include "AutoBuffer.h"

#include "Global.h"

#include "encode_algorithm.h"
// base debug
#include "LogTime.h"
#include "DHEventHandler.h"



#ifdef __cplusplus  
extern "C" {    
#endif

// 消息分发接口
//INTERFACE_API void DHPostMsg(DHEventHandler* pHandle, int param1, int param2);

INTERFACE_API void DHPostComand(int nMsgCommnd, int param1, int param2);

#ifdef __cplusplus  
}  
#endif

#endif // DHMobileApi_h__
