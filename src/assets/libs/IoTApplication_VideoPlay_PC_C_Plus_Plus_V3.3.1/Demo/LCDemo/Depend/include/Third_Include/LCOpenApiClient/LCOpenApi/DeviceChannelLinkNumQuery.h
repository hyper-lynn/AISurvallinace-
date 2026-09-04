/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceChannelLinkNumQuery_H_
#define _LC_OPENAPI_CLIENT_DeviceChannelLinkNumQuery_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备通道关联的配件数量
 */

typedef struct DeviceChannelLinkNumQueryRequest 
{
	LCOpenApiRequest base;

	struct DeviceChannelLinkNumQueryRequestData
	{
		
		/** 授权的token */
		CSTR token;

	} data;

} DeviceChannelLinkNumQueryRequest;

C_API DeviceChannelLinkNumQueryRequest *LCOPENAPI_INIT(DeviceChannelLinkNumQueryRequest);

typedef struct DeviceChannelLinkNumQueryResponse 
{
	LCOpenApiResponse base;

	struct DeviceChannelLinkNumQueryResponseData
	{
		
		/** define a list with struct of DeviceChannelLinkNumQueryResponseData_LinkagesElement */
		DECLARE_LIST(struct DeviceChannelLinkNumQueryResponseData_LinkagesElement
		{
			/** [int]单个设备通道关联配件的最大限制数 */
			int maxNum;
			/** 关联的设备通道id */
			CSTR channelId;
			/** [int]通道已经关联的配件数量 */
			int num;
			/** 关联的设备id */
			CSTR deviceId;
		}) linkages;
 
	} data;

} DeviceChannelLinkNumQueryResponse;

C_API DeviceChannelLinkNumQueryResponse *LCOPENAPI_INIT(DeviceChannelLinkNumQueryResponse);

#endif
