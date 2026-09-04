/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiCurrentInfoForRemoteDevice_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiCurrentInfoForRemoteDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取远程设备当前WIFI热点信息

参考PaaS协议：[获取远程设备当前WIFI热点信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E8%8E%B7%E5%8F%96%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E5%BD%93%E5%89%8DWIFI%E7%83%AD%E7%82%B9%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiCurrentInfoForRemoteDeviceRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiCurrentInfoForRemoteDeviceRequestData
	{
		
		/** [cstr]/device/access/device/wifi/current */
		#define _STATIC_transferWifi_WifiCurrentInfoForRemoteDeviceRequestData_url "/device/access/device/wifi/current"
		CSTR url;
		/** struct of transferWifi_WifiCurrentInfoForRemoteDeviceRequestData_Content */
		struct transferWifi_WifiCurrentInfoForRemoteDeviceRequestData_Content {
			/** [int]通道号数组 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferWifi_WifiCurrentInfoForRemoteDeviceRequest;

C_API transferWifi_WifiCurrentInfoForRemoteDeviceRequest *HSAPI_INIT(transferWifi_WifiCurrentInfoForRemoteDeviceRequest);

typedef struct transferWifi_WifiCurrentInfoForRemoteDeviceResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiCurrentInfoForRemoteDeviceResponseData
	{
		
		/** define a list with struct of transferWifi_WifiCurrentInfoForRemoteDeviceResponseData_ChannelsElement */
		DECLARE_LIST(struct transferWifi_WifiCurrentInfoForRemoteDeviceResponseData_ChannelsElement
		{
			/** [int]强度，0最弱，5最强 */
			int intensity;
			/** [O]信道，可选，大于14认为是5G频段，小于等于14是2.4G频段 */
			CSTR channel;
			/** [O]强度，单位为dbm */
			CSTR sigStrength;
			/** [int]通道号 */
			int channelId;
			/** WIFI名称 */
			CSTR SSID;
			/** [bool]当前有无连接热点 */
			BOOL linkEnable;
		}) channels;
 
	} data;

} transferWifi_WifiCurrentInfoForRemoteDeviceResponse;

C_API transferWifi_WifiCurrentInfoForRemoteDeviceResponse *HSAPI_INIT(transferWifi_WifiCurrentInfoForRemoteDeviceResponse);

#endif
