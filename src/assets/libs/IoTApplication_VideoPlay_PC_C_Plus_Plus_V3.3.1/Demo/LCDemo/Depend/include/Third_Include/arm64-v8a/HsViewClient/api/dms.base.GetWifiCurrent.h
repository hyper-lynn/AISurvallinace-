/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetWifiCurrent_H_
#define _HSVIEW_CLIENT_API_GetWifiCurrent_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备当前连接的WIFI热点的信息。
【使用平台账号认证】
 */

typedef struct GetWifiCurrentRequest 
{
	HsviewRequest base;

	struct GetWifiCurrentRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetWifiCurrentRequestData_METHOD "GET"
		/** [cstr]wifi-current */
		#define _STATIC_GetWifiCurrentRequestData_CMD "wifi-current"
		/** struct of GetWifiCurrentRequestData_Body */
		struct GetWifiCurrentRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetWifiCurrentRequest;

C_API GetWifiCurrentRequest *HSAPI_INIT(GetWifiCurrentRequest);

typedef struct GetWifiCurrentResponse 
{
	HsviewResponse base;

	struct GetWifiCurrentResponseData
	{
		
		/** 若连接了热点，填热点的名称；若未连接，填空。 */
		CSTR SSID;
		/** [bool]是否连接了wifi */
		BOOL LinkEnable;
 
	} data;

} GetWifiCurrentResponse;

C_API GetWifiCurrentResponse *HSAPI_INIT(GetWifiCurrentResponse);

#endif
