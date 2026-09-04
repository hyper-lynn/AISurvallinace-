/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceOsd_H_
#define _LC_OPENAPI_CLIENT_SetDeviceOsd_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备OSD配置

 */

typedef struct SetDeviceOsdRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceOsdRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** OSD字符,不支持换行 */
		CSTR osd;
		/** 是否生效 */
		CSTR enable;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setDeviceOsd */
		#define _STATIC_SetDeviceOsdRequestData_method "setDeviceOsd"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceOsdRequest;

C_API SetDeviceOsdRequest *LCOPENAPI_INIT(SetDeviceOsdRequest);

typedef struct SetDeviceOsdResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceOsdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceOsdResponse;

C_API SetDeviceOsdResponse *LCOPENAPI_INIT(SetDeviceOsdResponse);

#endif
