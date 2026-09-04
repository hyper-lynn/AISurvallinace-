/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferSetAlarmPlan_H_
#define _HSVIEW_CLIENT_API_TransferSetAlarmPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警计划【注意：改协议是平台内部协议，与客户端无关】

transferContent内容说明参考PaaS协议：[设置报警计划](http://paas.dahuatech.com/wiki/?p=/%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86/%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE/%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE/%E8%AE%BE%E7%BD%AE%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferSetAlarmPlanRequest 
{
	HsviewRequest base;

	struct TransferSetAlarmPlanRequestData
	{
		
		/** struct of TransferSetAlarmPlanRequestData_TransferContent */
		struct TransferSetAlarmPlanRequestData_TransferContent {
			/** define a list with struct of TransferSetAlarmPlanRequestData_TransferContent_ChannelsElement */
			DECLARE_LIST(struct TransferSetAlarmPlanRequestData_TransferContent_ChannelsElement
			{
				/** define a list with struct of TransferSetAlarmPlanRequestData_TransferContent_ChannelsElement_RulesElement */
				DECLARE_LIST(struct TransferSetAlarmPlanRequestData_TransferContent_ChannelsElement_RulesElement
				{
					/** T010000 */
					CSTR endTime;
					/** T000000 */
					CSTR beginTime;
					/** Monday */
					CSTR period;
				}) rules;
				/** [int]通道ID */
				int channelId ;
			}) channels;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferSetAlarmPlanRequest;

C_API TransferSetAlarmPlanRequest *HSAPI_INIT(TransferSetAlarmPlanRequest);

typedef struct TransferSetAlarmPlanResponse 
{
	HsviewResponse base;

	struct TransferSetAlarmPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferSetAlarmPlanResponse;

C_API TransferSetAlarmPlanResponse *HSAPI_INIT(TransferSetAlarmPlanResponse);

#endif
