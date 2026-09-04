/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmDeviceGet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmDeviceGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取提醒设备列表
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmDeviceGetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmDeviceGetRequestData
	{
		
		/** [int]条数,最大128 */
		int limit;
		/** [long]上次查询最后一个设备id，为-1表示从最后一个开始获取 */
		int64 bindId;

	} data;

} strategyPhoneAlarm_PhoneAlarmDeviceGetRequest;

C_API strategyPhoneAlarm_PhoneAlarmDeviceGetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmDeviceGetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmDeviceGetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData
	{
		
		/** define a list with struct of strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement */
		DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement
		{
			/** define a list with struct of strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement_ApListElement */
			DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement_ApListElement
			{
				/** 配件名称 */
				CSTR apName;
				/** 报警网关配件id */
				CSTR apId;
			}) apList;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** define a list with struct of strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement_ChannelListElement */
			DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmDeviceGetResponseData_DeviceListElement_ChannelListElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** 通道号 */
				CSTR channelId;
			}) channelList;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmDeviceGetResponse;

C_API strategyPhoneAlarm_PhoneAlarmDeviceGetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmDeviceGetResponse);

#endif
