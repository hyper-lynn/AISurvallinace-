/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetStorageStrategy_H_
#define _LC_OPENAPI_CLIENT_SetStorageStrategy_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置免费云存储套餐开或关

 */

typedef struct SetStorageStrategyRequest 
{
	LCOpenApiRequest base;

	struct SetStorageStrategyRequestData
	{
		
		/** [cstr]setStorageStrategy */
		#define _STATIC_SetStorageStrategyRequestData_method "setStorageStrategy"
		CSTR method;
		/** 状态，on表示开启，off表示关闭 */
		CSTR status;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetStorageStrategyRequest;

C_API SetStorageStrategyRequest *LCOPENAPI_INIT(SetStorageStrategyRequest);

typedef struct SetStorageStrategyResponse 
{
	LCOpenApiResponse base;

	struct SetStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetStorageStrategyResponse;

C_API SetStorageStrategyResponse *LCOPENAPI_INIT(SetStorageStrategyResponse);

#endif
