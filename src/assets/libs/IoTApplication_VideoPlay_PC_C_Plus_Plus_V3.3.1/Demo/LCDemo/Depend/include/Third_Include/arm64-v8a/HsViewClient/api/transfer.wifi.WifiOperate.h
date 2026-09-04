/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiOperate_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiOperate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
操作设备WIFI

参考PaaS协议：[操作设备WIFI](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E6%93%8D%E4%BD%9C%E8%AE%BE%E5%A4%87WIFI.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiOperateRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiOperateRequestData
	{
		
		/** [cstr]/device/wifi/operate */
		#define _STATIC_transferWifi_WifiOperateRequestData_url "/device/wifi/operate"
		CSTR url;
		/** struct of transferWifi_WifiOperateRequestData_Content */
		struct transferWifi_WifiOperateRequestData_Content {
			/** 该WIFI的唯一标示符，通常是一个MAC地址 */
			CSTR BSSID;
			/** 连接密码。若该热点是OPEN的，password为空 */
			CSTR password;
			/** WIFI名称，如TP-LINK */
			CSTR SSID;
			/** 表示连接或断开该热点，connect：连接热点，disconnect：断开热点 */
			CSTR link;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferWifi_WifiOperateRequest;

C_API transferWifi_WifiOperateRequest *HSAPI_INIT(transferWifi_WifiOperateRequest);

typedef struct transferWifi_WifiOperateResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiOperateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferWifi_WifiOperateResponse;

C_API transferWifi_WifiOperateResponse *HSAPI_INIT(transferWifi_WifiOperateResponse);

#endif
