/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_LocalRecordPlanSet_H_
#define _HSVIEW_CLIENT_API_transferRecord_LocalRecordPlanSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备本地录像计划

> 	特别说明
 + 支持批量，但一次不得超过8通道

参考PaaS协议：[设置设备本地录像计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92%2F%E8%AE%BE%E7%BD%AE%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_LocalRecordPlanSetRequest 
{
	HsviewRequest base;

	struct transferRecord_LocalRecordPlanSetRequestData
	{
		
		/** [cstr]/device/local/record/plan/config */
		#define _STATIC_transferRecord_LocalRecordPlanSetRequestData_url "/device/local/record/plan/config"
		CSTR url;
		/** struct of transferRecord_LocalRecordPlanSetRequestData_Content */
		struct transferRecord_LocalRecordPlanSetRequestData_Content {
			/** define a list with struct of transferRecord_LocalRecordPlanSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferRecord_LocalRecordPlanSetRequestData_Content_ChannelsElement
			{
				/** define a list with struct of transferRecord_LocalRecordPlanSetRequestData_Content_ChannelsElement_RulesElement */
				DECLARE_LIST(struct transferRecord_LocalRecordPlanSetRequestData_Content_ChannelsElement_RulesElement
				{
					/** 生效的结束时间,时间格式为THHMMSS */
					CSTR endTime;
					/** 生效的起始时间,时间格式为THHMMSS */
					CSTR beginTime;
					/** Monday */
					CSTR period;
				}) rules;
				/** [int] 1 */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_LocalRecordPlanSetRequest;

C_API transferRecord_LocalRecordPlanSetRequest *HSAPI_INIT(transferRecord_LocalRecordPlanSetRequest);

typedef struct transferRecord_LocalRecordPlanSetResponse 
{
	HsviewResponse base;

	struct transferRecord_LocalRecordPlanSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferRecord_LocalRecordPlanSetResponse;

C_API transferRecord_LocalRecordPlanSetResponse *HSAPI_INIT(transferRecord_LocalRecordPlanSetResponse);

#endif
