/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_SetApLinkage_H_
#define _HSVIEW_CLIENT_API_agOperate_SetApLinkage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件联动的设备
isPreset=1,则代表需要从设备获取当前的坐标位置

平台上若已经存在linkDeviceId和linkChannelId关联关系，代表重新更新关联信息，可能PTZ会发生变化，需要重新获取并更新。
【需要使用平台账号签名】
 */

typedef struct agOperate_SetApLinkageRequest 
{
	HsviewRequest base;

	struct agOperate_SetApLinkageRequestData
	{
		
		/** 关联的设备id */
		CSTR linkDeviceId;
		/** [int]是否采用摄像机云台位置：1-使用  0-不使用 */
		int hasPreset;
		/** 关联的设备通道id */
		CSTR linkChannelId;
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_SetApLinkageRequest;

C_API agOperate_SetApLinkageRequest *HSAPI_INIT(agOperate_SetApLinkageRequest);

typedef struct agOperate_SetApLinkageResponse 
{
	HsviewResponse base;

	struct agOperate_SetApLinkageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_SetApLinkageResponse;

C_API agOperate_SetApLinkageResponse *HSAPI_INIT(agOperate_SetApLinkageResponse);

#endif
