/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222226, Author: 27665, Date: 2022-03-01 15:08:36 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDevice_H_
#define _LC_OPENAPI_CLIENT_BindDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备绑定

 */

typedef struct BindDeviceRequest 
{
	LCOpenApiRequest base;

	struct BindDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 安全码或设备密码，若无则填空 */
		CSTR code;
		/** 设备用户名 */
		CSTR deviceUserName;
		/** [long] */
		int64 siteId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BindDeviceRequest;

C_API BindDeviceRequest *LCOPENAPI_INIT(BindDeviceRequest);

typedef struct BindDeviceResponse 
{
	LCOpenApiResponse base;

	struct BindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindDeviceResponse;

C_API BindDeviceResponse *LCOPENAPI_INIT(BindDeviceResponse);

#endif
