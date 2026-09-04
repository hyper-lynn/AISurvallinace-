/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetPreparation_H_
#define _LC_OPENAPI_CLIENT_GetPreparation_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取预案

 */

typedef struct GetPreparationRequest 
{
	LCOpenApiRequest base;

	struct GetPreparationRequestData
	{
		
		/** [cstr]getPreparation */
		#define _STATIC_GetPreparationRequestData_method "getPreparation"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPreparationRequest;

C_API GetPreparationRequest *LCOPENAPI_INIT(GetPreparationRequest);

typedef struct GetPreparationResponse 
{
	LCOpenApiResponse base;

	struct GetPreparationResponseData
	{
		
		/** 设备支持预案 */
		CSTR preparation;
		/** 已设置预案 */
		CSTR selected;
 
	} data;

} GetPreparationResponse;

C_API GetPreparationResponse *LCOPENAPI_INIT(GetPreparationResponse);

#endif
