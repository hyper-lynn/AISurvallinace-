/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectPlanQuery_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectPlanQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警计划

参考PaaS协议：[获取报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectPlanQueryRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectPlanQueryRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/alarm/plan/query */
		#define _STATIC_transferAlarm_MotionDetectPlanQueryRequestData_url "/device/alarm/plan/query"
		CSTR url;

	} data;

} transferAlarm_MotionDetectPlanQueryRequest;

C_API transferAlarm_MotionDetectPlanQueryRequest *HSAPI_INIT(transferAlarm_MotionDetectPlanQueryRequest);

typedef struct transferAlarm_MotionDetectPlanQueryResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectPlanQueryResponseData
	{
		
		/** define a list with struct of transferAlarm_MotionDetectPlanQueryResponseData_ChannelsElement */
		DECLARE_LIST(struct transferAlarm_MotionDetectPlanQueryResponseData_ChannelsElement
		{
			/** define a list with struct of transferAlarm_MotionDetectPlanQueryResponseData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct transferAlarm_MotionDetectPlanQueryResponseData_ChannelsElement_RulesElement
			{
				/** 生效的结束时间，时间格式为THHMMSS，如T010000 */
				CSTR endTime;
				/** 生效的开始时间，时间格式为THHMMSS，如T000000 */
				CSTR beginTime;
				/** Monday */
				CSTR period;
			}) rules;
			/** [int]设备通道号 */
			int channelId;
		}) channels;
 
	} data;

} transferAlarm_MotionDetectPlanQueryResponse;

C_API transferAlarm_MotionDetectPlanQueryResponse *HSAPI_INIT(transferAlarm_MotionDetectPlanQueryResponse);

#endif
