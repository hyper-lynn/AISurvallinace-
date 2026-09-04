/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectPlanConfig_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectPlanConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警计划

> 	特别说明
 + 支持批量，但一次不得超过8通道

参考PaaS协议：[设置报警计划](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E6%8A%A5%E8%AD%A6%E8%AE%A1%E5%88%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectPlanConfigRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectPlanConfigRequestData
	{
		
		/** [cstr]/device/alarm/plan/config */
		#define _STATIC_transferAlarm_MotionDetectPlanConfigRequestData_url "/device/alarm/plan/config"
		CSTR url;
		/** struct of transferAlarm_MotionDetectPlanConfigRequestData_Content */
		struct transferAlarm_MotionDetectPlanConfigRequestData_Content {
			/** define a list with struct of transferAlarm_MotionDetectPlanConfigRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferAlarm_MotionDetectPlanConfigRequestData_Content_ChannelsElement
			{
				/** define a list with struct of transferAlarm_MotionDetectPlanConfigRequestData_Content_ChannelsElement_RulesElement */
				DECLARE_LIST(struct transferAlarm_MotionDetectPlanConfigRequestData_Content_ChannelsElement_RulesElement
				{
					/** 生效的结束时间，时间格式为THHMMSS，如T010000 */
					CSTR endTime;
					/** 生效的开始时间，时间格式为THHMMSS，如T000000 */
					CSTR beginTime;
					/** Monday */
					CSTR period;
				}) rules;
				/** [int]设备通道号 */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_MotionDetectPlanConfigRequest;

C_API transferAlarm_MotionDetectPlanConfigRequest *HSAPI_INIT(transferAlarm_MotionDetectPlanConfigRequest);

typedef struct transferAlarm_MotionDetectPlanConfigResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectPlanConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_MotionDetectPlanConfigResponse;

C_API transferAlarm_MotionDetectPlanConfigResponse *HSAPI_INIT(transferAlarm_MotionDetectPlanConfigResponse);

#endif
