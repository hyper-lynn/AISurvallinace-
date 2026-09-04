/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_LocalRecordPlanGet_H_
#define _HSVIEW_CLIENT_API_transferRecord_LocalRecordPlanGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备本地录像计划

参考PaaS协议：[获取设备本地录像计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92%2F%E8%8E%B7%E5%8F%96%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_LocalRecordPlanGetRequest 
{
	HsviewRequest base;

	struct transferRecord_LocalRecordPlanGetRequestData
	{
		
		/** [cstr]/device/local/record/plan/query */
		#define _STATIC_transferRecord_LocalRecordPlanGetRequestData_url "/device/local/record/plan/query"
		CSTR url;
		/** struct of transferRecord_LocalRecordPlanGetRequestData_Content */
		struct transferRecord_LocalRecordPlanGetRequestData_Content {
			/** [int]设备通道号 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_LocalRecordPlanGetRequest;

C_API transferRecord_LocalRecordPlanGetRequest *HSAPI_INIT(transferRecord_LocalRecordPlanGetRequest);

typedef struct transferRecord_LocalRecordPlanGetResponse 
{
	HsviewResponse base;

	struct transferRecord_LocalRecordPlanGetResponseData
	{
		
		/** define a list with struct of transferRecord_LocalRecordPlanGetResponseData_ChannelsElement */
		DECLARE_LIST(struct transferRecord_LocalRecordPlanGetResponseData_ChannelsElement
		{
			/** define a list with struct of transferRecord_LocalRecordPlanGetResponseData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct transferRecord_LocalRecordPlanGetResponseData_ChannelsElement_RulesElement
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
 
	} data;

} transferRecord_LocalRecordPlanGetResponse;

C_API transferRecord_LocalRecordPlanGetResponse *HSAPI_INIT(transferRecord_LocalRecordPlanGetResponse);

#endif
