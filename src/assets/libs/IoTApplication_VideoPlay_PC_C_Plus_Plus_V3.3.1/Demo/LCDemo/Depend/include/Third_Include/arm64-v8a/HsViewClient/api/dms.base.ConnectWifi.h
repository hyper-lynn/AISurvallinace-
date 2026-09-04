/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ConnectWifi_H_
#define _HSVIEW_CLIENT_API_ConnectWifi_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
连接某个热点，设置WIFI密码
设置指定[SSID]的配置。
	BSSID：填写BSSID的目的是防止重名SSID
	Enable表示连接或断开该热点
	Password表示连接密码。若该热点是OPEN的，Password为空。
返回的Status有以下几种：“Success”成功，“Timeout”超时，“AuthFail”密码错误。
 */

typedef struct ConnectWifiRequest 
{
	HsviewRequest base;

	struct ConnectWifiRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填需要连接的SSID */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_ConnectWifiRequestData_METHOD "POST"
		/** [cstr]wifi */
		#define _STATIC_ConnectWifiRequestData_CMD "wifi"
		/** struct of ConnectWifiRequestData_Body */
		struct ConnectWifiRequestData_Body {
			/** BSSID */
			CSTR BSSID;
			/** wifi密码 */
			CSTR Password;
			/** [bool]连接或断开 */
			BOOL LinkEnable;
		} body;

	} data;

} ConnectWifiRequest;

C_API ConnectWifiRequest *HSAPI_INIT(ConnectWifiRequest);

typedef struct ConnectWifiResponse 
{
	HsviewResponse base;

	struct ConnectWifiResponseData
	{
		
		/** 成功或错误字串 */
		CSTR Status;
 
	} data;

} ConnectWifiResponse;

C_API ConnectWifiResponse *HSAPI_INIT(ConnectWifiResponse);

#endif
