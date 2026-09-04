/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_GetAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页查询报警信息

 */

typedef struct GetAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct GetAlarmMessageRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** [cstr]getAlarmMessage */
		#define _STATIC_GetAlarmMessageRequestData_method "getAlarmMessage"
		CSTR method;
		/** 拉取报警消息的个数，最大值为100 */
		CSTR count;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 通道ID */
		CSTR channelId;
		/** 不填写默认从头开始拉去 */
		CSTR nextAlarmId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAlarmMessageRequest;

C_API GetAlarmMessageRequest *LCOPENAPI_INIT(GetAlarmMessageRequest);

typedef struct GetAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct GetAlarmMessageResponseData
	{
		
		/** 当前报警消息列表最后一条报警消息Id */
		CSTR nextAlarmId;
		/** [int]当前获取到的报警消息总数 */
		int count;
		/** define a list with struct of GetAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetAlarmMessageResponseData_AlarmsElement
		{
			/** [int]报警类型 */
			int type;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 设备ID */
			CSTR deviceId;
			/** [long]报警消息ID */
			int64 alarmId;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picurlArray;
			/** 通道号 */
			CSTR channelId;
			/** 设备或通道的名称 */
			CSTR name;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
		}) alarms;
 
	} data;

} GetAlarmMessageResponse;

C_API GetAlarmMessageResponse *LCOPENAPI_INIT(GetAlarmMessageResponse);

#endif
