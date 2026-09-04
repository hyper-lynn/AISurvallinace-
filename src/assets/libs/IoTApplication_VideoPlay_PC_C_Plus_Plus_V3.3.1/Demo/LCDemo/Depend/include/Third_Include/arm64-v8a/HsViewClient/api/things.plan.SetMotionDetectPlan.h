/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsPlan_SetMotionDetectPlan_H_
#define _HSVIEW_CLIENT_API_thingsPlan_SetMotionDetectPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备移动检测提醒计划


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

typedef struct thingsPlan_SetMotionDetectPlanRequest 
{
	HsviewRequest base;

	struct thingsPlan_SetMotionDetectPlanRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** define a list with struct of thingsPlan_SetMotionDetectPlanRequestData_RulesElement */
		DECLARE_LIST(struct thingsPlan_SetMotionDetectPlanRequestData_RulesElement
		{
			/** T113000 */
			CSTR endTime;
			/** T083000 */
			CSTR beginTime;
			/** Sunday */
			CSTR period;
		}) rules;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsPlan_SetMotionDetectPlanRequest;

C_API thingsPlan_SetMotionDetectPlanRequest *HSAPI_INIT(thingsPlan_SetMotionDetectPlanRequest);

typedef struct thingsPlan_SetMotionDetectPlanResponse 
{
	HsviewResponse base;

	struct thingsPlan_SetMotionDetectPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsPlan_SetMotionDetectPlanResponse;

C_API thingsPlan_SetMotionDetectPlanResponse *HSAPI_INIT(thingsPlan_SetMotionDetectPlanResponse);

#endif
