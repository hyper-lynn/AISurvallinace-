/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAbility_AbilityEnableConfig_H_
#define _HSVIEW_CLIENT_API_deviceAbility_AbilityEnableConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备功能开关


------------请求参数说明------------
device:设备级使能开关
channels:通道级使能开关
channelId:[int], 通道ID
type:参考[设备使能类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2FHome.md&s=pd)
enable: [string], on-开启 off-关闭
-----------------------------------

参考PaaS协议：[设置设备功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct deviceAbility_AbilityEnableConfigRequest 
{
	HsviewRequest base;

	struct deviceAbility_AbilityEnableConfigRequestData
	{
		
		/** define a list with struct of deviceAbility_AbilityEnableConfigRequestData_DeviceElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableConfigRequestData_DeviceElement
		{
			/** on-开启 off-关闭 */
			CSTR enable;
			/** 设备级能力类型 */
			CSTR type;
		}) device;
		/** define a list with struct of deviceAbility_AbilityEnableConfigRequestData_ChannelsElement */
		DECLARE_LIST(struct deviceAbility_AbilityEnableConfigRequestData_ChannelsElement
		{
			/** define a list with struct of deviceAbility_AbilityEnableConfigRequestData_ChannelsElement_DetailElement */
			DECLARE_LIST(struct deviceAbility_AbilityEnableConfigRequestData_ChannelsElement_DetailElement
			{
				/** on-开启 off-关闭 */
				CSTR enable;
				/** 通道级能力类型 */
				CSTR type;
			}) detail;
			/** [int]通道号，《由于PaaS协议之前拼写错误，服务做兼容，channleId，channleId 2个字段都要传给设备》 */
			int channelId;
		}) channels;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceAbility_AbilityEnableConfigRequest;

C_API deviceAbility_AbilityEnableConfigRequest *HSAPI_INIT(deviceAbility_AbilityEnableConfigRequest);

typedef struct deviceAbility_AbilityEnableConfigResponse 
{
	HsviewResponse base;

	struct deviceAbility_AbilityEnableConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceAbility_AbilityEnableConfigResponse;

C_API deviceAbility_AbilityEnableConfigResponse *HSAPI_INIT(deviceAbility_AbilityEnableConfigResponse);

#endif
