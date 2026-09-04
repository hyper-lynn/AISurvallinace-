/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223439, Author: 304780, Date: 2022-10-12 16:27:55 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDeviceCameraStatus_H_
#define _LC_OPENAPI_CLIENT_GetDeviceCameraStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备使能开关状态。
注：仅支持PaaS设备（platform：4）；

 */

typedef struct GetDeviceCameraStatusRequest 
{
	LCOpenApiRequest base;

	struct GetDeviceCameraStatusRequestData
	{
		
		/** closeCamera：隐私遮罩；smartTrack：智能追踪；smartLocate：听声变位；aiFireControl：智能火灾控制 */
		CSTR enableType;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceCameraStatusRequest;

C_API GetDeviceCameraStatusRequest *LCOPENAPI_INIT(GetDeviceCameraStatusRequest);

typedef struct GetDeviceCameraStatusResponse 
{
	LCOpenApiResponse base;

	struct GetDeviceCameraStatusResponseData
	{
		
		/** on:开,off:关 */
		CSTR status;
		/** closeCamera：隐私遮罩；smartTrack：智能追踪；smartLocate：听声变位：aiFireControl：智能火灾控制 */
		CSTR enableType;
 
	} data;

} GetDeviceCameraStatusResponse;

C_API GetDeviceCameraStatusResponse *LCOPENAPI_INIT(GetDeviceCameraStatusResponse);

#endif
