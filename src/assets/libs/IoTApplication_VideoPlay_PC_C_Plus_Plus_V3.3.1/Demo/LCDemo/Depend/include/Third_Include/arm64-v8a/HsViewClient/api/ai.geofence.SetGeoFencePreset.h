/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiGeofence_SetGeoFencePreset_H_
#define _HSVIEW_CLIENT_API_aiGeofence_SetGeoFencePreset_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置预置点
每个预置点都有唯一id

【需要使用平台账号签名】
 */

typedef struct aiGeofence_SetGeoFencePresetRequest 
{
	HsviewRequest base;

	struct aiGeofence_SetGeoFencePresetRequestData
	{
		
		/** [bool][O]表示当前预置点的开启/关闭状态 */
		BOOL isOpen;
		/** [O]备注信息 */
		CSTR remark;
		/** 客户端生成预置点id */
		CSTR presetId;
		/** [O]预置点经度 */
		CSTR longitude;
		/** [O]预置点纬度 */
		CSTR latitude;
		/** [O]直径 */
		CSTR range;
		/** [O]预置点名称 */
		CSTR presetName;

	} data;

} aiGeofence_SetGeoFencePresetRequest;

C_API aiGeofence_SetGeoFencePresetRequest *HSAPI_INIT(aiGeofence_SetGeoFencePresetRequest);

typedef struct aiGeofence_SetGeoFencePresetResponse 
{
	HsviewResponse base;

	struct aiGeofence_SetGeoFencePresetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} aiGeofence_SetGeoFencePresetResponse;

C_API aiGeofence_SetGeoFencePresetResponse *HSAPI_INIT(aiGeofence_SetGeoFencePresetResponse);

#endif
