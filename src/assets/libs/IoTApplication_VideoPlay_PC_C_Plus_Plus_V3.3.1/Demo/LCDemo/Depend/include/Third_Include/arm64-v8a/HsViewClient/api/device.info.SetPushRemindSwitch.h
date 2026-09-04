/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceInfo_SetPushRemindSwitch_H_
#define _HSVIEW_CLIENT_API_deviceInfo_SetPushRemindSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备推送提醒开关
【需要使用平台账号签名】
 */

typedef struct deviceInfo_SetPushRemindSwitchRequest 
{
	HsviewRequest base;

	struct deviceInfo_SetPushRemindSwitchRequestData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceInfo_SetPushRemindSwitchRequest;

C_API deviceInfo_SetPushRemindSwitchRequest *HSAPI_INIT(deviceInfo_SetPushRemindSwitchRequest);

typedef struct deviceInfo_SetPushRemindSwitchResponse 
{
	HsviewResponse base;

	struct deviceInfo_SetPushRemindSwitchResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceInfo_SetPushRemindSwitchResponse;

C_API deviceInfo_SetPushRemindSwitchResponse *HSAPI_INIT(deviceInfo_SetPushRemindSwitchResponse);

#endif
