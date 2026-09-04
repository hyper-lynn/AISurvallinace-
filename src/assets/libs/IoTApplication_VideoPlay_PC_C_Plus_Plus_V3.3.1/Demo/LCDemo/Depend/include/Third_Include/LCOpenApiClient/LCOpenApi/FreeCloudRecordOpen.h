/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_FreeCloudRecordOpen_H_
#define _LC_OPENAPI_CLIENT_FreeCloudRecordOpen_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备通道开通免费云存储套餐
 */

typedef struct FreeCloudRecordOpenRequest 
{
	LCOpenApiRequest base;

	struct FreeCloudRecordOpenRequestData
	{
		
		/** [long]云服务套餐id */
		int64 strategyId;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} FreeCloudRecordOpenRequest;

C_API FreeCloudRecordOpenRequest *LCOPENAPI_INIT(FreeCloudRecordOpenRequest);

typedef struct FreeCloudRecordOpenResponse 
{
	LCOpenApiResponse base;

	struct FreeCloudRecordOpenResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} FreeCloudRecordOpenResponse;

C_API FreeCloudRecordOpenResponse *LCOPENAPI_INIT(FreeCloudRecordOpenResponse);

#endif
