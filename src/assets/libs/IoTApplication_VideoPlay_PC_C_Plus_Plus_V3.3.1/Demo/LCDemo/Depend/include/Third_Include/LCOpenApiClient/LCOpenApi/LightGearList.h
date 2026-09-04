/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LightGearList_H_
#define _LC_OPENAPI_CLIENT_LightGearList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取灯类设备的档位信息
 */

typedef struct LightGearListRequest 
{
	LCOpenApiRequest base;

	struct LightGearListRequestData
	{
		
		/** 档位类型数组 */
		DECLARE_LIST(CSTR) type;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} LightGearListRequest;

C_API LightGearListRequest *LCOPENAPI_INIT(LightGearListRequest);

typedef struct LightGearListResponse 
{
	LCOpenApiResponse base;

	struct LightGearListResponseData
	{
		
		/** define a list with struct of LightGearListResponseData_GearElement */
		DECLARE_LIST(struct LightGearListResponseData_GearElement
		{
			/** 档位值 */
			CSTR value;
			/** 档位类型 */
			CSTR type;
		}) gear;
 
	} data;

} LightGearListResponse;

C_API LightGearListResponse *LCOPENAPI_INIT(LightGearListResponse);

#endif
