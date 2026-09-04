/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmRemindPlanGet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmRemindPlanGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取提醒时间段
 时间格式为THHMMSS
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmRemindPlanGetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmRemindPlanGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyPhoneAlarm_PhoneAlarmRemindPlanGetRequest;

C_API strategyPhoneAlarm_PhoneAlarmRemindPlanGetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmRemindPlanGetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmRemindPlanGetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmRemindPlanGetResponseData
	{
		
		/** 时间设定，如T080059-T113059，是手机本地时间，开始范围（T000000到T235959），结束范围（T000000到T235959） */
		DECLARE_LIST(CSTR) remindTime;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmRemindPlanGetResponse;

C_API strategyPhoneAlarm_PhoneAlarmRemindPlanGetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmRemindPlanGetResponse);

#endif
