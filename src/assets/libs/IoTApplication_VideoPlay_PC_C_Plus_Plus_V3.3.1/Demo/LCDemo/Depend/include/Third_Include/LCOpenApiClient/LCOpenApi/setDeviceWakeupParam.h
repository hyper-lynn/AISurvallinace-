/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227741, Author: 251672, Date: 2024-11-25 19:29:19 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_setDeviceWakeupParam_H_
#define _LC_OPENAPI_CLIENT_setDeviceWakeupParam_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备唤醒设置
 */

typedef struct setDeviceWakeupParamRequest 
{
	LCOpenApiRequest base;

	struct setDeviceWakeupParamRequestData
	{
		
		/** paas设备专属字段  工作模式 0	节能模式 1	普通模式 2	Ultra模式 3	自定义模式 4	超级省电模式 5	自动模式 6	常供电模式 7	休眠、定时唤醒模式 8浅休眠模式  9AOV模式 */
		CSTR workMode;
		/** [bool]唤醒使能是否开启 */
		BOOL enable;
		/** 白天间隔时间，单位秒（0-7200s） */
		CSTR dayInterval;
		/** 设备ID */
		CSTR deviceId;
		/**  */
		CSTR token;
		/** 夜间间隔时间，单位秒（0-7200s） */
		CSTR nightInterval;
		/** 可选，不存在默认查询的是设备 */
		CSTR channelId;
		/** define a list with struct of setDeviceWakeupParamRequestData_PeriodicWakeupElement */
		DECLARE_LIST(struct setDeviceWakeupParamRequestData_PeriodicWakeupElement
		{
			/** 时间格式为HH:mm:ss */
			CSTR endTime;
			/** 时间格式为HH:mm:ss */
			CSTR beginTime;
			/** Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday */
			CSTR period;
		}) periodicWakeup;
		/** 唤醒模式（TimeInterval（时间间隔模式），TimeSection（时间段模式）） */
		CSTR mode;

	} data;

} setDeviceWakeupParamRequest;

C_API setDeviceWakeupParamRequest *LCOPENAPI_INIT(setDeviceWakeupParamRequest);

typedef struct setDeviceWakeupParamResponse 
{
	LCOpenApiResponse base;

	struct setDeviceWakeupParamResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} setDeviceWakeupParamResponse;

C_API setDeviceWakeupParamResponse *LCOPENAPI_INIT(setDeviceWakeupParamResponse);

#endif
