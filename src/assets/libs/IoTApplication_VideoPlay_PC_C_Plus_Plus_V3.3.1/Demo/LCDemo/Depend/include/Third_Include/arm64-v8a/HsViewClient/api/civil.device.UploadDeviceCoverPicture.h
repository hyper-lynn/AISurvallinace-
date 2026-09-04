/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UploadDeviceCoverPicture_H_
#define _HSVIEW_CLIENT_API_UploadDeviceCoverPicture_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备视频封面。
要求使用jpeg图片，4:3格式，大小控制在200KB以下。
【需要使用平台账号签名】
 */

typedef struct UploadDeviceCoverPictureRequest 
{
	HsviewRequest base;

	struct UploadDeviceCoverPictureRequestData
	{
		
		/** 图片类型，填jpeg */
		CSTR pictureType;
		/** 通道号，留空表示设置设备 */
		CSTR channelId;
		/** 图片二进制数据的base64编码字符串 */
		CSTR pictureData;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UploadDeviceCoverPictureRequest;

C_API UploadDeviceCoverPictureRequest *HSAPI_INIT(UploadDeviceCoverPictureRequest);

typedef struct UploadDeviceCoverPictureResponse 
{
	HsviewResponse base;

	struct UploadDeviceCoverPictureResponseData
	{
		
		/** 封面图片Url */
		CSTR picUrl;
 
	} data;

} UploadDeviceCoverPictureResponse;

C_API UploadDeviceCoverPictureResponse *HSAPI_INIT(UploadDeviceCoverPictureResponse);

#endif
