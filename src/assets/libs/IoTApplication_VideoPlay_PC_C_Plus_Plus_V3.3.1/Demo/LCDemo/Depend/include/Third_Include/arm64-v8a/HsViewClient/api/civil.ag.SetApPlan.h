/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetApPlan_H_
#define _HSVIEW_CLIENT_API_SetApPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件的计划
period：生效的周期, 不支持跨天！
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日

beginTime和endTime: 时间格式为%H:%M:%S

[更新记录] 2017.4.5 修改协议备注, period不支持跨天和多选，只支持星期一到星期天。
【需要使用平台账号签名】
 */

typedef struct SetApPlanRequest 
{
	HsviewRequest base;

	struct SetApPlanRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** define a list with struct of SetApPlanRequestData_RulesElement */
		DECLARE_LIST(struct SetApPlanRequestData_RulesElement
		{
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** 重复周期 */
			CSTR period;
		}) rules;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} SetApPlanRequest;

C_API SetApPlanRequest *HSAPI_INIT(SetApPlanRequest);

typedef struct SetApPlanResponse 
{
	HsviewResponse base;

	struct SetApPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetApPlanResponse;

C_API SetApPlanResponse *HSAPI_INIT(SetApPlanResponse);

#endif
