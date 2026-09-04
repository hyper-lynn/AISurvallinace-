/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_DeleteAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除用户的报警消息

 */

typedef struct DeleteAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct DeleteAlarmMessageRequestData
	{
		
		/** [cstr]deleteAlarmMessage */
		#define _STATIC_DeleteAlarmMessageRequestData_method "deleteAlarmMessage"
		CSTR method;
		/** [String]设备ID */
		CSTR deviceId;
		/** [String]通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [long]报警消息ID */
		int64 indexId;

	} data;

} DeleteAlarmMessageRequest;

C_API DeleteAlarmMessageRequest *LCOPENAPI_INIT(DeleteAlarmMessageRequest);

typedef struct DeleteAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct DeleteAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteAlarmMessageResponse;

C_API DeleteAlarmMessageResponse *LCOPENAPI_INIT(DeleteAlarmMessageResponse);

#endif
