/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkagesGet_H_
#define _HSVIEW_CLIENT_API_deviceLinkage_DeviceLinkagesGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的联动列表

【需要使用平台账号签名】
 */

typedef struct deviceLinkage_DeviceLinkagesGetRequest 
{
	HsviewRequest base;

	struct deviceLinkage_DeviceLinkagesGetRequestData
	{
		
		/** [O]设备通道号  为空或者不存在 代表是设备级 */
		CSTR channelId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} deviceLinkage_DeviceLinkagesGetRequest;

C_API deviceLinkage_DeviceLinkagesGetRequest *HSAPI_INIT(deviceLinkage_DeviceLinkagesGetRequest);

typedef struct deviceLinkage_DeviceLinkagesGetResponse 
{
	HsviewResponse base;

	struct deviceLinkage_DeviceLinkagesGetResponseData
	{
		
		/** define a list with struct of deviceLinkage_DeviceLinkagesGetResponseData_LinkagesElement */
		DECLARE_LIST(struct deviceLinkage_DeviceLinkagesGetResponseData_LinkagesElement
		{
			/** 关联的设备id */
			CSTR linkDeviceId;
			/** [int]是否设置过摄像机云台位置，0-否，1-是 */
			int hasPreset;
			/** 关联的设备通道id */
			CSTR linkChannelId;
		}) linkages;
 
	} data;

} deviceLinkage_DeviceLinkagesGetResponse;

C_API deviceLinkage_DeviceLinkagesGetResponse *HSAPI_INIT(deviceLinkage_DeviceLinkagesGetResponse);

#endif
