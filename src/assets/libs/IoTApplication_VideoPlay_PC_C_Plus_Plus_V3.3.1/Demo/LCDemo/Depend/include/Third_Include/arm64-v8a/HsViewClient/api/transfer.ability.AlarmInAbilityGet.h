/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAbility_AlarmInAbilityGet_H_
#define _HSVIEW_CLIENT_API_transferAbility_AlarmInAbilityGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备告警输入通道功能开关

参考PaaS协议：[获取设备告警输入通道功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E5%91%8A%E8%AD%A6%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E5%91%8A%E8%AD%A6%E8%BE%93%E5%85%A5%E9%80%9A%E9%81%93%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAbility_AlarmInAbilityGetRequest 
{
	HsviewRequest base;

	struct transferAbility_AlarmInAbilityGetRequestData
	{
		
		/** [cstr]/device/alarmIn/ability/query */
		#define _STATIC_transferAbility_AlarmInAbilityGetRequestData_url "/device/alarmIn/ability/query"
		CSTR url;
		/** struct of transferAbility_AlarmInAbilityGetRequestData_Content */
		struct transferAbility_AlarmInAbilityGetRequestData_Content {
			/** [int]通道号数组 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAbility_AlarmInAbilityGetRequest;

C_API transferAbility_AlarmInAbilityGetRequest *HSAPI_INIT(transferAbility_AlarmInAbilityGetRequest);

typedef struct transferAbility_AlarmInAbilityGetResponse 
{
	HsviewResponse base;

	struct transferAbility_AlarmInAbilityGetResponseData
	{
		
		/** define a list with struct of transferAbility_AlarmInAbilityGetResponseData_ChannelsElement */
		DECLARE_LIST(struct transferAbility_AlarmInAbilityGetResponseData_ChannelsElement
		{
			/** on-开启 off-关闭 */
			CSTR enable;
			/** [int]通道号 */
			int channelId;
		}) channels;
 
	} data;

} transferAbility_AlarmInAbilityGetResponse;

C_API transferAbility_AlarmInAbilityGetResponse *HSAPI_INIT(transferAbility_AlarmInAbilityGetResponse);

#endif
