/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkagesDel_H_
#define _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkagesDel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除设备联动的设备的联动规则

linkages不能为空。
【需要使用平台账号签名】
 */

typedef struct deviceLinkage_DeviceLinkagesDelRequest 
{
	HsviewRequest base;

	struct deviceLinkage_DeviceLinkagesDelRequestData
	{
		
		/** [O] 设备通道号 为空或者不存在 代表设备级 */
		CSTR channelId;
		/** define a list with struct of deviceLinkage_DeviceLinkagesDelRequestData_LinkagesElement */
		DECLARE_LIST(struct deviceLinkage_DeviceLinkagesDelRequestData_LinkagesElement
		{
			/** 联动设备通道号 */
			CSTR linkChannelId;
			/** 联动的设备id */
			CSTR linkDeviceId;
		}) linkages;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceLinkage_DeviceLinkagesDelRequest;

C_API deviceLinkage_DeviceLinkagesDelRequest *HSAPI_INIT(deviceLinkage_DeviceLinkagesDelRequest);

typedef struct deviceLinkage_DeviceLinkagesDelResponse 
{
	HsviewResponse base;

	struct deviceLinkage_DeviceLinkagesDelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceLinkage_DeviceLinkagesDelResponse;

C_API deviceLinkage_DeviceLinkagesDelResponse *HSAPI_INIT(deviceLinkage_DeviceLinkagesDelResponse);

#endif
