/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 224087, Author: 233705, Date: 2023-01-05 16:12:18 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DevicePort_H_
#define _LC_OPENAPI_CLIENT_DevicePort_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备端口

 */

typedef struct DevicePortRequest 
{
	LCOpenApiRequest base;

	struct DevicePortRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DevicePortRequest;

C_API DevicePortRequest *LCOPENAPI_INIT(DevicePortRequest);

typedef struct DevicePortResponse 
{
	LCOpenApiResponse base;

	struct DevicePortResponseData
	{
		
		/** [int]rtsp端口 */
		int rtspPort;
		/** [int]http端口 */
		int httpPort;
		/** [int]私有协议端口 */
		int privatePort;
 
	} data;

} DevicePortResponse;

C_API DevicePortResponse *LCOPENAPI_INIT(DevicePortResponse);

#endif
