/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceAbilityEnableConfig_H_
#define _LC_OPENAPI_CLIENT_DeviceAbilityEnableConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备功能开关
 */

typedef struct DeviceAbilityEnableConfigRequest 
{
	LCOpenApiRequest base;

	struct DeviceAbilityEnableConfigRequestData
	{
		
		/** define a list with struct of DeviceAbilityEnableConfigRequestData_DeviceElement */
		DECLARE_LIST(struct DeviceAbilityEnableConfigRequestData_DeviceElement
		{
			/** on-开启 off-关闭 */
			CSTR enable;
			/** [O]通道级能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of DeviceAbilityEnableConfigRequestData_ChannelsElement */
		DECLARE_LIST(struct DeviceAbilityEnableConfigRequestData_ChannelsElement
		{
			/** define a list with struct of DeviceAbilityEnableConfigRequestData_ChannelsElement_DetailElement */
			DECLARE_LIST(struct DeviceAbilityEnableConfigRequestData_ChannelsElement_DetailElement
			{
				/** on-开启 off-关闭 */
				CSTR enable;
				/** [O]通道级能力类型 */
				CSTR type;
			}) detail;
			/** [int]通道号 */
			int channelId;
		}) channels;
		/** 授权的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceAbilityEnableConfigRequest;

C_API DeviceAbilityEnableConfigRequest *LCOPENAPI_INIT(DeviceAbilityEnableConfigRequest);

typedef struct DeviceAbilityEnableConfigResponse 
{
	LCOpenApiResponse base;

	struct DeviceAbilityEnableConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeviceAbilityEnableConfigResponse;

C_API DeviceAbilityEnableConfigResponse *LCOPENAPI_INIT(DeviceAbilityEnableConfigResponse);

#endif
