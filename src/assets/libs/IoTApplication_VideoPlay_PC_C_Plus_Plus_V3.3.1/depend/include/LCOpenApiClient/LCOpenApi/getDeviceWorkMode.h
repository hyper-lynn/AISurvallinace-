/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223123, Author: 27665, Date: 2022-08-10 09:30:55 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_getDeviceWorkMode_H_
#define _LC_OPENAPI_CLIENT_getDeviceWorkMode_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备的工作模式
 */

typedef struct getDeviceWorkModeRequest 
{
	LCOpenApiRequest base;

	struct getDeviceWorkModeRequestData
	{
		
		/** 可选，通道上设备序列号，优先级大于channelId */
		CSTR channelSn;
		/** 可选，不存在默认查询的是设备 */
		CSTR channelId;
		/**  */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} getDeviceWorkModeRequest;

C_API getDeviceWorkModeRequest *LCOPENAPI_INIT(getDeviceWorkModeRequest);

typedef struct getDeviceWorkModeResponse 
{
	LCOpenApiResponse base;

	struct getDeviceWorkModeResponseData
	{
		
		/** struct of getDeviceWorkModeResponseData_Detail */
		struct getDeviceWorkModeResponseData_Detail {
			/** 可选，两次PIR间隔时间, [string]，单位秒 */
			CSTR intervalTime;
			/** struct of getDeviceWorkModeResponseData_Detail_TimedWakeup */
			struct getDeviceWorkModeResponseData_Detail_TimedWakeup {
				/** [int]表示夜间间隔时间，单位：秒 */
				int nightInterval;
				/** [bool]定时唤醒使能是否开启 */
				BOOL enable;
				/** [int]表示白天间隔时间，单位：秒 */
				int dayInterval;
				/** define a list with struct of getDeviceWorkModeResponseData_Detail_TimedWakeup_PeriodicWakeupElement */
				DECLARE_LIST(struct getDeviceWorkModeResponseData_Detail_TimedWakeup_PeriodicWakeupElement
				{
					/** 时间格式为HH:mm:ss */
					CSTR endTime;
					/** 时间格式为HH:mm:ss */
					CSTR beginTime;
					/** Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday */
					CSTR period;
				}) periodicWakeup;
				/** 休眠模式 */
				CSTR mode;
			} timedWakeup;
			/** struct of getDeviceWorkModeResponseData_Detail_LowPowerSleep */
			struct getDeviceWorkModeResponseData_Detail_LowPowerSleep {
				/** [bool]休眠使能是否开启 */
				BOOL enable;
				/** 休眠阈值 */
				CSTR electricity;
			} lowPowerSleep;
			/** 0,1 */
			DECLARE_LIST(CSTR) modes;
			/** 工作模式 */
			CSTR mode;
			/** 可选，逗留时长, [string]，单位秒 */
			CSTR stayTime;
			/** 可选，单次PIR录像上限, [string]，单位秒 */
			CSTR recordTime;
		} detail;
 
	} data;

} getDeviceWorkModeResponse;

C_API getDeviceWorkModeResponse *LCOPENAPI_INIT(getDeviceWorkModeResponse);

#endif
