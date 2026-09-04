/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BreathingLightStatus_H_
#define _LC_OPENAPI_CLIENT_BreathingLightStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取呼吸灯状态

 */

typedef struct BreathingLightStatusRequest 
{
	LCOpenApiRequest base;

	struct BreathingLightStatusRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]breathingLightStatus */
		#define _STATIC_BreathingLightStatusRequestData_method "breathingLightStatus"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BreathingLightStatusRequest;

C_API BreathingLightStatusRequest *LCOPENAPI_INIT(BreathingLightStatusRequest);

typedef struct BreathingLightStatusResponse 
{
	LCOpenApiResponse base;

	struct BreathingLightStatusResponseData
	{
		
		/** 状态，1表示开启，0表示关闭 */
		CSTR status;
 
	} data;

} BreathingLightStatusResponse;

C_API BreathingLightStatusResponse *LCOPENAPI_INIT(BreathingLightStatusResponse);

#endif
