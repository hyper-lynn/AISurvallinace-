/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PanoPictureGet_H_
#define _LC_OPENAPI_CLIENT_PanoPictureGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取全景图
 */

typedef struct PanoPictureGetRequest 
{
	LCOpenApiRequest base;

	struct PanoPictureGetRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PanoPictureGetRequest;

C_API PanoPictureGetRequest *LCOPENAPI_INIT(PanoPictureGetRequest);

typedef struct PanoPictureGetResponse 
{
	LCOpenApiResponse base;

	struct PanoPictureGetResponseData
	{
		
		/** 全景图URL */
		CSTR url;
 
	} data;

} PanoPictureGetResponse;

C_API PanoPictureGetResponse *LCOPENAPI_INIT(PanoPictureGetResponse);

#endif
