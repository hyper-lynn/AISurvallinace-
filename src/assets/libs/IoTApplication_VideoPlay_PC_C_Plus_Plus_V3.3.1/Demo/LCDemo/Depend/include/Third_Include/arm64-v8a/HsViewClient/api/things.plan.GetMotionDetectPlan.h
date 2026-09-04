/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsPlan_GetMotionDetectPlan_H_
#define _HSVIEW_CLIENT_API_thingsPlan_GetMotionDetectPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备移动检测提醒计划
	
	period：生效的周期
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日

	beginTime和endTime：生效的起止时间,时间格式为THHMMSS，endTime必须小于beginTime。
	同一个period可以有多对baginTime和endTime，最多只能有六对beginTime和endTime。

【使用平台账号签名】
 */

typedef struct thingsPlan_GetMotionDetectPlanRequest 
{
	HsviewRequest base;

	struct thingsPlan_GetMotionDetectPlanRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsPlan_GetMotionDetectPlanRequest;

C_API thingsPlan_GetMotionDetectPlanRequest *HSAPI_INIT(thingsPlan_GetMotionDetectPlanRequest);

typedef struct thingsPlan_GetMotionDetectPlanResponse 
{
	HsviewResponse base;

	struct thingsPlan_GetMotionDetectPlanResponseData
	{
		
		/** define a list with struct of thingsPlan_GetMotionDetectPlanResponseData_RulesElement */
		DECLARE_LIST(struct thingsPlan_GetMotionDetectPlanResponseData_RulesElement
		{
			/** T113000 */
			CSTR endTime;
			/** T083000 */
			CSTR beginTime;
			/** Sunday */
			CSTR period;
		}) rules;
 
	} data;

} thingsPlan_GetMotionDetectPlanResponse;

C_API thingsPlan_GetMotionDetectPlanResponse *HSAPI_INIT(thingsPlan_GetMotionDetectPlanResponse);

#endif
