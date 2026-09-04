/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyPassword_H_
#define _LC_OPENAPI_CLIENT_ModifyPassword_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改设备密码，此仅对有"TCM"设备能力级的设备有效，设备管理相关的接口中会返回该设备是否具备TCM设备能力级，设备能力级介绍请见：设备能力级；

 */

typedef struct ModifyPasswordRequest 
{
	LCOpenApiRequest base;

	struct ModifyPasswordRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 新密码 */
		CSTR newPassword;
		/** [cstr]modifyPassword */
		#define _STATIC_ModifyPasswordRequestData_method "modifyPassword"
		CSTR method;
		/** 老密码 */
		CSTR oldPassword;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyPasswordRequest;

C_API ModifyPasswordRequest *LCOPENAPI_INIT(ModifyPasswordRequest);

typedef struct ModifyPasswordResponse 
{
	LCOpenApiResponse base;

	struct ModifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyPasswordResponse;

C_API ModifyPasswordResponse *LCOPENAPI_INIT(ModifyPasswordResponse);

#endif
