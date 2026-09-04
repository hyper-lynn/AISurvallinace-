/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsEasy4ipdevice_AlarmEnableGet_H_
#define _HSVIEW_CLIENT_API_thingsEasy4ipdevice_AlarmEnableGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
easy4ip设备告警订阅查询

【使用平台账号签名】
 */

typedef struct thingsEasy4ipdevice_AlarmEnableGetRequest 
{
	HsviewRequest base;

	struct thingsEasy4ipdevice_AlarmEnableGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsEasy4ipdevice_AlarmEnableGetRequest;

C_API thingsEasy4ipdevice_AlarmEnableGetRequest *HSAPI_INIT(thingsEasy4ipdevice_AlarmEnableGetRequest);

typedef struct thingsEasy4ipdevice_AlarmEnableGetResponse 
{
	HsviewResponse base;

	struct thingsEasy4ipdevice_AlarmEnableGetResponseData
	{
		
		/** [O]设备级别告警类型 */
		DECLARE_LIST(CSTR) alarmtype;
		/** 设备名称，非空，最大长度64 */
		CSTR devicename;
		/** define a list with struct of thingsEasy4ipdevice_AlarmEnableGetResponseData_ChannelsElement */
		DECLARE_LIST(struct thingsEasy4ipdevice_AlarmEnableGetResponseData_ChannelsElement
		{
			/** [int]通道号 */
			int channelid;
			/** define a list with struct of thingsEasy4ipdevice_AlarmEnableGetResponseData_ChannelsElement_ChannelalarmtypeElement */
			DECLARE_LIST(struct thingsEasy4ipdevice_AlarmEnableGetResponseData_ChannelsElement_ChannelalarmtypeElement
			{
				/** [O]通道级别告警子类型 */
				CSTR subtype;
				/** 通道级别告警类型 */
				CSTR type;
			}) channelalarmtype;
		}) channels;
 
	} data;

} thingsEasy4ipdevice_AlarmEnableGetResponse;

C_API thingsEasy4ipdevice_AlarmEnableGetResponse *HSAPI_INIT(thingsEasy4ipdevice_AlarmEnableGetResponse);

#endif
