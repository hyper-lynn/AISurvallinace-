/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryDeviceOsd_H_
#define _LC_OPENAPI_CLIENT_QueryDeviceOsd_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备OSD配置

 */

typedef struct QueryDeviceOsdRequest 
{
	LCOpenApiRequest base;

	struct QueryDeviceOsdRequestData
	{
		
		/** [cstr]setDeviceOsd */
		#define _STATIC_QueryDeviceOsdRequestData_method "setDeviceOsd"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryDeviceOsdRequest;

C_API QueryDeviceOsdRequest *LCOPENAPI_INIT(QueryDeviceOsdRequest);

typedef struct QueryDeviceOsdResponse 
{
	LCOpenApiResponse base;

	struct QueryDeviceOsdResponseData
	{
		
		/** OSD使能开关（on使能打开,off使能关闭） */
		CSTR enable;
		/** OSD字符，对应设备端channelTitle，不支持换行 */
		CSTR osd;
 
	} data;

} QueryDeviceOsdResponse;

C_API QueryDeviceOsdResponse *LCOPENAPI_INIT(QueryDeviceOsdResponse);

#endif
