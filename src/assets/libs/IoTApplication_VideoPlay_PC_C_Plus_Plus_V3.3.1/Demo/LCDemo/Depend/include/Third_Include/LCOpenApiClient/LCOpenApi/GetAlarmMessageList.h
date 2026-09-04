/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 224466, Author: 34944, Date: 2023-04-28 09:34:33 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAlarmMessageList_H_
#define _LC_OPENAPI_CLIENT_GetAlarmMessageList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询报警图片列表

 */

typedef struct GetAlarmMessageListRequest 
{
	LCOpenApiRequest base;

	struct GetAlarmMessageListRequestData
	{
		
		/** define a list with struct of GetAlarmMessageListRequestData_DeviceListElement */
		DECLARE_LIST(struct GetAlarmMessageListRequestData_DeviceListElement
		{
			/** 报警事件ID */
			CSTR alarmId;
			/** 设备Id */
			CSTR deviceId;
		}) deviceList;
		/** [cstr]listAlarmMessageByIds */
		#define _STATIC_GetAlarmMessageListRequestData_method "listAlarmMessageByIds"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GetAlarmMessageListRequest;

C_API GetAlarmMessageListRequest *LCOPENAPI_INIT(GetAlarmMessageListRequest);

typedef struct GetAlarmMessageListResponse 
{
	LCOpenApiResponse base;

	struct GetAlarmMessageListResponseData
	{
		
		/** define a list with struct of GetAlarmMessageListResponseData_MessageListElement */
		DECLARE_LIST(struct GetAlarmMessageListResponseData_MessageListElement
		{
			/** 报警事件ID */
			CSTR alarmId;
			/** 缩略图 */
			CSTR thumbUrl;
			/** 封面图 */
			DECLARE_LIST(CSTR) picUrl;
			/** 设备Id */
			CSTR deviceId;
		}) messageList;
 
	} data;

} GetAlarmMessageListResponse;

C_API GetAlarmMessageListResponse *LCOPENAPI_INIT(GetAlarmMessageListResponse);

#endif
