/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SirenGet_H_
#define _LC_OPENAPI_CLIENT_SirenGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取警笛状态
 */

typedef struct SirenGetRequest 
{
	LCOpenApiRequest base;

	struct SirenGetRequestData
	{
		
		/** 客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式，如20180301T111730 */
		CSTR clientLocalTime;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SirenGetRequest;

C_API SirenGetRequest *LCOPENAPI_INIT(SirenGetRequest);

typedef struct SirenGetResponse 
{
	LCOpenApiResponse base;

	struct SirenGetResponseData
	{
		
		/** 客户端请求中的clientLocalTime值，将Req的值原样带回 */
		CSTR clientLocalTime;
		/** [O]探照灯开关状态，on-开启，off-关闭 */
		CSTR searchLight;
		/** [O]白光灯开关状态，on:开启，off:关闭 */
		CSTR whiteLight;
		/** 响铃倒计时剩余时间，单位为秒，若为-1则表示未响铃 */
		CSTR time;
 
	} data;

} SirenGetResponse;

C_API SirenGetResponse *LCOPENAPI_INIT(SirenGetResponse);

#endif
