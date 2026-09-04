/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_ChnAlarmPlanGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_ChnAlarmPlanGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取单通道报警计划
响应参数说明
 channels：通道数组
 rules：报警计划规则
 period:[string]，参考[计划周期定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)
 beginTime和endTime：生效的起止时间,时间格式为THHMMSS

参考PaaS协议：[获取单通道报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E5%8D%95%E9%80%9A%E9%81%93%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_ChnAlarmPlanGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_ChnAlarmPlanGetRequestData
	{
		
		/** [cstr]/device/alarm/plan/query/ */
		#define _STATIC_transferAlarm_ChnAlarmPlanGetRequestData_url "/device/alarm/plan/query/"
		CSTR url;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_ChnAlarmPlanGetRequest;

C_API transferAlarm_ChnAlarmPlanGetRequest *HSAPI_INIT(transferAlarm_ChnAlarmPlanGetRequest);

typedef struct transferAlarm_ChnAlarmPlanGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_ChnAlarmPlanGetResponseData
	{
		
		/** define a list with struct of transferAlarm_ChnAlarmPlanGetResponseData_RulesElement */
		DECLARE_LIST(struct transferAlarm_ChnAlarmPlanGetResponseData_RulesElement
		{
			/** T010000 */
			CSTR endTime;
			/** T000000 */
			CSTR beginTime;
			/** Monday */
			CSTR period;
		}) rules;
 
	} data;

} transferAlarm_ChnAlarmPlanGetResponse;

C_API transferAlarm_ChnAlarmPlanGetResponse *HSAPI_INIT(transferAlarm_ChnAlarmPlanGetResponse);

#endif
