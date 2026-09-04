/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetEncryptDetailInner_H_
#define _LC_OPENAPI_CLIENT_GetEncryptDetailInner_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取单个设备的信息

 */

typedef struct GetEncryptDetailInnerRequest 
{
	LCOpenApiRequest base;

	struct GetEncryptDetailInnerRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetEncryptDetailInnerRequest;

C_API GetEncryptDetailInnerRequest *LCOPENAPI_INIT(GetEncryptDetailInnerRequest);

typedef struct GetEncryptDetailInnerResponse 
{
	LCOpenApiResponse base;

	struct GetEncryptDetailInnerResponseData
	{
		
		/** [int]套餐状态 -1：未开通， 0:过期 1:使用中 */
		int strategyStatus;
		/** 套餐结束时间 */
		CSTR endTime;
 
	} data;

} GetEncryptDetailInnerResponse;

C_API GetEncryptDetailInnerResponse *LCOPENAPI_INIT(GetEncryptDetailInnerResponse);

#endif
