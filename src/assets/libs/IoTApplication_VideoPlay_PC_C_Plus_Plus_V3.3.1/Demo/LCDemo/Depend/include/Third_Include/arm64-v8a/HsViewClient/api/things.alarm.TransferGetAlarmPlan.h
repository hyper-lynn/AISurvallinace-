/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferGetAlarmPlan_H_
#define _HSVIEW_CLIENT_API_TransferGetAlarmPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警计划 【注意：该协议为平台内部协议，与客户端无关】

transferContent内容说明参考PaaS协议：[获取单通道报警计划](http://paas.dahuatech.com/wiki/?p=/%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86/%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE/%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE/%E8%8E%B7%E5%8F%96%E5%8D%95%E9%80%9A%E9%81%93%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferGetAlarmPlanRequest 
{
	HsviewRequest base;

	struct TransferGetAlarmPlanRequestData
	{
		
		/** [int]通道ID */
		int channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferGetAlarmPlanRequest;

C_API TransferGetAlarmPlanRequest *HSAPI_INIT(TransferGetAlarmPlanRequest);

typedef struct TransferGetAlarmPlanResponse 
{
	HsviewResponse base;

	struct TransferGetAlarmPlanResponseData
	{
		
		/** define a list with struct of TransferGetAlarmPlanResponseData_RulesElement */
		DECLARE_LIST(struct TransferGetAlarmPlanResponseData_RulesElement
		{
			/** T010000 */
			CSTR endTime;
			/** T000000 */
			CSTR beginTime;
			/** Monday */
			CSTR period;
		}) rules;
 
	} data;

} TransferGetAlarmPlanResponse;

C_API TransferGetAlarmPlanResponse *HSAPI_INIT(TransferGetAlarmPlanResponse);

#endif
