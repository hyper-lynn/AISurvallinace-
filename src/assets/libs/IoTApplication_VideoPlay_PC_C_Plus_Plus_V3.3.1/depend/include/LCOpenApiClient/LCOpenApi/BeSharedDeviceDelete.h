/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BeSharedDeviceDelete_H_
#define _LC_OPENAPI_CLIENT_BeSharedDeviceDelete_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除被分享的设备权限（别人分享给我的设备）
 */

typedef struct BeSharedDeviceDeleteRequest 
{
	LCOpenApiRequest base;

	struct BeSharedDeviceDeleteRequestData
	{
		
		/** 分享的功能 */
		CSTR functions;
		/** 授权token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} BeSharedDeviceDeleteRequest;

C_API BeSharedDeviceDeleteRequest *LCOPENAPI_INIT(BeSharedDeviceDeleteRequest);

typedef struct BeSharedDeviceDeleteResponse 
{
	LCOpenApiResponse base;

	struct BeSharedDeviceDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BeSharedDeviceDeleteResponse;

C_API BeSharedDeviceDeleteResponse *LCOPENAPI_INIT(BeSharedDeviceDeleteResponse);

#endif
