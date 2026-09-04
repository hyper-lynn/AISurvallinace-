/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetCollection_H_
#define _LC_OPENAPI_CLIENT_SetCollection_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
新增收藏点

 */

typedef struct SetCollectionRequest 
{
	LCOpenApiRequest base;

	struct SetCollectionRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 收藏点名称，不可重复，最多20个 */
		CSTR name;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setCollection */
		#define _STATIC_SetCollectionRequestData_method "setCollection"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetCollectionRequest;

C_API SetCollectionRequest *LCOPENAPI_INIT(SetCollectionRequest);

typedef struct SetCollectionResponse 
{
	LCOpenApiResponse base;

	struct SetCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetCollectionResponse;

C_API SetCollectionResponse *LCOPENAPI_INIT(SetCollectionResponse);

#endif
