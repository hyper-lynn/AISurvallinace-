/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyBreathingLight_H_
#define _LC_OPENAPI_CLIENT_ModifyBreathingLight_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置呼吸灯状态

 */

typedef struct ModifyBreathingLightRequest 
{
	LCOpenApiRequest base;

	struct ModifyBreathingLightRequestData
	{
		
		/** 状态，on表示开启，off表示关闭 */
		CSTR status;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]modifyBreathingLight */
		#define _STATIC_ModifyBreathingLightRequestData_method "modifyBreathingLight"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyBreathingLightRequest;

C_API ModifyBreathingLightRequest *LCOPENAPI_INIT(ModifyBreathingLightRequest);

typedef struct ModifyBreathingLightResponse 
{
	LCOpenApiResponse base;

	struct ModifyBreathingLightResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyBreathingLightResponse;

C_API ModifyBreathingLightResponse *LCOPENAPI_INIT(ModifyBreathingLightResponse);

#endif
