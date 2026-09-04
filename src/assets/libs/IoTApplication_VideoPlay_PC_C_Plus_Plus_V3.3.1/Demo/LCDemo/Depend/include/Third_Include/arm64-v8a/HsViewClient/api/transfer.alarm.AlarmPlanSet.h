/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_AlarmPlanSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_AlarmPlanSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

一般情况下不要再引入该协议使用，请使用[transfer.alarm.MotionDetectPlanConfig](https://paas.dahuatech.com/wiki/?p=%2FSaaS%2FtransferPaaS%2Ftransfer.alarm.MotionDetectPlanConfig&s=pj)

设置报警计划

> 	特别说明
 + 支持批量，但一次不得超过8通道

参考PaaS协议：[设置报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_AlarmPlanSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_AlarmPlanSetRequestData
	{
		
		/** [cstr]/device/alarm/plan/config */
		#define _STATIC_transferAlarm_AlarmPlanSetRequestData_url "/device/alarm/plan/config"
		CSTR url;
		/** struct of transferAlarm_AlarmPlanSetRequestData_Content */
		struct transferAlarm_AlarmPlanSetRequestData_Content {
			/** define a list with struct of transferAlarm_AlarmPlanSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferAlarm_AlarmPlanSetRequestData_Content_ChannelsElement
			{
				/** define a list with struct of transferAlarm_AlarmPlanSetRequestData_Content_ChannelsElement_RulesElement */
				DECLARE_LIST(struct transferAlarm_AlarmPlanSetRequestData_Content_ChannelsElement_RulesElement
				{
					/** T010000 */
					CSTR endTime;
					/** T000000 */
					CSTR beginTime;
					/** Monday */
					CSTR period;
				}) rules;
				/** [int] */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_AlarmPlanSetRequest;

C_API transferAlarm_AlarmPlanSetRequest *HSAPI_INIT(transferAlarm_AlarmPlanSetRequest);

typedef struct transferAlarm_AlarmPlanSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_AlarmPlanSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_AlarmPlanSetResponse;

C_API transferAlarm_AlarmPlanSetResponse *HSAPI_INIT(transferAlarm_AlarmPlanSetResponse);

#endif
