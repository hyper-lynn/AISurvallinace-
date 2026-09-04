/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDoorbellMusicVolume_H_
#define _LC_OPENAPI_CLIENT_GetDoorbellMusicVolume_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取门铃的铃声音量
 */

typedef struct GetDoorbellMusicVolumeRequest 
{
	LCOpenApiRequest base;

	struct GetDoorbellMusicVolumeRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDoorbellMusicVolumeRequest;

C_API GetDoorbellMusicVolumeRequest *LCOPENAPI_INIT(GetDoorbellMusicVolumeRequest);

typedef struct GetDoorbellMusicVolumeResponse 
{
	LCOpenApiResponse base;

	struct GetDoorbellMusicVolumeResponseData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
 
	} data;

} GetDoorbellMusicVolumeResponse;

C_API GetDoorbellMusicVolumeResponse *LCOPENAPI_INIT(GetDoorbellMusicVolumeResponse);

#endif
