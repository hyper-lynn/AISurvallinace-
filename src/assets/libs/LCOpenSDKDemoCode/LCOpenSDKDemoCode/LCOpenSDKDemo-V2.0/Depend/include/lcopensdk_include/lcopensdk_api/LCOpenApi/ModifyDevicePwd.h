/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyDevicePwd_H_
#define _LC_OPENAPI_CLIENT_ModifyDevicePwd_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改设备密码

 */

typedef struct ModifyDevicePwdRequest 
{
	LCOpenApiRequest base;

	struct ModifyDevicePwdRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]modifyDevicePwd */
		#define _STATIC_ModifyDevicePwdRequestData_method "modifyDevicePwd"
		CSTR method;
		/** 新密码 */
		CSTR newPwd;
		/** 老密码 */
		CSTR oldPwd;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyDevicePwdRequest;

C_API ModifyDevicePwdRequest *LCOPENAPI_INIT(ModifyDevicePwdRequest);

typedef struct ModifyDevicePwdResponse 
{
	LCOpenApiResponse base;

	struct ModifyDevicePwdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyDevicePwdResponse;

C_API ModifyDevicePwdResponse *LCOPENAPI_INIT(ModifyDevicePwdResponse);

#endif
