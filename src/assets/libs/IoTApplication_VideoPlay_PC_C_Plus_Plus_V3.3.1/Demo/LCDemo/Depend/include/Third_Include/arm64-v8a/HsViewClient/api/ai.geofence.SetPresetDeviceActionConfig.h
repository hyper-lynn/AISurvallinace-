/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiGeofence_SetPresetDeviceActionConfig_H_
#define _HSVIEW_CLIENT_API_aiGeofence_SetPresetDeviceActionConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置预置点联动设备行为配置信息
actionType的内容可以是客户端自定义，平台不关注

【需要使用平台账号签名】
 */

typedef struct aiGeofence_SetPresetDeviceActionConfigRequest 
{
	HsviewRequest base;

	struct aiGeofence_SetPresetDeviceActionConfigRequestData
	{
		
		/** 预置点id */
		CSTR presetId;
		/** define a list with struct of aiGeofence_SetPresetDeviceActionConfigRequestData_ActionsElement */
		DECLARE_LIST(struct aiGeofence_SetPresetDeviceActionConfigRequestData_ActionsElement
		{
			/** 通道ID */
			CSTR channelId;
			/** define a list with struct of aiGeofence_SetPresetDeviceActionConfigRequestData_ActionsElement_DevActionElement */
			DECLARE_LIST(struct aiGeofence_SetPresetDeviceActionConfigRequestData_ActionsElement_DevActionElement
			{
				/** [bool]是否有效 */
				BOOL enable;
				/** 该预置点执行的设备操作类型，arrive/leave... */
				CSTR actionType;
			}) devAction;
			/** 设备ID */
			CSTR deviceId;
		}) actions;

	} data;

} aiGeofence_SetPresetDeviceActionConfigRequest;

C_API aiGeofence_SetPresetDeviceActionConfigRequest *HSAPI_INIT(aiGeofence_SetPresetDeviceActionConfigRequest);

typedef struct aiGeofence_SetPresetDeviceActionConfigResponse 
{
	HsviewResponse base;

	struct aiGeofence_SetPresetDeviceActionConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} aiGeofence_SetPresetDeviceActionConfigResponse;

C_API aiGeofence_SetPresetDeviceActionConfigResponse *HSAPI_INIT(aiGeofence_SetPresetDeviceActionConfigResponse);

#endif
