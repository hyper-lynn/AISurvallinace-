/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteGroupDevice_H_
#define _LC_OPENAPI_CLIENT_DeleteGroupDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分组下删除设备

 */

typedef struct DeleteGroupDeviceRequest 
{
	LCOpenApiRequest base;

	struct DeleteGroupDeviceRequestData
	{
		
		/** [cstr]deleteGroupDevice */
		#define _STATIC_DeleteGroupDeviceRequestData_method "deleteGroupDevice"
		CSTR method;
		/** [long]分组Id */
		int64 groupId;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteGroupDeviceRequest;

C_API DeleteGroupDeviceRequest *LCOPENAPI_INIT(DeleteGroupDeviceRequest);

typedef struct DeleteGroupDeviceResponse 
{
	LCOpenApiResponse base;

	struct DeleteGroupDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteGroupDeviceResponse;

C_API DeleteGroupDeviceResponse *LCOPENAPI_INIT(DeleteGroupDeviceResponse);

#endif
