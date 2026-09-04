/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RefreshDeviceCover_H_
#define _LC_OPENAPI_CLIENT_RefreshDeviceCover_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备/通道封面刷新

 */

typedef struct RefreshDeviceCoverRequest 
{
	LCOpenApiRequest base;

	struct RefreshDeviceCoverRequestData
	{
		
		/** [cstr]refreshDeviceCover */
		#define _STATIC_RefreshDeviceCoverRequestData_method "refreshDeviceCover"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} RefreshDeviceCoverRequest;

C_API RefreshDeviceCoverRequest *LCOPENAPI_INIT(RefreshDeviceCoverRequest);

typedef struct RefreshDeviceCoverResponse 
{
	LCOpenApiResponse base;

	struct RefreshDeviceCoverResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} RefreshDeviceCoverResponse;

C_API RefreshDeviceCoverResponse *LCOPENAPI_INIT(RefreshDeviceCoverResponse);

#endif
