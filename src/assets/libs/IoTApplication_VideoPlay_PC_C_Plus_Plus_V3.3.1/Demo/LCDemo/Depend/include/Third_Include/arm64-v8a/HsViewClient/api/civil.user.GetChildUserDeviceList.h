/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChildUserDeviceList_H_
#define _HSVIEW_CLIENT_API_GetChildUserDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取子账号的设备列表。
请求消息体JSON的project体现项目，如果为乐橙小微必填LeChange-Pro:乐橙小微。
【使用平台账号签名认证】
 */

typedef struct GetChildUserDeviceListRequest 
{
	HsviewRequest base;

	struct GetChildUserDeviceListRequestData
	{
		
		/** 子账号用户名 */
		CSTR childUsername;

	} data;

} GetChildUserDeviceListRequest;

C_API GetChildUserDeviceListRequest *HSAPI_INIT(GetChildUserDeviceListRequest);

typedef struct GetChildUserDeviceListResponse 
{
	HsviewResponse base;

	struct GetChildUserDeviceListResponseData
	{
		
		/** define a list with struct of GetChildUserDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetChildUserDeviceListResponseData_DevicesElement
		{
			/** define a list with struct of GetChildUserDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetChildUserDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** 通道缩略图URL */
				CSTR thumbUrl;
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
				/** 该子账号可用功能，有：videoMonitor configure alarmMsg videoRecord，每个功能用逗号隔开 */
				CSTR functions;
			}) channels;
			/** 设备ID */
			CSTR deviceId;
		}) devices;
 
	} data;

} GetChildUserDeviceListResponse;

C_API GetChildUserDeviceListResponse *HSAPI_INIT(GetChildUserDeviceListResponse);

#endif
