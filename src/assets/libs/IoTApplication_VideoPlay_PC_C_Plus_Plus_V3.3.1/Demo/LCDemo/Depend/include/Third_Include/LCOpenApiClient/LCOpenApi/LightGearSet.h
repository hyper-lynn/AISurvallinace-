/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LightGearSet_H_
#define _LC_OPENAPI_CLIENT_LightGearSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置灯类设备的档位
 */

typedef struct LightGearSetRequest 
{
	LCOpenApiRequest base;

	struct LightGearSetRequestData
	{
		
		/** 档位类型数组 */
		CSTR type;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 档位值 */
		CSTR value;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} LightGearSetRequest;

C_API LightGearSetRequest *LCOPENAPI_INIT(LightGearSetRequest);

typedef struct LightGearSetResponse 
{
	LCOpenApiResponse base;

	struct LightGearSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} LightGearSetResponse;

C_API LightGearSetResponse *LCOPENAPI_INIT(LightGearSetResponse);

#endif
