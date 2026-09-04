/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsWifi_GetDeviceWifiStateFromServer_H_
#define _HSVIEW_CLIENT_API_thingsWifi_GetDeviceWifiStateFromServer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备wifi信息查询，直接从服务缓存拉取

--------------------请求参数说明---------------------------------------
linkEnable：[bool],当前有无连接热点
SSID: [string]若连接了热点，填热点的名称；若未连接，填空。
intensity:[string], 强度。0最弱，5最强
sigStrength:[string], 强度，可选，单位为dbm
------------------------------------------------------------------------

参考PaaS协议：[设备电量查询](http://paas.dahuatech.com/wiki/?p=%2F%E4%BA%8B%E4%BB%B6%E4%B8%8A%E6%8A%A5%2F%E4%BF%A1%E6%81%AF%E4%BA%8B%E4%BB%B6%2F%E8%AE%BE%E5%A4%87Wifi%E4%B8%8A%E6%8A%A5.md&s=pd

【需要使用平台账号签名】
 */

typedef struct thingsWifi_GetDeviceWifiStateFromServerRequest 
{
	HsviewRequest base;

	struct thingsWifi_GetDeviceWifiStateFromServerRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsWifi_GetDeviceWifiStateFromServerRequest;

C_API thingsWifi_GetDeviceWifiStateFromServerRequest *HSAPI_INIT(thingsWifi_GetDeviceWifiStateFromServerRequest);

typedef struct thingsWifi_GetDeviceWifiStateFromServerResponse 
{
	HsviewResponse base;

	struct thingsWifi_GetDeviceWifiStateFromServerResponseData
	{
		
		/** [O]强度，可选，单位为dbm */
		CSTR sigStrength;
		/** [O]强度。0最弱，5最强 */
		CSTR intensity;
		/** [O]若连接了热点，填热点的名称；若未连接，填空 */
		CSTR SSID;
		/** [bool]当前有无连接热点 */
		BOOL linkEnable;
 
	} data;

} thingsWifi_GetDeviceWifiStateFromServerResponse;

C_API thingsWifi_GetDeviceWifiStateFromServerResponse *HSAPI_INIT(thingsWifi_GetDeviceWifiStateFromServerResponse);

#endif
