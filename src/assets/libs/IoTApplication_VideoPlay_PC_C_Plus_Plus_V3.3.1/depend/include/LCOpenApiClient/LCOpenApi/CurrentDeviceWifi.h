/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CurrentDeviceWifi_H_
#define _LC_OPENAPI_CLIENT_CurrentDeviceWifi_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备当前连接的热点信息

 */

typedef struct CurrentDeviceWifiRequest 
{
	LCOpenApiRequest base;

	struct CurrentDeviceWifiRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} CurrentDeviceWifiRequest;

C_API CurrentDeviceWifiRequest *LCOPENAPI_INIT(CurrentDeviceWifiRequest);

typedef struct CurrentDeviceWifiResponse 
{
	LCOpenApiResponse base;

	struct CurrentDeviceWifiResponseData
	{
		
		/** 若连接了热点，填热点的名称；若未连接，填空 */
		CSTR ssid;
		/** 可选 ,通道，大于14认为是5G频段，小于等于14是2.4G频段 */
		CSTR channel;
		/**  可选 强度，单位为dbm */
		CSTR sigStrength;
		/** 强度，0最弱，5最强 */
		CSTR intensity;
		/** [bool]是否连接了wifi */
		BOOL linkEnable;
 
	} data;

} CurrentDeviceWifiResponse;

C_API CurrentDeviceWifiResponse *LCOPENAPI_INIT(CurrentDeviceWifiResponse);

#endif
