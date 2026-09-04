/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_SetApPlan_H_
#define _HSVIEW_CLIENT_API_agOperate_SetApPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件的计划

defenceAreaType:计划类型，默认为intime，取值如下：
intime:及时
delay: 延时
fullday:24小时

enableDelay:延时类型有效，其他类型不用关心。

period：生效的周期, 不支持跨天！
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日

beginTime和endTime：生效的起止时间,时间格式为THHMMSS，endTime必须大于beginTime。

参考PaaS协议：[设置配件报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92%2F%E8%AE%BE%E7%BD%AE%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)
【需要使用平台账号签名】
 */

typedef struct agOperate_SetApPlanRequest 
{
	HsviewRequest base;

	struct agOperate_SetApPlanRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** delay */
		CSTR defenceAreaType;
		/** define a list with struct of agOperate_SetApPlanRequestData_RulesElement */
		DECLARE_LIST(struct agOperate_SetApPlanRequestData_RulesElement
		{
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** 重复周期 */
			CSTR period;
		}) rules;
		/** [int]延时时间 */
		int enableDelay;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_SetApPlanRequest;

C_API agOperate_SetApPlanRequest *HSAPI_INIT(agOperate_SetApPlanRequest);

typedef struct agOperate_SetApPlanResponse 
{
	HsviewResponse base;

	struct agOperate_SetApPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_SetApPlanResponse;

C_API agOperate_SetApPlanResponse *HSAPI_INIT(agOperate_SetApPlanResponse);

#endif
