/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_ChannelPicModify_H_
#define _HSVIEW_CLIENT_API_deviceManager_ChannelPicModify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改设备通道封面
【需要使用平台账号签名】
 */

typedef struct deviceManager_ChannelPicModifyRequest 
{
	HsviewRequest base;

	struct deviceManager_ChannelPicModifyRequestData
	{
		
		/** [O]通道封面类型，auto--自动抓图,custom--用户自定义图片 */
		CSTR picType;
		/** 通道号 */
		CSTR channelId;
		/** [O]图片二进制数据的base64编码字符串 */
		CSTR pictureData;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceManager_ChannelPicModifyRequest;

C_API deviceManager_ChannelPicModifyRequest *HSAPI_INIT(deviceManager_ChannelPicModifyRequest);

typedef struct deviceManager_ChannelPicModifyResponse 
{
	HsviewResponse base;

	struct deviceManager_ChannelPicModifyResponseData
	{
		
		/** 封面图片Url */
		CSTR picUrl;
 
	} data;

} deviceManager_ChannelPicModifyResponse;

C_API deviceManager_ChannelPicModifyResponse *HSAPI_INIT(deviceManager_ChannelPicModifyResponse);

#endif
