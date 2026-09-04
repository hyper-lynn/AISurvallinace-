/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDevices_H_
#define _HSVIEW_CLIENT_API_GetDevices_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个账号（AccessToken）的设备列表。
 
回复字段如下：
deviceId：设备ID
online：是否在线，true/false
deviceModel:设备型号
name：设备名称
channels：设备的视频通道数组，其中：
  id：通道号
  name：通道名称
  online：是否在线，true/false
  picurl：通道缩略图URL
  
【使用appkey/secret签名认证】
 */

typedef struct GetDevicesRequest 
{
	HsviewRequest base;

	struct GetDevicesRequestData
	{
		
		/** 需要操作的用户的AccessToken */
		CSTR accessToken;

	} data;

} GetDevicesRequest;

C_API GetDevicesRequest *HSAPI_INIT(GetDevicesRequest);

typedef struct GetDevicesResponse 
{
	HsviewResponse base;

	struct GetDevicesResponseData
	{
		
		/** define a list with struct of GetDevicesResponseData_DevicesElement */
		DECLARE_LIST(struct GetDevicesResponseData_DevicesElement
		{
			/** [bool]是否在线 */
			BOOL online;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of GetDevicesResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetDevicesResponseData_DevicesElement_ChannelsElement
			{
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备型号 */
			CSTR deviceModel;
			/** [bool]是否从别人那里分享的 */
			BOOL beSharedFrom;
			/** [bool]是否分享给别人的 */
			BOOL beSharedTo;
			/** 设备ID */
			CSTR deviceId;
		}) devices;
 
	} data;

} GetDevicesResponse;

C_API GetDevicesResponse *HSAPI_INIT(GetDevicesResponse);

#endif
