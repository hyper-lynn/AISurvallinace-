/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceAbilityEnableQuery_H_
#define _LC_OPENAPI_CLIENT_DeviceAbilityEnableQuery_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备功能开关
 */

typedef struct DeviceAbilityEnableQueryRequest 
{
	LCOpenApiRequest base;

	struct DeviceAbilityEnableQueryRequestData
	{
		
		/** define a list with struct of DeviceAbilityEnableQueryRequestData_DeviceElement */
		DECLARE_LIST(struct DeviceAbilityEnableQueryRequestData_DeviceElement
		{
			/** 设备级别能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of DeviceAbilityEnableQueryRequestData_ChannelsElement */
		DECLARE_LIST(struct DeviceAbilityEnableQueryRequestData_ChannelsElement
		{
			/** 设备级别能力类型 */
			DECLARE_LIST(CSTR) type;
			/** [int]通道号 */
			int channelId;
		}) channels;
		/** 授权的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceAbilityEnableQueryRequest;

C_API DeviceAbilityEnableQueryRequest *LCOPENAPI_INIT(DeviceAbilityEnableQueryRequest);

typedef struct DeviceAbilityEnableQueryResponse 
{
	LCOpenApiResponse base;

	struct DeviceAbilityEnableQueryResponseData
	{
		
		/** define a list with struct of DeviceAbilityEnableQueryResponseData_DeviceElement */
		DECLARE_LIST(struct DeviceAbilityEnableQueryResponseData_DeviceElement
		{
			/** on-开启 off-关闭 */
			CSTR enable;
			/** [O]设备级能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of DeviceAbilityEnableQueryResponseData_ChannelsElement */
		DECLARE_LIST(struct DeviceAbilityEnableQueryResponseData_ChannelsElement
		{
			/** define a list with struct of DeviceAbilityEnableQueryResponseData_ChannelsElement_DetailElement */
			DECLARE_LIST(struct DeviceAbilityEnableQueryResponseData_ChannelsElement_DetailElement
			{
				/** on-开启 off-关闭 */
				CSTR enable;
				/** [O]通道级能力类型 */
				CSTR type;
			}) detail;
			/** [int]通道号 */
			int channelId;
		}) channels;
 
	} data;

} DeviceAbilityEnableQueryResponse;

C_API DeviceAbilityEnableQueryResponse *LCOPENAPI_INIT(DeviceAbilityEnableQueryResponse);

#endif
