/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAbility_AlarmInAbilitySet_H_
#define _HSVIEW_CLIENT_API_transferAbility_AlarmInAbilitySet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备告警输入通道功能开关

参考PaaS协议：[设置设备告警输入通道功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E5%91%8A%E8%AD%A6%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E5%91%8A%E8%AD%A6%E8%BE%93%E5%85%A5%E9%80%9A%E9%81%93%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAbility_AlarmInAbilitySetRequest 
{
	HsviewRequest base;

	struct transferAbility_AlarmInAbilitySetRequestData
	{
		
		/** [cstr]/device/alarmIn/ability/config */
		#define _STATIC_transferAbility_AlarmInAbilitySetRequestData_url "/device/alarmIn/ability/config"
		CSTR url;
		/** struct of transferAbility_AlarmInAbilitySetRequestData_Content */
		struct transferAbility_AlarmInAbilitySetRequestData_Content {
			/** define a list with struct of transferAbility_AlarmInAbilitySetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferAbility_AlarmInAbilitySetRequestData_Content_ChannelsElement
			{
				/** on-开启 off-关闭 */
				CSTR enable;
				/** [int]通道号 */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAbility_AlarmInAbilitySetRequest;

C_API transferAbility_AlarmInAbilitySetRequest *HSAPI_INIT(transferAbility_AlarmInAbilitySetRequest);

typedef struct transferAbility_AlarmInAbilitySetResponse 
{
	HsviewResponse base;

	struct transferAbility_AlarmInAbilitySetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAbility_AlarmInAbilitySetResponse;

C_API transferAbility_AlarmInAbilitySetResponse *HSAPI_INIT(transferAbility_AlarmInAbilitySetResponse);

#endif
