/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetUserAuthTaget_H_
#define _LC_OPENAPI_CLIENT_SetUserAuthTaget_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置授权对象(单一设备授权)
 */

typedef struct SetUserAuthTagetRequest 
{
	LCOpenApiRequest base;

	struct SetUserAuthTagetRequestData
	{
		
		/** [long]角色ID */
		int64 roleId;
		/** [cstr]setUserAuthTaget */
		#define _STATIC_SetUserAuthTagetRequestData_method "setUserAuthTaget"
		CSTR method;
		/** 被授权的手机号 */
		CSTR userPhone;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetUserAuthTagetRequest;

C_API SetUserAuthTagetRequest *LCOPENAPI_INIT(SetUserAuthTagetRequest);

typedef struct SetUserAuthTagetResponse 
{
	LCOpenApiResponse base;

	struct SetUserAuthTagetResponseData
	{
		
		/** [long]授权Id */
		int64 authId;
 
	} data;

} SetUserAuthTagetResponse;

C_API SetUserAuthTagetResponse *LCOPENAPI_INIT(SetUserAuthTagetResponse);

#endif
