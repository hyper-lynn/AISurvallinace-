/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneDelete_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 删除联系人
 order:联系人顺序号 从1开始
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneDeleteRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneDeleteRequestData
	{
		
		/** 联系人电话号码（11位） */
		CSTR phone;
		/** [int] 1 */
		int order;

	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneDeleteRequest;

C_API strategyPhoneAlarm_PhoneAlarmPhoneDeleteRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneDeleteRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneDeleteResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneDeleteResponse;

C_API strategyPhoneAlarm_PhoneAlarmPhoneDeleteResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneDeleteResponse);

#endif
