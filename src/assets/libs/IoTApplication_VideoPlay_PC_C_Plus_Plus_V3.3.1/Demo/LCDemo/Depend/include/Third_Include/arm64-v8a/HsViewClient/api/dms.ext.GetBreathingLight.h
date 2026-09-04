/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBreathingLight_H_
#define _HSVIEW_CLIENT_API_GetBreathingLight_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的呼吸灯状态。
【使用平台账号签名】
 */

typedef struct GetBreathingLightRequest 
{
	HsviewRequest base;

	struct GetBreathingLightRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetBreathingLightRequestData_METHOD "GET"
		/** [cstr]breathing-light */
		#define _STATIC_GetBreathingLightRequestData_CMD "breathing-light"
		/** struct of GetBreathingLightRequestData_Body */
		struct GetBreathingLightRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetBreathingLightRequest;

C_API GetBreathingLightRequest *HSAPI_INIT(GetBreathingLightRequest);

typedef struct GetBreathingLightResponse 
{
	HsviewResponse base;

	struct GetBreathingLightResponseData
	{
		
		/** 状态，on表示开启，off表示关闭 */
		CSTR Status;
 
	} data;

} GetBreathingLightResponse;

C_API GetBreathingLightResponse *HSAPI_INIT(GetBreathingLightResponse);

#endif
