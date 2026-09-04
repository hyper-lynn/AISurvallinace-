/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225593, Author: 112352, Date: 2023-12-07 20:35:25 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_Device3DPosition_H_
#define _LC_OPENAPI_CLIENT_Device3DPosition_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备三维定位
 */

typedef struct Device3DPositionRequest 
{
	LCOpenApiRequest base;

	struct Device3DPositionRequestData
	{
		
		/** [int] */
		DECLARE_LIST(int) startPoint;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]device3DPosition */
		#define _STATIC_Device3DPositionRequestData_method "device3DPosition"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** [int] */
		DECLARE_LIST(int) endPoint;
		/** 设备ID */
		CSTR deviceId;

	} data;

} Device3DPositionRequest;

C_API Device3DPositionRequest *LCOPENAPI_INIT(Device3DPositionRequest);

typedef struct Device3DPositionResponse 
{
	LCOpenApiResponse base;

	struct Device3DPositionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} Device3DPositionResponse;

C_API Device3DPositionResponse *LCOPENAPI_INIT(Device3DPositionResponse);

#endif
