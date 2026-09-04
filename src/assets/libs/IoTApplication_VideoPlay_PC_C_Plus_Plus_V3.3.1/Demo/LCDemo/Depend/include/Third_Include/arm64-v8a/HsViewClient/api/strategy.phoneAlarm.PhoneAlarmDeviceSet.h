/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmDeviceSet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmDeviceSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 新增删除提醒设备列表
 devices数组里面全部是已勾选的设备，平台内部处理设备新增还是删除
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmDeviceSetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmDeviceSetRequestData
	{
		
		/** define a list with struct of strategyPhoneAlarm_PhoneAlarmDeviceSetRequestData_InsertDevicesElement */
		DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmDeviceSetRequestData_InsertDevicesElement
		{
			/** 配件Id */
			DECLARE_LIST(CSTR) apList;
			/** 通道号 */
			DECLARE_LIST(CSTR) channelList;
			/** 设备序列号 */
			CSTR deviceId;
		}) insertDevices;
		/** define a list with struct of strategyPhoneAlarm_PhoneAlarmDeviceSetRequestData_DeleteDevicesElement */
		DECLARE_LIST(struct strategyPhoneAlarm_PhoneAlarmDeviceSetRequestData_DeleteDevicesElement
		{
			/** 配件Id */
			DECLARE_LIST(CSTR) apList;
			/** 通道号 */
			DECLARE_LIST(CSTR) channelList;
			/** 设备序列号 */
			CSTR deviceId;
		}) deleteDevices;

	} data;

} strategyPhoneAlarm_PhoneAlarmDeviceSetRequest;

C_API strategyPhoneAlarm_PhoneAlarmDeviceSetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmDeviceSetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmDeviceSetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmDeviceSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmDeviceSetResponse;

C_API strategyPhoneAlarm_PhoneAlarmDeviceSetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmDeviceSetResponse);

#endif
