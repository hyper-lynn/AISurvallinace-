/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AddGroupDevice_H_
#define _LC_OPENAPI_CLIENT_AddGroupDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分组下增加设备

 */

typedef struct AddGroupDeviceRequest 
{
	LCOpenApiRequest base;

	struct AddGroupDeviceRequestData
	{
		
		/** [cstr]addGroupDevice */
		#define _STATIC_AddGroupDeviceRequestData_method "addGroupDevice"
		CSTR method;
		/** [long]分组Id */
		int64 groupId;
		/** 通道编号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备编号 */
		CSTR deviceId;

	} data;

} AddGroupDeviceRequest;

C_API AddGroupDeviceRequest *LCOPENAPI_INIT(AddGroupDeviceRequest);

typedef struct AddGroupDeviceResponse 
{
	LCOpenApiResponse base;

	struct AddGroupDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddGroupDeviceResponse;

C_API AddGroupDeviceResponse *LCOPENAPI_INIT(AddGroupDeviceResponse);

#endif
