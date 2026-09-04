/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyCollection_H_
#define _LC_OPENAPI_CLIENT_ModifyCollection_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改已存在的收藏点名称

 */

typedef struct ModifyCollectionRequest 
{
	LCOpenApiRequest base;

	struct ModifyCollectionRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 新的收藏点名称 */
		CSTR newName;
		/** 旧的收藏点名称 */
		CSTR oldName;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]modifyCollection */
		#define _STATIC_ModifyCollectionRequestData_method "modifyCollection"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyCollectionRequest;

C_API ModifyCollectionRequest *LCOPENAPI_INIT(ModifyCollectionRequest);

typedef struct ModifyCollectionResponse 
{
	LCOpenApiResponse base;

	struct ModifyCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyCollectionResponse;

C_API ModifyCollectionResponse *LCOPENAPI_INIT(ModifyCollectionResponse);

#endif
