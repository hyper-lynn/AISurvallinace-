/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiGeofence_GetPresetDeviceActionConfig_H_
#define _HSVIEW_CLIENT_API_aiGeofence_GetPresetDeviceActionConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取预置点联动设备行为配置信息
如果request中的presetId为空，则返回该用户的全部预置点配置信息

【需要使用平台账号签名】
 */

typedef struct aiGeofence_GetPresetDeviceActionConfigRequest 
{
	HsviewRequest base;

	struct aiGeofence_GetPresetDeviceActionConfigRequestData
	{
		
		/** [O]预置点id */
		DECLARE_LIST(CSTR) presetId;

	} data;

} aiGeofence_GetPresetDeviceActionConfigRequest;

C_API aiGeofence_GetPresetDeviceActionConfigRequest *HSAPI_INIT(aiGeofence_GetPresetDeviceActionConfigRequest);

typedef struct aiGeofence_GetPresetDeviceActionConfigResponse 
{
	HsviewResponse base;

	struct aiGeofence_GetPresetDeviceActionConfigResponseData
	{
		
		/** define a list with struct of aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement */
		DECLARE_LIST(struct aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement
		{
			/** [bool]表示当前预置点的开启/关闭状态 */
			BOOL isOpen;
			/** 该预置点最近一次执行的状态，默认为default。arrive、leave等 */
			CSTR lastAction;
			/** 直径 */
			CSTR range;
			/** 预置点id */
			CSTR presetId;
			/** [O]备注信息 */
			CSTR remark;
			/** 预置点经度 */
			CSTR longitude;
			/** 预置点纬度 */
			CSTR latitude;
			/** define a list with struct of aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement_ActionsElement */
			DECLARE_LIST(struct aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement_ActionsElement
			{
				/** 通道ID */
				CSTR channelId;
				/** define a list with struct of aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement_ActionsElement_DevActionElement */
				DECLARE_LIST(struct aiGeofence_GetPresetDeviceActionConfigResponseData_PresetInfoElement_ActionsElement_DevActionElement
				{
					/** [bool]是否有效 */
					BOOL enable;
					/** 该预置点执行的设备操作类型，arrive/leave... */
					CSTR actionType;
				}) devAction;
				/** 设备ID */
				CSTR deviceId;
			}) actions;
			/** [O]预置点名称 */
			CSTR presetName;
		}) presetInfo;
 
	} data;

} aiGeofence_GetPresetDeviceActionConfigResponse;

C_API aiGeofence_GetPresetDeviceActionConfigResponse *HSAPI_INIT(aiGeofence_GetPresetDeviceActionConfigResponse);

#endif
