/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221382, Author: 27665, Date: 2021-10-21 14:31:47 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_StopDeviceAlarmSound_H_
#define _LC_OPENAPI_CLIENT_StopDeviceAlarmSound_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
消除设备告警音
 */

typedef struct StopDeviceAlarmSoundRequest 
{
	LCOpenApiRequest base;

	struct StopDeviceAlarmSoundRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} StopDeviceAlarmSoundRequest;

C_API StopDeviceAlarmSoundRequest *LCOPENAPI_INIT(StopDeviceAlarmSoundRequest);

typedef struct StopDeviceAlarmSoundResponse 
{
	LCOpenApiResponse base;

	struct StopDeviceAlarmSoundResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} StopDeviceAlarmSoundResponse;

C_API StopDeviceAlarmSoundResponse *LCOPENAPI_INIT(StopDeviceAlarmSoundResponse);

#endif
