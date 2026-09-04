/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiClose_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiClose_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
关闭设备WIFI

参考PaaS协议：[关闭设备WIFI](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E5%85%B3%E9%97%AD%E8%AE%BE%E5%A4%87WIFI.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiCloseRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiCloseRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/wifi/close */
		#define _STATIC_transferWifi_WifiCloseRequestData_url "/device/wifi/close"
		CSTR url;

	} data;

} transferWifi_WifiCloseRequest;

C_API transferWifi_WifiCloseRequest *HSAPI_INIT(transferWifi_WifiCloseRequest);

typedef struct transferWifi_WifiCloseResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiCloseResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferWifi_WifiCloseResponse;

C_API transferWifi_WifiCloseResponse *HSAPI_INIT(transferWifi_WifiCloseResponse);

#endif
