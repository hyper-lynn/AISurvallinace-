/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DisableWifi_H_
#define _HSVIEW_CLIENT_API_DisableWifi_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
关闭设备WIFI
 */

typedef struct DisableWifiRequest 
{
	HsviewRequest base;

	struct DisableWifiRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_DisableWifiRequestData_METHOD "POST"
		/** [cstr]wifi-off */
		#define _STATIC_DisableWifiRequestData_CMD "wifi-off"
		/** struct of DisableWifiRequestData_Body */
		struct DisableWifiRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} DisableWifiRequest;

C_API DisableWifiRequest *HSAPI_INIT(DisableWifiRequest);

typedef struct DisableWifiResponse 
{
	HsviewResponse base;

	struct DisableWifiResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DisableWifiResponse;

C_API DisableWifiResponse *HSAPI_INIT(DisableWifiResponse);

#endif
