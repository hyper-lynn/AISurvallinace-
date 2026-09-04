/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteDeviceAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_DeleteDeviceAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据报警消息ID批量删除报警消息
 */

typedef struct DeleteDeviceAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct DeleteDeviceAlarmMessageRequestData
	{
		
		/** [long]报警消息ID数组 */
		DECLARE_LIST(int64) alarmId;
		/** 通道序列号 */
		CSTR channelId;
		/** 授权token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeleteDeviceAlarmMessageRequest;

C_API DeleteDeviceAlarmMessageRequest *LCOPENAPI_INIT(DeleteDeviceAlarmMessageRequest);

typedef struct DeleteDeviceAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct DeleteDeviceAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteDeviceAlarmMessageResponse;

C_API DeleteDeviceAlarmMessageResponse *LCOPENAPI_INIT(DeleteDeviceAlarmMessageResponse);

#endif
