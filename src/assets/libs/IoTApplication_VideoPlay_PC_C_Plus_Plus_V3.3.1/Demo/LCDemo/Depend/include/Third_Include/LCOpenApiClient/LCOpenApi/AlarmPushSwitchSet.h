/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AlarmPushSwitchSet_H_
#define _LC_OPENAPI_CLIENT_AlarmPushSwitchSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备推送提醒开关
 */

typedef struct AlarmPushSwitchSetRequest 
{
	LCOpenApiRequest base;

	struct AlarmPushSwitchSetRequestData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
		/** [O]通道号 */
		CSTR channelId;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} AlarmPushSwitchSetRequest;

C_API AlarmPushSwitchSetRequest *LCOPENAPI_INIT(AlarmPushSwitchSetRequest);

typedef struct AlarmPushSwitchSetResponse 
{
	LCOpenApiResponse base;

	struct AlarmPushSwitchSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AlarmPushSwitchSetResponse;

C_API AlarmPushSwitchSetResponse *LCOPENAPI_INIT(AlarmPushSwitchSetResponse);

#endif
