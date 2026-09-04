/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetApPlan_H_
#define _HSVIEW_CLIENT_API_GetApPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件的计划
period：生效的周期
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日

	beginTime和endTime：生效的起止时间,时间格式为%H:%M:%S，endTime必须小于beginTime。
	
[更新记录] 2017.4.5 修改协议备注, period不支持once、workday、holiday。
【需要使用平台账号签名】
 */

typedef struct GetApPlanRequest 
{
	HsviewRequest base;

	struct GetApPlanRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} GetApPlanRequest;

C_API GetApPlanRequest *HSAPI_INIT(GetApPlanRequest);

typedef struct GetApPlanResponse 
{
	HsviewResponse base;

	struct GetApPlanResponseData
	{
		
		/** define a list with struct of GetApPlanResponseData_RulesElement */
		DECLARE_LIST(struct GetApPlanResponseData_RulesElement
		{
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** 重复周期 */
			CSTR period;
		}) rules;
		/** [int]配件的使能:1-使能开启 ，0-使能关闭 */
		int apEnable;
 
	} data;

} GetApPlanResponse;

C_API GetApPlanResponse *HSAPI_INIT(GetApPlanResponse);

#endif
