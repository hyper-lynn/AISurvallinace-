/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAlarmMessageById_H_
#define _LC_OPENAPI_CLIENT_GetAlarmMessageById_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据报警消息Id查询报警详情

 */

typedef struct GetAlarmMessageByIdRequest 
{
	LCOpenApiRequest base;

	struct GetAlarmMessageByIdRequestData
	{
		
		/** 告警消息ID */
		CSTR alarmId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]getAlarmMessageById */
		#define _STATIC_GetAlarmMessageByIdRequestData_method "getAlarmMessageById"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 消息类型 */
		CSTR msgType;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAlarmMessageByIdRequest;

C_API GetAlarmMessageByIdRequest *LCOPENAPI_INIT(GetAlarmMessageByIdRequest);

typedef struct GetAlarmMessageByIdResponse 
{
	LCOpenApiResponse base;

	struct GetAlarmMessageByIdResponseData
	{
		
		/** [long]报警消息ID */
		int64 alarmId;
		/** [long]报警时间UNIX时间戳秒 */
		int64 time;
		/** 缩略图url */
		CSTR thumbUrl;
		/** 报警图片url */
		DECLARE_LIST(CSTR) picurlArray;
		/** 通道号 */
		CSTR channelId;
		/** [String]消息类型,alarmPIR：人体红外；videoMotion：动态检测；wireLessDevLowPower：低电压告警 */
		CSTR msgType;
		/** 设备ID */
		CSTR deviceId;
 
	} data;

} GetAlarmMessageByIdResponse;

C_API GetAlarmMessageByIdResponse *LCOPENAPI_INIT(GetAlarmMessageByIdResponse);

#endif
