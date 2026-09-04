/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225593, Author: 112352, Date: 2023-12-07 20:35:25 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetStreamErrorMsg_H_
#define _LC_OPENAPI_CLIENT_GetStreamErrorMsg_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取拉流结果，如果发生错误，返回内容将包含错误码和错误信息

 */

typedef struct GetStreamErrorMsgRequest 
{
	LCOpenApiRequest base;

	struct GetStreamErrorMsgRequestData
	{
		
		/** 拉流URL diget */
		CSTR digest;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetStreamErrorMsgRequest;

C_API GetStreamErrorMsgRequest *LCOPENAPI_INIT(GetStreamErrorMsgRequest);

typedef struct GetStreamErrorMsgResponse 
{
	LCOpenApiResponse base;

	struct GetStreamErrorMsgResponseData
	{
		
		/** 错误信息 */
		CSTR msg;
		/** 错误码 */
		CSTR code;
 
	} data;

} GetStreamErrorMsgResponse;

C_API GetStreamErrorMsgResponse *LCOPENAPI_INIT(GetStreamErrorMsgResponse);

#endif
