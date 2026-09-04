/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225593, Author: 112352, Date: 2023-12-07 20:35:25 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TurnCollection_H_
#define _LC_OPENAPI_CLIENT_TurnCollection_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
转动设备到目标收藏点
备注：需要设备存在CollectionPoint收藏点位能力集
 */

typedef struct TurnCollectionRequest 
{
	LCOpenApiRequest base;

	struct TurnCollectionRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备类型，可选，针对ehome设备不需要校验预置点信息（ehome:ehome设备，gb:国标设备） */
		CSTR deviceType;
		/** 收藏点名称 */
		CSTR name;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]turnCollection */
		#define _STATIC_TurnCollectionRequestData_method "turnCollection"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} TurnCollectionRequest;

C_API TurnCollectionRequest *LCOPENAPI_INIT(TurnCollectionRequest);

typedef struct TurnCollectionResponse 
{
	LCOpenApiResponse base;

	struct TurnCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TurnCollectionResponse;

C_API TurnCollectionResponse *LCOPENAPI_INIT(TurnCollectionResponse);

#endif
