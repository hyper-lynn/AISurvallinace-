/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetDeviceSnap_H_
#define _HSVIEW_CLIENT_API_SetDeviceSnap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置摄像头抓图。
【使用平台账号签名】
 */

typedef struct SetDeviceSnapRequest 
{
	HsviewRequest base;

	struct SetDeviceSnapRequestData
	{
		
		/** [boolean]是否加密，默认不加密。[选填] */
		CSTR encrypt;
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceSnapRequest;

C_API SetDeviceSnapRequest *HSAPI_INIT(SetDeviceSnapRequest);

typedef struct SetDeviceSnapResponse 
{
	HsviewResponse base;

	struct SetDeviceSnapResponseData
	{
		
		/** 抓图访问地址 */
		CSTR url;
 
	} data;

} SetDeviceSnapResponse;

C_API SetDeviceSnapResponse *HSAPI_INIT(SetDeviceSnapResponse);

#endif
