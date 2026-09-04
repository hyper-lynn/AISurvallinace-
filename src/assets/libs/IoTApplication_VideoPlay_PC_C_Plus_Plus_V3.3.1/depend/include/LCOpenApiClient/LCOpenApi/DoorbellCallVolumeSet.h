/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallVolumeSet_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallVolumeSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置门铃的通话音量
 */

typedef struct DoorbellCallVolumeSetRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallVolumeSetRequestData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
		/** 门铃设备序列号 */
		CSTR deviceId ;
		/** 授权的token */
		CSTR token;

	} data;

} DoorbellCallVolumeSetRequest;

C_API DoorbellCallVolumeSetRequest *LCOPENAPI_INIT(DoorbellCallVolumeSetRequest);

typedef struct DoorbellCallVolumeSetResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallVolumeSetResponseData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
 
	} data;

} DoorbellCallVolumeSetResponse;

C_API DoorbellCallVolumeSetResponse *LCOPENAPI_INIT(DoorbellCallVolumeSetResponse);

#endif
