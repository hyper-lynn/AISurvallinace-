/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnUsedCloudList_H_
#define _LC_OPENAPI_CLIENT_UnUsedCloudList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取未启用的云存储服务列表

 */

typedef struct UnUsedCloudListRequest 
{
	LCOpenApiRequest base;

	struct UnUsedCloudListRequestData
	{
		
		/** 上次查询最后一个deviceCloudId */
		CSTR nextDeviceCloudId;
		/** 条数 最大15 */
		CSTR limit;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** [cstr]unUsedCloudList */
		#define _STATIC_UnUsedCloudListRequestData_method "unUsedCloudList"
		CSTR method;

	} data;

} UnUsedCloudListRequest;

C_API UnUsedCloudListRequest *LCOPENAPI_INIT(UnUsedCloudListRequest);

typedef struct UnUsedCloudListResponse 
{
	LCOpenApiResponse base;

	struct UnUsedCloudListResponseData
	{
		
		/**  */
		CSTR nextDeviceCloudId;
		/** define a list with struct of UnUsedCloudListResponseData_CloudInfosElement */
		DECLARE_LIST(struct UnUsedCloudListResponseData_CloudInfosElement
		{
			/** 套餐名称 */
			CSTR name;
			/** 云存储策略id */
			CSTR strategyId;
			/** [long]云存储套餐唯一id */
			int64 deviceCloudId;
			/** [int]云存储数量 */
			int cloudCount;
			/** [int]剩余有效天数，正数表示剩余天数，-1表示未使用过 */
			int validDays;
		}) cloudInfos;
 
	} data;

} UnUsedCloudListResponse;

C_API UnUsedCloudListResponse *LCOPENAPI_INIT(UnUsedCloudListResponse);

#endif
