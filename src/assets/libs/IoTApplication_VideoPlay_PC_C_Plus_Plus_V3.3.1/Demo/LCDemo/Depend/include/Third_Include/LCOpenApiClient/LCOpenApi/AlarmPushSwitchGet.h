/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AlarmPushSwitchGet_H_
#define _LC_OPENAPI_CLIENT_AlarmPushSwitchGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备推送提醒开关
 */

typedef struct AlarmPushSwitchGetRequest 
{
	LCOpenApiRequest base;

	struct AlarmPushSwitchGetRequestData
	{
		
		/** [O]通道号 */
		CSTR channelId;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} AlarmPushSwitchGetRequest;

C_API AlarmPushSwitchGetRequest *LCOPENAPI_INIT(AlarmPushSwitchGetRequest);

typedef struct AlarmPushSwitchGetResponse 
{
	LCOpenApiResponse base;

	struct AlarmPushSwitchGetResponseData
	{
		
		/** [bool]是否有效 */
		BOOL enable;
 
	} data;

} AlarmPushSwitchGetResponse;

C_API AlarmPushSwitchGetResponse *LCOPENAPI_INIT(AlarmPushSwitchGetResponse);

#endif
