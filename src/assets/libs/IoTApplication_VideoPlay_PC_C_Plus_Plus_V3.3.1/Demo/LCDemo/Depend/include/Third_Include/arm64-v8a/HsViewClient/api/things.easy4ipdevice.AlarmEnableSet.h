/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsEasy4ipdevice_AlarmEnableSet_H_
#define _HSVIEW_CLIENT_API_thingsEasy4ipdevice_AlarmEnableSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
easy4ip设备告警订阅设置

----------备注----------
平台按easy4ip老协议补充填充4个字段：
"servertype":"Easy4Ip",
"effectivetime"
"sound"="a.caf",
"serveraddr"
------------------------

【使用平台账号签名】
 */

typedef struct thingsEasy4ipdevice_AlarmEnableSetRequest 
{
	HsviewRequest base;

	struct thingsEasy4ipdevice_AlarmEnableSetRequestData
	{
		
		/** [O]设备级别告警类型 */
		DECLARE_LIST(CSTR) alarmtype;
		/** define a list with struct of thingsEasy4ipdevice_AlarmEnableSetRequestData_ChannelsElement */
		DECLARE_LIST(struct thingsEasy4ipdevice_AlarmEnableSetRequestData_ChannelsElement
		{
			/** [int]通道号 */
			int channelid;
			/** define a list with struct of thingsEasy4ipdevice_AlarmEnableSetRequestData_ChannelsElement_ChannelalarmtypeElement */
			DECLARE_LIST(struct thingsEasy4ipdevice_AlarmEnableSetRequestData_ChannelsElement_ChannelalarmtypeElement
			{
				/** [O]通道级别告警子类型 */
				CSTR subtype;
				/** 通道级别告警类型,如VideoMotion,注意首字母大写 */
				CSTR type;
			}) channelalarmtype;
		}) channels;
		/** 设备名称，非空，最大长度64 */
		CSTR devicename;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsEasy4ipdevice_AlarmEnableSetRequest;

C_API thingsEasy4ipdevice_AlarmEnableSetRequest *HSAPI_INIT(thingsEasy4ipdevice_AlarmEnableSetRequest);

typedef struct thingsEasy4ipdevice_AlarmEnableSetResponse 
{
	HsviewResponse base;

	struct thingsEasy4ipdevice_AlarmEnableSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsEasy4ipdevice_AlarmEnableSetResponse;

C_API thingsEasy4ipdevice_AlarmEnableSetResponse *HSAPI_INIT(thingsEasy4ipdevice_AlarmEnableSetResponse);

#endif
