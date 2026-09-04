/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmMode_H_
#define _HSVIEW_CLIENT_API_GetAlarmMode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备或者配件的报警模式。
参数说明：
AlarmMode：
	Normal：正常的报警模式，产生事件时报警
	Timing：计时模式，当一段时间未产生事件则报警
TimeLimit：长时间没有发生事件的时限，单位为秒。该字段只有在AlarmMode为Timing时才有效，表示当TimeLimit时间没有事件，则产生一个报警。
【需要使用平台账号签名】
 */

typedef struct GetAlarmModeRequest 
{
	HsviewRequest base;

	struct GetAlarmModeRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetAlarmModeRequestData_METHOD "GET"
		/** [cstr]alarm-mode */
		#define _STATIC_GetAlarmModeRequestData_CMD "alarm-mode"
		/** struct of GetAlarmModeRequestData_Body */
		struct GetAlarmModeRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmModeRequest;

C_API GetAlarmModeRequest *HSAPI_INIT(GetAlarmModeRequest);

typedef struct GetAlarmModeResponse 
{
	HsviewResponse base;

	struct GetAlarmModeResponseData
	{
		
		/** [int]长时间没有发生事件的时限，单位为秒 */
		int TimeLimit;
		/** 两种模式：Normal或Timing */
		CSTR AlarmMode;
 
	} data;

} GetAlarmModeResponse;

C_API GetAlarmModeResponse *HSAPI_INIT(GetAlarmModeResponse);

#endif
