/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkageSet_H_
#define _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkageSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备联动的设备
hasPreset=1,则代表需要从设备获取当前的坐标位置

平台上若已经存在linkDeviceId和linkChannelId关联关系，代表重新更新关联信息，可能PTZ会发生变化，需要重新获取并更新。
【需要使用平台账号签名】
 */

typedef struct deviceLinkage_DeviceLinkageSetRequest 
{
	HsviewRequest base;

	struct deviceLinkage_DeviceLinkageSetRequestData
	{
		
		/** 关联的设备id */
		CSTR linkDeviceId;
		/** [int]是否采用摄像机云台位置：1-使用  0-不使用 */
		int hasPreset;
		/** [O]设备通道号  为空或者不存在 代表是设备级 */
		CSTR channelId;
		/** 关联的设备通道id */
		CSTR linkChannelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceLinkage_DeviceLinkageSetRequest;

C_API deviceLinkage_DeviceLinkageSetRequest *HSAPI_INIT(deviceLinkage_DeviceLinkageSetRequest);

typedef struct deviceLinkage_DeviceLinkageSetResponse 
{
	HsviewResponse base;

	struct deviceLinkage_DeviceLinkageSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceLinkage_DeviceLinkageSetResponse;

C_API deviceLinkage_DeviceLinkageSetResponse *HSAPI_INIT(deviceLinkage_DeviceLinkageSetResponse);

#endif
