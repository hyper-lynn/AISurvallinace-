/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223440, Author: 304780, Date: 2022-10-13 13:50:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceCameraStatus_H_
#define _LC_OPENAPI_CLIENT_SetDeviceCameraStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备使能开关；
注：仅支持PaaS设备（platform：4）；

 */

typedef struct SetDeviceCameraStatusRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceCameraStatusRequestData
	{
		
		/** closeCamera：隐私遮罩；smartTrack：智能追踪；smartLocate：听声变位；aiFireControl：智能火灾控制 */
		CSTR enableType;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [bool]遮蔽开关（true:开；false:关） */
		BOOL enable;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setDeviceCameraStatus */
		#define _STATIC_SetDeviceCameraStatusRequestData_method "setDeviceCameraStatus"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceCameraStatusRequest;

C_API SetDeviceCameraStatusRequest *LCOPENAPI_INIT(SetDeviceCameraStatusRequest);

typedef struct SetDeviceCameraStatusResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceCameraStatusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceCameraStatusResponse;

C_API SetDeviceCameraStatusResponse *LCOPENAPI_INIT(SetDeviceCameraStatusResponse);

#endif
