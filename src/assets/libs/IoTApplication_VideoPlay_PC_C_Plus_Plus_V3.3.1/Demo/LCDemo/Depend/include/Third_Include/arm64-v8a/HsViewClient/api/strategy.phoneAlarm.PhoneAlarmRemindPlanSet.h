/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmRemindPlanSet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmRemindPlanSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 设置提醒时间段
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmRemindPlanSetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmRemindPlanSetRequestData
	{
		
		/** 时间设定，如T080059-T113059，是手机本地时间，开始范围（T000000到T235959），结束范围（T000000到T235959） */
		DECLARE_LIST(CSTR) remindTime;

	} data;

} strategyPhoneAlarm_PhoneAlarmRemindPlanSetRequest;

C_API strategyPhoneAlarm_PhoneAlarmRemindPlanSetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmRemindPlanSetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmRemindPlanSetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmRemindPlanSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmRemindPlanSetResponse;

C_API strategyPhoneAlarm_PhoneAlarmRemindPlanSetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmRemindPlanSetResponse);

#endif
