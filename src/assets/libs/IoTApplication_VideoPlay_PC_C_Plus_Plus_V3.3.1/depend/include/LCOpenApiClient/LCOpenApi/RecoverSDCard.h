/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222589, Author: 27665, Date: 2022-04-22 15:26:31 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RecoverSDCard_H_
#define _LC_OPENAPI_CLIENT_RecoverSDCard_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
请求初始化SD卡

 */

typedef struct RecoverSDCardRequest 
{
	LCOpenApiRequest base;

	struct RecoverSDCardRequestData
	{
		
		/** 需要格式化存储介质编号,不填该参数默认设备是单sd卡 */
		CSTR index;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} RecoverSDCardRequest;

C_API RecoverSDCardRequest *LCOPENAPI_INIT(RecoverSDCardRequest);

typedef struct RecoverSDCardResponse 
{
	LCOpenApiResponse base;

	struct RecoverSDCardResponseData
	{
		
		/** 结果 */
		CSTR result;
 
	} data;

} RecoverSDCardResponse;

C_API RecoverSDCardResponse *LCOPENAPI_INIT(RecoverSDCardResponse);

#endif
