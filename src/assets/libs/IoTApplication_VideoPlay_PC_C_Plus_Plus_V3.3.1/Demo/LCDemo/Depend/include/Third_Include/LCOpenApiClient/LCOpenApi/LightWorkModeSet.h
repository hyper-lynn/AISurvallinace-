/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LightWorkModeSet_H_
#define _LC_OPENAPI_CLIENT_LightWorkModeSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
探照灯模式设置
 */

typedef struct LightWorkModeSetRequest 
{
	LCOpenApiRequest base;

	struct LightWorkModeSetRequestData
	{
		
		/** 为空或floodlight表示设置探照灯的工作模式 */
		CSTR type;
		/** 探照灯模式对应的索引值，有效值大于等于0 */
		CSTR index;
		/** 通道。为空为设备级操作（需要设备支持通道探照灯能力 ChanSearchLight）；不为空则为通道级操作 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} LightWorkModeSetRequest;

C_API LightWorkModeSetRequest *LCOPENAPI_INIT(LightWorkModeSetRequest);

typedef struct LightWorkModeSetResponse 
{
	LCOpenApiResponse base;

	struct LightWorkModeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} LightWorkModeSetResponse;

C_API LightWorkModeSetResponse *LCOPENAPI_INIT(LightWorkModeSetResponse);

#endif
