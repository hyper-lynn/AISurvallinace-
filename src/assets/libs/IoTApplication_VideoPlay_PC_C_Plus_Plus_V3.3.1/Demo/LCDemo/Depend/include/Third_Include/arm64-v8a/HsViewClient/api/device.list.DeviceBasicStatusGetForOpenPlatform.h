/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_DeviceBasicStatusGetForOpenPlatform_H_
#define _HSVIEW_CLIENT_API_deviceList_DeviceBasicStatusGetForOpenPlatform_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
通过设备序列号获取设备通道在离线状态。
注：返回请求用户有权限的设备状态（在线状态隐私级别较低）。

【使用平台账号签名】
 */

typedef struct deviceList_DeviceBasicStatusGetForOpenPlatformRequest 
{
	HsviewRequest base;

	struct deviceList_DeviceBasicStatusGetForOpenPlatformRequestData
	{
		
		/** 设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} deviceList_DeviceBasicStatusGetForOpenPlatformRequest;

C_API deviceList_DeviceBasicStatusGetForOpenPlatformRequest *HSAPI_INIT(deviceList_DeviceBasicStatusGetForOpenPlatformRequest);

typedef struct deviceList_DeviceBasicStatusGetForOpenPlatformResponse 
{
	HsviewResponse base;

	struct deviceList_DeviceBasicStatusGetForOpenPlatformResponseData
	{
		
		/** define a list with struct of deviceList_DeviceBasicStatusGetForOpenPlatformResponseData_DevicesElement */
		DECLARE_LIST(struct deviceList_DeviceBasicStatusGetForOpenPlatformResponseData_DevicesElement
		{
			/** online-在线 offline-在线 upgrading-升级中 sleep-休眠 */
			CSTR status;
			/** define a list with struct of deviceList_DeviceBasicStatusGetForOpenPlatformResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_DeviceBasicStatusGetForOpenPlatformResponseData_DevicesElement_ChannelsElement
			{
				/** 远程通道状态 online-在线 offline-在线 close-未配置 */
				CSTR status;
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;
 
	} data;

} deviceList_DeviceBasicStatusGetForOpenPlatformResponse;

C_API deviceList_DeviceBasicStatusGetForOpenPlatformResponse *HSAPI_INIT(deviceList_DeviceBasicStatusGetForOpenPlatformResponse);

#endif
