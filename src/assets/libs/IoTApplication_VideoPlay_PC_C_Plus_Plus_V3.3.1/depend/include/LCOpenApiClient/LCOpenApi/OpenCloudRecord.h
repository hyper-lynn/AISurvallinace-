/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_OpenCloudRecord_H_
#define _LC_OPENAPI_CLIENT_OpenCloudRecord_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
开通云存储

 */

typedef struct OpenCloudRecordRequest 
{
	LCOpenApiRequest base;

	struct OpenCloudRecordRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [long]云存储套餐ID */
		int64 strategyId;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]openCloudRecord */
		#define _STATIC_OpenCloudRecordRequestData_method "openCloudRecord"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} OpenCloudRecordRequest;

C_API OpenCloudRecordRequest *LCOPENAPI_INIT(OpenCloudRecordRequest);

typedef struct OpenCloudRecordResponse 
{
	LCOpenApiResponse base;

	struct OpenCloudRecordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} OpenCloudRecordResponse;

C_API OpenCloudRecordResponse *LCOPENAPI_INIT(OpenCloudRecordResponse);

#endif
