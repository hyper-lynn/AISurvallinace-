/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiOpen_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiOpen_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
打开设备WIFI

参考PaaS协议：[打开设备WIFI](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87WIFI%E4%BF%A1%E6%81%AF%2F%E6%89%93%E5%BC%80%E8%AE%BE%E5%A4%87WIFI.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiOpenRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiOpenRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/wifi/open */
		#define _STATIC_transferWifi_WifiOpenRequestData_url "/device/wifi/open"
		CSTR url;

	} data;

} transferWifi_WifiOpenRequest;

C_API transferWifi_WifiOpenRequest *HSAPI_INIT(transferWifi_WifiOpenRequest);

typedef struct transferWifi_WifiOpenResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiOpenResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferWifi_WifiOpenResponse;

C_API transferWifi_WifiOpenResponse *HSAPI_INIT(transferWifi_WifiOpenResponse);

#endif
