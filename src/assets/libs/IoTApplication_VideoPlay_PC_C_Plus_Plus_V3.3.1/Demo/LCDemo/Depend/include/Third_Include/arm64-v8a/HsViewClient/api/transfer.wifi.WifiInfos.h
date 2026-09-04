/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiInfos_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiInfos_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取可连接WIFI热点信息

参考PaaS协议：[获取可连接WIFI热点信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E8%8E%B7%E5%8F%96%E5%8F%AF%E8%BF%9E%E6%8E%A5WIFI%E7%83%AD%E7%82%B9%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiInfosRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiInfosRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/wifi/info */
		#define _STATIC_transferWifi_WifiInfosRequestData_url "/device/wifi/info"
		CSTR url;

	} data;

} transferWifi_WifiInfosRequest;

C_API transferWifi_WifiInfosRequest *HSAPI_INIT(transferWifi_WifiInfosRequest);

typedef struct transferWifi_WifiInfosResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiInfosResponseData
	{
		
		/** 设备是否开启WIFI。true:开启，false:关闭 */
		CSTR enable;
		/** define a list with struct of transferWifi_WifiInfosResponseData_InfosElement */
		DECLARE_LIST(struct transferWifi_WifiInfosResponseData_InfosElement
		{
			/** [int]强度，0最弱，5最强 */
			int intensity;
			/** 连接状态。unconnected：未连接；connecting：连接中；connected：已连接 */
			CSTR status;
			/** 该WIFI的唯一标示符，通常是一个MAC地址 */
			CSTR BSSID;
			/** WIFI名称，如TP-link */
			CSTR SSID;
			/** WIFI认证模式 */
			CSTR auth;
		}) infos;
 
	} data;

} transferWifi_WifiInfosResponse;

C_API transferWifi_WifiInfosResponse *HSAPI_INIT(transferWifi_WifiInfosResponse);

#endif
