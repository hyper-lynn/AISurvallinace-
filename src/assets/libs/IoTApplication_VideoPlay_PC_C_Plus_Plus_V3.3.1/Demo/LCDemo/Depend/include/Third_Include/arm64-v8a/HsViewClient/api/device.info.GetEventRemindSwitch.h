/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceInfo_GetEventRemindSwitch_H_
#define _HSVIEW_CLIENT_API_deviceInfo_GetEventRemindSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备事件提醒开关，适用于海外

【需要使用平台账号签名】
 */

typedef struct deviceInfo_GetEventRemindSwitchRequest 
{
	HsviewRequest base;

	struct deviceInfo_GetEventRemindSwitchRequestData
	{
		
		/** 事件提醒开关类型：callEvent呼叫事件,offlineEvent离线事件 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceInfo_GetEventRemindSwitchRequest;

C_API deviceInfo_GetEventRemindSwitchRequest *HSAPI_INIT(deviceInfo_GetEventRemindSwitchRequest);

typedef struct deviceInfo_GetEventRemindSwitchResponse 
{
	HsviewResponse base;

	struct deviceInfo_GetEventRemindSwitchResponseData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
 
	} data;

} deviceInfo_GetEventRemindSwitchResponse;

C_API deviceInfo_GetEventRemindSwitchResponse *HSAPI_INIT(deviceInfo_GetEventRemindSwitchResponse);

#endif
