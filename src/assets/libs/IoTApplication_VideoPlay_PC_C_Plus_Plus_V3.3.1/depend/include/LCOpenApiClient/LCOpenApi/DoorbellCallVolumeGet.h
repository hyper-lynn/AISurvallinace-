/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallVolumeGet_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallVolumeGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取门铃的通话音量
 */

typedef struct DoorbellCallVolumeGetRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallVolumeGetRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellCallVolumeGetRequest;

C_API DoorbellCallVolumeGetRequest *LCOPENAPI_INIT(DoorbellCallVolumeGetRequest);

typedef struct DoorbellCallVolumeGetResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallVolumeGetResponseData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
 
	} data;

} DoorbellCallVolumeGetResponse;

C_API DoorbellCallVolumeGetResponse *LCOPENAPI_INIT(DoorbellCallVolumeGetResponse);

#endif
