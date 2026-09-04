/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_NotifySnapPicture_H_
#define _HSVIEW_CLIENT_API_deviceManager_NotifySnapPicture_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
手动抓图协议

开放平台手动抓图，响应中需要返回相应的已经授权的图片地址，开发者会在一段时间后拿着这个地址来下载图片。
【需要使用平台账号签名】
 */

typedef struct deviceManager_NotifySnapPictureRequest 
{
	HsviewRequest base;

	struct deviceManager_NotifySnapPictureRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 1 普通设备抓图 2 抓图设置通道封面图 */
		CSTR type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceManager_NotifySnapPictureRequest;

C_API deviceManager_NotifySnapPictureRequest *HSAPI_INIT(deviceManager_NotifySnapPictureRequest);

typedef struct deviceManager_NotifySnapPictureResponse 
{
	HsviewResponse base;

	struct deviceManager_NotifySnapPictureResponseData
	{
		
		/** [O]可选 抓图标示符 */
		CSTR token;
		/** [O]可选 封面图片Url */
		CSTR pictureAddr;
 
	} data;

} deviceManager_NotifySnapPictureResponse;

C_API deviceManager_NotifySnapPictureResponse *HSAPI_INIT(deviceManager_NotifySnapPictureResponse);

#endif
