/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_LocalAlarmPlanSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_LocalAlarmPlanSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备本地报警计划

> 	特别说明
 + 支持批量，但一次不得超过8通道

>    请求参数说明
 + channels：通道数组
 + rules：报警计划规则
 + period:[string]，参考[计划周期定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)
 + beginTime和endTime：生效的起止时间,时间格式为THHMMSS

参考PaaS协议：[设置设备本地报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E6%9C%AC%E5%9C%B0%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)
【需要使用平台账号签名】
 */

typedef struct transferAlarm_LocalAlarmPlanSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_LocalAlarmPlanSetRequestData
	{
		
		/** [cstr]/device/local/alarm/plan/config */
		#define _STATIC_transferAlarm_LocalAlarmPlanSetRequestData_url "/device/local/alarm/plan/config"
		CSTR url;
		/** struct of transferAlarm_LocalAlarmPlanSetRequestData_Content */
		struct transferAlarm_LocalAlarmPlanSetRequestData_Content {
			/** define a list with struct of transferAlarm_LocalAlarmPlanSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferAlarm_LocalAlarmPlanSetRequestData_Content_ChannelsElement
			{
				/** define a list with struct of transferAlarm_LocalAlarmPlanSetRequestData_Content_ChannelsElement_RulesElement */
				DECLARE_LIST(struct transferAlarm_LocalAlarmPlanSetRequestData_Content_ChannelsElement_RulesElement
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
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_LocalAlarmPlanSetRequest;

C_API transferAlarm_LocalAlarmPlanSetRequest *HSAPI_INIT(transferAlarm_LocalAlarmPlanSetRequest);

typedef struct transferAlarm_LocalAlarmPlanSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_LocalAlarmPlanSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_LocalAlarmPlanSetResponse;

C_API transferAlarm_LocalAlarmPlanSetResponse *HSAPI_INIT(transferAlarm_LocalAlarmPlanSetResponse);

#endif
