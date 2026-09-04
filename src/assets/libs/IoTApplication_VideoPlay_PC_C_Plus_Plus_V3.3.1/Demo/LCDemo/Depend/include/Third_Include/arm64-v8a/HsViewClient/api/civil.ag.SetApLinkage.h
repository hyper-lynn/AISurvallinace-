/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetApLinkage_H_
#define _HSVIEW_CLIENT_API_SetApLinkage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件联动的设备
isPreset=1,则代表需要从设备获取当前的坐标位置

oldLinkDeviceId
oldLinkChannelId
如果这个2个字段不为空或null，则代表更新本条关联信息
【需要使用平台账号签名】
 */

typedef struct SetApLinkageRequest 
{
	HsviewRequest base;

	struct SetApLinkageRequestData
	{
		
		/** [O]要修改的关联通道id */
		CSTR oldLinkChannelId;
		/** 关联的设备id */
		CSTR linkDeviceId;
		/** 关联的设备通道id */
		CSTR linkChannelId;
		/** [int]是否采用预置点：1-使用  0-不使用 */
		int hasPreset;
		/** [O]要修改的关联设备id */
		CSTR oldLinkDeviceId;
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} SetApLinkageRequest;

C_API SetApLinkageRequest *HSAPI_INIT(SetApLinkageRequest);

typedef struct SetApLinkageResponse 
{
	HsviewResponse base;

	struct SetApLinkageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetApLinkageResponse;

C_API SetApLinkageResponse *HSAPI_INIT(SetApLinkageResponse);

#endif
