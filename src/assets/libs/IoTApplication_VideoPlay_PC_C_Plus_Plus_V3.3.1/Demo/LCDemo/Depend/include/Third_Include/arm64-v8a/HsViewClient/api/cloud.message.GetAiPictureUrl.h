/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetAiPictureUrl_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetAiPictureUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
智能报警配置展示
paas协议地址：http://paas.dahuatech.com/wiki/?p=%2FSaaStoPaaS%2F%E5%91%8A%E8%AD%A6%E6%9F%A5%E8%AF%A2%2Fcloud.message.GetAiPictureUrl&s=pj
【使用平台账号签名】
 */

typedef struct cloudMessage_GetAiPictureUrlRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetAiPictureUrlRequestData
	{
		
		/** define a list with struct of cloudMessage_GetAiPictureUrlRequestData_DeviceListElement */
		DECLARE_LIST(struct cloudMessage_GetAiPictureUrlRequestData_DeviceListElement
		{
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;

	} data;

} cloudMessage_GetAiPictureUrlRequest;

C_API cloudMessage_GetAiPictureUrlRequest *HSAPI_INIT(cloudMessage_GetAiPictureUrlRequest);

typedef struct cloudMessage_GetAiPictureUrlResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetAiPictureUrlResponseData
	{
		
		/** define a list with struct of cloudMessage_GetAiPictureUrlResponseData_PicListElement */
		DECLARE_LIST(struct cloudMessage_GetAiPictureUrlResponseData_PicListElement
		{
			/** 授权的图片地址 */
			CSTR picUrl;
			/** 设备序列号 */
			CSTR deviceId;
		}) picList;
 
	} data;

} cloudMessage_GetAiPictureUrlResponse;

C_API cloudMessage_GetAiPictureUrlResponse *HSAPI_INIT(cloudMessage_GetAiPictureUrlResponse);

#endif
