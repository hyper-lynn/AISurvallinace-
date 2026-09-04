/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneGet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取提醒联系人列表
 当state=valid 展示在页面
 state=invalid 隐藏在页面
 order:联系人顺序 从1开始
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneGetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneGetRequest;

C_API strategyPhoneAlarm_PhoneAlarmPhoneGetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneGetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneGetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneGetResponseData
	{
		
		/** define a list with struct of strategyPhoneAlarm_PhoneAlarmPhoneGetResponseData_PhonesElement */
		DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmPhoneGetResponseData_PhonesElement
		{
			/** valid:有效联系人,invalid:无效联系人 */
			CSTR state;
			/** [int] 1 */
			int order;
			/** 联系人电话号码（11位） */
			CSTR phone;
		}) phones;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneGetResponse;

C_API strategyPhoneAlarm_PhoneAlarmPhoneGetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneGetResponse);

#endif
