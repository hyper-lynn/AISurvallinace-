/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223658, Author: 34944, Date: 2022-11-10 09:33:20 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDeviceV2_H_
#define _LC_OPENAPI_CLIENT_BindDeviceV2_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备绑定

 */

typedef struct BindDeviceV2Request 
{
	LCOpenApiRequest base;

	struct BindDeviceV2RequestData
	{
		
		/** 设备名称 */
		CSTR deviceName;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 安全码或设备密码，若无则填空 */
		CSTR code;
		/** 站点ID */
		CSTR siteId;
		/** 设备用户名 */
		CSTR deviceUserName;
		/** 设备类型 */
		CSTR deviceCatalog;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BindDeviceV2Request;

C_API BindDeviceV2Request *LCOPENAPI_INIT(BindDeviceV2Request);

typedef struct BindDeviceV2Response 
{
	LCOpenApiResponse base;

	struct BindDeviceV2ResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindDeviceV2Response;

C_API BindDeviceV2Response *LCOPENAPI_INIT(BindDeviceV2Response);

#endif
