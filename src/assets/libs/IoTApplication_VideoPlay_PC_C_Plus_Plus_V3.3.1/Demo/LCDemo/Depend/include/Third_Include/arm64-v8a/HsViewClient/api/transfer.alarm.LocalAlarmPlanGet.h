/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_LocalAlarmPlanGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_LocalAlarmPlanGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备本地报警计划
>    响应参数说明    
 + channels：通道数组
 + rules：报警计划规则
 + period:参考[计划周期定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)
 + beginTime和endTime：生效的起止时间，时间格式为THHMMSS

参考PaaS协议：[获取设备本地报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E6%9C%AC%E5%9C%B0%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)
【需要使用平台账号签名】
 */

typedef struct transferAlarm_LocalAlarmPlanGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_LocalAlarmPlanGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/local/alarm/plan/query */
		#define _STATIC_transferAlarm_LocalAlarmPlanGetRequestData_url "/device/local/alarm/plan/query"
		CSTR url;

	} data;

} transferAlarm_LocalAlarmPlanGetRequest;

C_API transferAlarm_LocalAlarmPlanGetRequest *HSAPI_INIT(transferAlarm_LocalAlarmPlanGetRequest);

typedef struct transferAlarm_LocalAlarmPlanGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_LocalAlarmPlanGetResponseData
	{
		
		/** define a list with struct of transferAlarm_LocalAlarmPlanGetResponseData_ChannelsElement */
		DECLARE_LIST(struct transferAlarm_LocalAlarmPlanGetResponseData_ChannelsElement
		{
			/** define a list with struct of transferAlarm_LocalAlarmPlanGetResponseData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct transferAlarm_LocalAlarmPlanGetResponseData_ChannelsElement_RulesElement
			{
				/** T010000 */
				CSTR endTime;
				/** T000000 */
				CSTR beginTime;
				/** Monday */
				CSTR period;
			}) rules;
			/** [int] */
			int channelId;
		}) channels;
 
	} data;

} transferAlarm_LocalAlarmPlanGetResponse;

C_API transferAlarm_LocalAlarmPlanGetResponse *HSAPI_INIT(transferAlarm_LocalAlarmPlanGetResponse);

#endif
