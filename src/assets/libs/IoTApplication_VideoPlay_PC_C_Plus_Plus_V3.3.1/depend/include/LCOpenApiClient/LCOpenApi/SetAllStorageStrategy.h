/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetAllStorageStrategy_H_
#define _LC_OPENAPI_CLIENT_SetAllStorageStrategy_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置云存储套餐开或关

 */

typedef struct SetAllStorageStrategyRequest 
{
	LCOpenApiRequest base;

	struct SetAllStorageStrategyRequestData
	{
		
		/** 状态，1表示开启，0表示关闭 */
		CSTR status;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetAllStorageStrategyRequest;

C_API SetAllStorageStrategyRequest *LCOPENAPI_INIT(SetAllStorageStrategyRequest);

typedef struct SetAllStorageStrategyResponse 
{
	LCOpenApiResponse base;

	struct SetAllStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAllStorageStrategyResponse;

C_API SetAllStorageStrategyResponse *LCOPENAPI_INIT(SetAllStorageStrategyResponse);

#endif
