/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_OtherRingTypeNotify_H_
#define _LC_OPENAPI_CLIENT_OtherRingTypeNotify_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
通知门铃第三方铃铛类型
 */

typedef struct OtherRingTypeNotifyRequest 
{
	LCOpenApiRequest base;

	struct OtherRingTypeNotifyRequestData
	{
		
		/** [int]第三方铃铛的类型,0 未接，默认0、1 机械、2 电子 */
		int type;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 响铃的时间 */
		CSTR ringtime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} OtherRingTypeNotifyRequest;

C_API OtherRingTypeNotifyRequest *LCOPENAPI_INIT(OtherRingTypeNotifyRequest);

typedef struct OtherRingTypeNotifyResponse 
{
	LCOpenApiResponse base;

	struct OtherRingTypeNotifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} OtherRingTypeNotifyResponse;

C_API OtherRingTypeNotifyResponse *LCOPENAPI_INIT(OtherRingTypeNotifyResponse);

#endif
