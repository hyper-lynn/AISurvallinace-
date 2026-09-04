/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetCollection_H_
#define _LC_OPENAPI_CLIENT_GetCollection_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取已添加的收藏点名称信息

 */

typedef struct GetCollectionRequest 
{
	LCOpenApiRequest base;

	struct GetCollectionRequestData
	{
		
		/** [cstr]getCollection */
		#define _STATIC_GetCollectionRequestData_method "getCollection"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetCollectionRequest;

C_API GetCollectionRequest *LCOPENAPI_INIT(GetCollectionRequest);

typedef struct GetCollectionResponse 
{
	LCOpenApiResponse base;

	struct GetCollectionResponseData
	{
		
		/** define a list with struct of GetCollectionResponseData_CollectionsElement */
		DECLARE_LIST(struct GetCollectionResponseData_CollectionsElement
		{
			/** 收藏点名称 */
			CSTR name;
		}) collections;
 
	} data;

} GetCollectionResponse;

C_API GetCollectionResponse *LCOPENAPI_INIT(GetCollectionResponse);

#endif
