/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetBreathingLight_H_
#define _HSVIEW_CLIENT_API_SetBreathingLight_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的呼吸灯状态。
【使用平台账号签名】
 */

typedef struct SetBreathingLightRequest 
{
	HsviewRequest base;

	struct SetBreathingLightRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetBreathingLightRequestData_METHOD "POST"
		/** [cstr]breathing-light */
		#define _STATIC_SetBreathingLightRequestData_CMD "breathing-light"
		/** struct of SetBreathingLightRequestData_Body */
		struct SetBreathingLightRequestData_Body {
			/** 状态，on表示开启，off表示关闭 */
			CSTR Status;
		} body;

	} data;

} SetBreathingLightRequest;

C_API SetBreathingLightRequest *HSAPI_INIT(SetBreathingLightRequest);

typedef struct SetBreathingLightResponse 
{
	HsviewResponse base;

	struct SetBreathingLightResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetBreathingLightResponse;

C_API SetBreathingLightResponse *HSAPI_INIT(SetBreathingLightResponse);

#endif
