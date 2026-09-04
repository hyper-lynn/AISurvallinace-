/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceInfo_GetPushRemindSwitch_H_
#define _HSVIEW_CLIENT_API_deviceInfo_GetPushRemindSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备推送提醒开关
【需要使用平台账号签名】
 */

typedef struct deviceInfo_GetPushRemindSwitchRequest 
{
	HsviewRequest base;

	struct deviceInfo_GetPushRemindSwitchRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceInfo_GetPushRemindSwitchRequest;

C_API deviceInfo_GetPushRemindSwitchRequest *HSAPI_INIT(deviceInfo_GetPushRemindSwitchRequest);

typedef struct deviceInfo_GetPushRemindSwitchResponse 
{
	HsviewResponse base;

	struct deviceInfo_GetPushRemindSwitchResponseData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
 
	} data;

} deviceInfo_GetPushRemindSwitchResponse;

C_API deviceInfo_GetPushRemindSwitchResponse *HSAPI_INIT(deviceInfo_GetPushRemindSwitchResponse);

#endif
