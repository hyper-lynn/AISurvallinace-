/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ExShareDeviceDelete_H_
#define _LC_OPENAPI_CLIENT_ExShareDeviceDelete_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除设备分享权限
 */

typedef struct ExShareDeviceDeleteRequest 
{
	LCOpenApiRequest base;

	struct ExShareDeviceDeleteRequestData
	{
		
		/** 授权token */
		CSTR token;
		/** 分享的功能 */
		CSTR functions;
		/** phone */
		CSTR accountType;
		/** 被分享账号 */
		CSTR account;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ExShareDeviceDeleteRequest;

C_API ExShareDeviceDeleteRequest *LCOPENAPI_INIT(ExShareDeviceDeleteRequest);

typedef struct ExShareDeviceDeleteResponse 
{
	LCOpenApiResponse base;

	struct ExShareDeviceDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ExShareDeviceDeleteResponse;

C_API ExShareDeviceDeleteResponse *LCOPENAPI_INIT(ExShareDeviceDeleteResponse);

#endif
