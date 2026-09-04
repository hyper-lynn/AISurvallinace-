/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiGeofence_ImplementPresetAction_H_
#define _HSVIEW_CLIENT_API_aiGeofence_ImplementPresetAction_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
执行该预置点的行为

【需要使用平台账号签名】
 */

typedef struct aiGeofence_ImplementPresetActionRequest 
{
	HsviewRequest base;

	struct aiGeofence_ImplementPresetActionRequestData
	{
		
		/** define a list with struct of aiGeofence_ImplementPresetActionRequestData_PresetActionElement */
		DECLARE_LIST(struct aiGeofence_ImplementPresetActionRequestData_PresetActionElement
		{
			/** 预置点id */
			CSTR presetId;
			/** 该预置点执行的设备操作类型，arrive/leave... */
			CSTR actionType;
		}) presetAction;

	} data;

} aiGeofence_ImplementPresetActionRequest;

C_API aiGeofence_ImplementPresetActionRequest *HSAPI_INIT(aiGeofence_ImplementPresetActionRequest);

typedef struct aiGeofence_ImplementPresetActionResponse 
{
	HsviewResponse base;

	struct aiGeofence_ImplementPresetActionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} aiGeofence_ImplementPresetActionResponse;

C_API aiGeofence_ImplementPresetActionResponse *HSAPI_INIT(aiGeofence_ImplementPresetActionResponse);

#endif
