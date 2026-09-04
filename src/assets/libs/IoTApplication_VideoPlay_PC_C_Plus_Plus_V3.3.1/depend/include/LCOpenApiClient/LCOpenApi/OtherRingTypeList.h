/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_OtherRingTypeList_H_
#define _LC_OPENAPI_CLIENT_OtherRingTypeList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取第三方铃铛类型
 */

typedef struct OtherRingTypeListRequest 
{
	LCOpenApiRequest base;

	struct OtherRingTypeListRequestData
	{
		
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} OtherRingTypeListRequest;

C_API OtherRingTypeListRequest *LCOPENAPI_INIT(OtherRingTypeListRequest);

typedef struct OtherRingTypeListResponse 
{
	LCOpenApiResponse base;

	struct OtherRingTypeListResponseData
	{
		
		/** 可选,响铃的时间 */
		CSTR ringtime;
		/** [int]第三方铃铛的类型,0 未接，默认0、1 机械、2 电子 */
		int type;
 
	} data;

} OtherRingTypeListResponse;

C_API OtherRingTypeListResponse *LCOPENAPI_INIT(OtherRingTypeListResponse);

#endif
