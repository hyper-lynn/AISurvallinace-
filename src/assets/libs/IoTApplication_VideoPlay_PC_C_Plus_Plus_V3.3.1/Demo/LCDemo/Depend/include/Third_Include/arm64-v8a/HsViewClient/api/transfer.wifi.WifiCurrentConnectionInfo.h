/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiCurrentConnectionInfo_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiCurrentConnectionInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取当前WIFI热点信息

参考PaaS协议：[获取当前WIFI热点信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E8%8E%B7%E5%8F%96%E5%BD%93%E5%89%8DWIFI%E7%83%AD%E7%82%B9%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiCurrentConnectionInfoRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiCurrentConnectionInfoRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/wifi/current */
		#define _STATIC_transferWifi_WifiCurrentConnectionInfoRequestData_url "/device/wifi/current"
		CSTR url;

	} data;

} transferWifi_WifiCurrentConnectionInfoRequest;

C_API transferWifi_WifiCurrentConnectionInfoRequest *HSAPI_INIT(transferWifi_WifiCurrentConnectionInfoRequest);

typedef struct transferWifi_WifiCurrentConnectionInfoResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiCurrentConnectionInfoResponseData
	{
		
		/** [int]强度，0最弱，5最强 */
		int intensity;
		/** [O],通道，大于14认为是5G频段，小于等于14是2.4G频段 */
		CSTR channel;
		/** [O]强度，单位为dbm */
		CSTR sigStrength;
		/** WIFI名称 */
		CSTR SSID;
		/** [bool]当前有无连接热点 */
		BOOL linkEnable;
 
	} data;

} transferWifi_WifiCurrentConnectionInfoResponse;

C_API transferWifi_WifiCurrentConnectionInfoResponse *HSAPI_INIT(transferWifi_WifiCurrentConnectionInfoResponse);

#endif
