/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_EnableWifi_H_
#define _HSVIEW_CLIENT_API_EnableWifi_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
打开设备WIFI
 */

typedef struct EnableWifiRequest 
{
	HsviewRequest base;

	struct EnableWifiRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_EnableWifiRequestData_METHOD "POST"
		/** [cstr]wifi-on */
		#define _STATIC_EnableWifiRequestData_CMD "wifi-on"
		/** struct of EnableWifiRequestData_Body */
		struct EnableWifiRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} EnableWifiRequest;

C_API EnableWifiRequest *HSAPI_INIT(EnableWifiRequest);

typedef struct EnableWifiResponse 
{
	HsviewResponse base;

	struct EnableWifiResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} EnableWifiResponse;

C_API EnableWifiResponse *HSAPI_INIT(EnableWifiResponse);

#endif
