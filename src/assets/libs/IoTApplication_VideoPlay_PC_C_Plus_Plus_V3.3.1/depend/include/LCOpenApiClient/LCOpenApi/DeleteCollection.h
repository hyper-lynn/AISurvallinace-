/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteCollection_H_
#define _LC_OPENAPI_CLIENT_DeleteCollection_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除给定的收藏点

 */

typedef struct DeleteCollectionRequest 
{
	LCOpenApiRequest base;

	struct DeleteCollectionRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 收藏点名称列表 */
		CSTR names;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]deleteCollection */
		#define _STATIC_DeleteCollectionRequestData_method "deleteCollection"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteCollectionRequest;

C_API DeleteCollectionRequest *LCOPENAPI_INIT(DeleteCollectionRequest);

typedef struct DeleteCollectionResponse 
{
	LCOpenApiResponse base;

	struct DeleteCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteCollectionResponse;

C_API DeleteCollectionResponse *LCOPENAPI_INIT(DeleteCollectionResponse);

#endif
