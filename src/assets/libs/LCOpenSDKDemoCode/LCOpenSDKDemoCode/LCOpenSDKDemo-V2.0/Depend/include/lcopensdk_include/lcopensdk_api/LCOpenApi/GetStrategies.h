/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetStrategies_H_
#define _LC_OPENAPI_CLIENT_GetStrategies_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取所有云存储套餐

 */

typedef struct GetStrategiesRequest 
{
	LCOpenApiRequest base;

	struct GetStrategiesRequestData
	{
		
		/** [cstr]getStrategies */
		#define _STATIC_GetStrategiesRequestData_method "getStrategies"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetStrategiesRequest;

C_API GetStrategiesRequest *LCOPENAPI_INIT(GetStrategiesRequest);

typedef struct GetStrategiesResponse 
{
	LCOpenApiResponse base;

	struct GetStrategiesResponseData
	{
		
		/** define a list with struct of GetStrategiesResponseData_StrategiesElement */
		DECLARE_LIST(struct GetStrategiesResponseData_StrategiesElement
		{
			/** 云存储套餐存储时间 */
			CSTR recordStorageTimeLimit;
			/** 云录像host */
			CSTR description;
			/** [int]套餐ID */
			int strategyId;
			/** 套餐使用有效时长（天） */
			CSTR timeLimit;
			/** 图片Url */
			CSTR picUrl;
			/** 名称 */
			CSTR name;
			/** 云录像port */
			CSTR fee;
		}) strategies;
 
	} data;

} GetStrategiesResponse;

C_API GetStrategiesResponse *LCOPENAPI_INIT(GetStrategiesResponse);

#endif
