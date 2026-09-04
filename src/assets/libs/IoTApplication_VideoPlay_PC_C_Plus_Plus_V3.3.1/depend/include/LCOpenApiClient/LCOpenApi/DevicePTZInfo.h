/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DevicePTZInfo_H_
#define _LC_OPENAPI_CLIENT_DevicePTZInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备通道当前PTZ信息

 */

typedef struct DevicePTZInfoRequest 
{
	LCOpenApiRequest base;

	struct DevicePTZInfoRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道号 */
		CSTR channelId;
		/** [cstr]devicePTZInfo */
		#define _STATIC_DevicePTZInfoRequestData_method "devicePTZInfo"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DevicePTZInfoRequest;

C_API DevicePTZInfoRequest *LCOPENAPI_INIT(DevicePTZInfoRequest);

typedef struct DevicePTZInfoResponse 
{
	LCOpenApiResponse base;

	struct DevicePTZInfoResponseData
	{
		
		/** 水平位置 */
		CSTR h;
		/** 变倍倍数 */
		CSTR z;
		/** 垂直位置 */
		CSTR v;
 
	} data;

} DevicePTZInfoResponse;

C_API DevicePTZInfoResponse *LCOPENAPI_INIT(DevicePTZInfoResponse);

#endif
