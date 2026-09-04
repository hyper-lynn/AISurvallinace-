/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserAuthDevicesByPage_H_
#define _HSVIEW_CLIENT_API_GetUserAuthDevicesByPage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取设备列表
【需要使用平台账号签名】

 */

typedef struct GetUserAuthDevicesByPageRequest 
{
	HsviewRequest base;

	struct GetUserAuthDevicesByPageRequestData
	{
		
		/** 1-15 */
		CSTR need;

	} data;

} GetUserAuthDevicesByPageRequest;

C_API GetUserAuthDevicesByPageRequest *HSAPI_INIT(GetUserAuthDevicesByPageRequest);

typedef struct GetUserAuthDevicesByPageResponse 
{
	HsviewResponse base;

	struct GetUserAuthDevicesByPageResponseData
	{
		
		/** define a list with struct of GetUserAuthDevicesByPageResponseData_DevicesElement */
		DECLARE_LIST(struct GetUserAuthDevicesByPageResponseData_DevicesElement
		{
			/** [int]视频通道的总数量（包含未接入的通道） */
			int channelNum;
			/** [bool]是否在线 */
			BOOL online;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of GetUserAuthDevicesByPageResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetUserAuthDevicesByPageResponseData_DevicesElement_ChannelsElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** [long]分享的用户Id */
				DECLARE_LIST(int64) sharedUserIds;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int]剩余分享数量 */
				int leftShareCount;
			}) channels;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** 设备ID */
			CSTR deviceId;
		}) devices;
 
	} data;

} GetUserAuthDevicesByPageResponse;

C_API GetUserAuthDevicesByPageResponse *HSAPI_INIT(GetUserAuthDevicesByPageResponse);

#endif
