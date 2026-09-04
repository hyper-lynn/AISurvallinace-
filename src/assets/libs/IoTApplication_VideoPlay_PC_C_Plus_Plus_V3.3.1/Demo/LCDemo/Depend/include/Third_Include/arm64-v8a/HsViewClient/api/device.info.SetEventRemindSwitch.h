/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceInfo_SetEventRemindSwitch_H_
#define _HSVIEW_CLIENT_API_deviceInfo_SetEventRemindSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备事件提醒开关，适用于海外

【需要使用平台账号签名】
 */

typedef struct deviceInfo_SetEventRemindSwitchRequest 
{
	HsviewRequest base;

	struct deviceInfo_SetEventRemindSwitchRequestData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
		/** 事件提醒开关类型：callEvent呼叫事件,offlineEvent离线事件 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceInfo_SetEventRemindSwitchRequest;

C_API deviceInfo_SetEventRemindSwitchRequest *HSAPI_INIT(deviceInfo_SetEventRemindSwitchRequest);

typedef struct deviceInfo_SetEventRemindSwitchResponse 
{
	HsviewResponse base;

	struct deviceInfo_SetEventRemindSwitchResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceInfo_SetEventRemindSwitchResponse;

C_API deviceInfo_SetEventRemindSwitchResponse *HSAPI_INIT(deviceInfo_SetEventRemindSwitchResponse);

#endif
