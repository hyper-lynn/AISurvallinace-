/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmMode_H_
#define _HSVIEW_CLIENT_API_SetAlarmMode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备或者配件的报警模式。
参数说明：
AlarmMode：
	Normal：正常的报警模式，产生事件时报警
	Timing：计时模式，当一段时间未产生事件则报警
TimeLimit：长时间没有发生事件的时限，单位为秒。该字段只有在AlarmMode为Timing时才有效，表示当TimeLimit时间没有事件，则产生一个报警。
【需要使用平台账号签名】
 */

typedef struct SetAlarmModeRequest 
{
	HsviewRequest base;

	struct SetAlarmModeRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmModeRequestData_METHOD "POST"
		/** [cstr]alarm-mode */
		#define _STATIC_SetAlarmModeRequestData_CMD "alarm-mode"
		/** struct of SetAlarmModeRequestData_Body */
		struct SetAlarmModeRequestData_Body {
			/** [int]长时间没有发生事件的时限，单位为秒 */
			int TimeLimit;
			/** 两种模式：Normal或Timing */
			CSTR AlarmMode;
		} body;

	} data;

} SetAlarmModeRequest;

C_API SetAlarmModeRequest *HSAPI_INIT(SetAlarmModeRequest);

typedef struct SetAlarmModeResponse 
{
	HsviewResponse base;

	struct SetAlarmModeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAlarmModeResponse;

C_API SetAlarmModeResponse *HSAPI_INIT(SetAlarmModeResponse);

#endif
