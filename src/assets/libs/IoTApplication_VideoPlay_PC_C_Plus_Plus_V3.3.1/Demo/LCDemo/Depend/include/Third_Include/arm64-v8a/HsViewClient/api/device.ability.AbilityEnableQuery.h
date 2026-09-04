/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAbility_AbilityEnableQuery_H_
#define _HSVIEW_CLIENT_API_deviceAbility_AbilityEnableQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备功能开关

------------请求参数说明------------
device:设备级使能开关
channels:通道级使能开关
channelId:[int], 通道ID
type:参考[设备使能类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2FHome.md&s=pd)
-----------------------------------


------------响应参数说明------------
device:设备级使能开关
channels:通道级使能开关
channelId:[int], 通道ID
type:参考[设备使能类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2FHome.md&s=pd)
enable: [string], on-开启 off-关闭
-----------------------------------


参考PaaS协议：[获取设备功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

协议提交：
返回结果中去除使能类型字段，客户端按照数组下标一一对应

【需要使用平台账号签名】
 */

typedef struct deviceAbility_AbilityEnableQueryRequest 
{
	HsviewRequest base;

	struct deviceAbility_AbilityEnableQueryRequestData
	{
		
		/** define a list with struct of deviceAbility_AbilityEnableQueryRequestData_DeviceElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableQueryRequestData_DeviceElement
		{
			/** 设备级能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of deviceAbility_AbilityEnableQueryRequestData_ChannelsElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableQueryRequestData_ChannelsElement
		{
			/** 通道级能力类型 */
			DECLARE_LIST(CSTR) type;
			/** [int]通道号, 《由于PaaS协议之前拼写错误，服务做兼容，channleId，channleId 2个字段都要传给设备》 */
			int channelId;
		}) channels;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceAbility_AbilityEnableQueryRequest;

C_API deviceAbility_AbilityEnableQueryRequest *HSAPI_INIT(deviceAbility_AbilityEnableQueryRequest);

typedef struct deviceAbility_AbilityEnableQueryResponse 
{
	HsviewResponse base;

	struct deviceAbility_AbilityEnableQueryResponseData
	{
		
		/** define a list with struct of deviceAbility_AbilityEnableQueryResponseData_DeviceElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableQueryResponseData_DeviceElement
		{
			/** on-开启 off-关闭 */
			CSTR enable;
			/** [O]设备级能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of deviceAbility_AbilityEnableQueryResponseData_ChannelsElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableQueryResponseData_ChannelsElement
		{
			/** define a list with struct of deviceAbility_AbilityEnableQueryResponseData_ChannelsElement_DetailElement */
			DECLARE_LIST(struct deviceAbility_AbilityEnableQueryResponseData_ChannelsElement_DetailElement
			{
				/** on-开启 off-关闭 */
				CSTR enable;
				/** [O]通道级能力类型 */
				CSTR type;
			}) detail;
			/** [int]通道号, 《由于PaaS协议之前拼写错误，服务做兼容，channleId，channleId兼容成channelId》 */
			int channelId;
		}) channels;
 
	} data;

} deviceAbility_AbilityEnableQueryResponse;

C_API deviceAbility_AbilityEnableQueryResponse *HSAPI_INIT(deviceAbility_AbilityEnableQueryResponse);

#endif
