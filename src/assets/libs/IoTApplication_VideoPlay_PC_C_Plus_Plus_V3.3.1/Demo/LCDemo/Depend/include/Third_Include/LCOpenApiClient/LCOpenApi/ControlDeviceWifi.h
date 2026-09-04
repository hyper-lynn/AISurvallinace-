/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlDeviceWifi_H_
#define _LC_OPENAPI_CLIENT_ControlDeviceWifi_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
控制设备连接热点

 */

typedef struct ControlDeviceWifiRequest 
{
	LCOpenApiRequest base;

	struct ControlDeviceWifiRequestData
	{
		
		/** wifi密码 */
		CSTR password;
		/** 填需要连接的SSID */
		CSTR ssid;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** BSSID */
		CSTR bssid;
		/** [bool]连接或断开 */
		BOOL linkEnable;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ControlDeviceWifiRequest;

C_API ControlDeviceWifiRequest *LCOPENAPI_INIT(ControlDeviceWifiRequest);

typedef struct ControlDeviceWifiResponse 
{
	LCOpenApiResponse base;

	struct ControlDeviceWifiResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlDeviceWifiResponse;

C_API ControlDeviceWifiResponse *LCOPENAPI_INIT(ControlDeviceWifiResponse);

#endif
