/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetWifiStatus_H_
#define _HSVIEW_CLIENT_API_GetWifiStatus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备所在的WIFI环境信息

回复中是环境中所有的WIFI热点信息：

Enable表示设备是否开启WIFI。
	false：WIFI功能关闭。
	true：WIFI功能开启。

当Enable为true时同时返回设备当前环境中的热点列表：
	SSID：热点ID
	BSSID：BSS ID，通常是一个MAC地址。
	LinkStatus：0未连接，1连接中，2已连接。
	Auth：认证模式：OPEN，WEP，WPA/WPA2 PSK，WPA/WPA2
	Intensity：强度，0最弱，5最强

 */

typedef struct GetWifiStatusRequest 
{
	HsviewRequest base;

	struct GetWifiStatusRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetWifiStatusRequestData_METHOD "GET"
		/** [cstr]wifi */
		#define _STATIC_GetWifiStatusRequestData_CMD "wifi"
		/** struct of GetWifiStatusRequestData_Body */
		struct GetWifiStatusRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetWifiStatusRequest;

C_API GetWifiStatusRequest *HSAPI_INIT(GetWifiStatusRequest);

typedef struct GetWifiStatusResponse 
{
	HsviewResponse base;

	struct GetWifiStatusResponseData
	{
		
		/** [bool]是否开启了wifi */
		BOOL Enable;
		/** define a list with struct of GetWifiStatusResponseData_WLanStructElement */
		DECLARE_LIST(struct GetWifiStatusResponseData_WLanStructElement
		{
			/** [int]强度 */
			int Intensity;
			/** BSSID */
			CSTR BSSID;
			/** 加密方式 */
			CSTR Auth;
			/** SSID */
			CSTR SSID;
			/** [int]状态 */
			int LinkStatus;
		}) WLan;
 
	} data;

} GetWifiStatusResponse;

C_API GetWifiStatusResponse *HSAPI_INIT(GetWifiStatusResponse);

#endif
