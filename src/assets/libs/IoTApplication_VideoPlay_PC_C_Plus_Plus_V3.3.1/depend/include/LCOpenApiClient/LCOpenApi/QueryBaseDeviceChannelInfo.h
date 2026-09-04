/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryBaseDeviceChannelInfo_H_
#define _LC_OPENAPI_CLIENT_QueryBaseDeviceChannelInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据设备序列号集合获取开放平台添加设备的通道基本信息

 */

typedef struct QueryBaseDeviceChannelInfoRequest 
{
	LCOpenApiRequest base;

	struct QueryBaseDeviceChannelInfoRequestData
	{
		
		/** [cstr]queryOpenDeviceChannelInfo */
		#define _STATIC_QueryBaseDeviceChannelInfoRequestData_method "queryOpenDeviceChannelInfo"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryBaseDeviceChannelInfoRequest;

C_API QueryBaseDeviceChannelInfoRequest *LCOPENAPI_INIT(QueryBaseDeviceChannelInfoRequest);

typedef struct QueryBaseDeviceChannelInfoResponse 
{
	LCOpenApiResponse base;

	struct QueryBaseDeviceChannelInfoResponseData
	{
		
		/** define a list with struct of QueryBaseDeviceChannelInfoResponseData_DevicesElement */
		DECLARE_LIST(struct QueryBaseDeviceChannelInfoResponseData_DevicesElement
		{
			/** 设备状态 online-在线 offline-离线 close-未配置 sleep-休眠 */
			CSTR status;
			/** define a list with struct of QueryBaseDeviceChannelInfoResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct QueryBaseDeviceChannelInfoResponseData_DevicesElement_ChannelsElement
			{
				/** 远程通道状态 online-在线 offline-离线 close-未配置 sleep-休眠 */
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

} QueryBaseDeviceChannelInfoResponse;

C_API QueryBaseDeviceChannelInfoResponse *LCOPENAPI_INIT(QueryBaseDeviceChannelInfoResponse);

#endif
