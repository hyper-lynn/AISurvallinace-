/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDoorbellMusicVolume_H_
#define _LC_OPENAPI_CLIENT_SetDoorbellMusicVolume_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置门铃的铃声音量
 */

typedef struct SetDoorbellMusicVolumeRequest 
{
	LCOpenApiRequest base;

	struct SetDoorbellMusicVolumeRequestData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDoorbellMusicVolumeRequest;

C_API SetDoorbellMusicVolumeRequest *LCOPENAPI_INIT(SetDoorbellMusicVolumeRequest);

typedef struct SetDoorbellMusicVolumeResponse 
{
	LCOpenApiResponse base;

	struct SetDoorbellMusicVolumeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDoorbellMusicVolumeResponse;

C_API SetDoorbellMusicVolumeResponse *LCOPENAPI_INIT(SetDoorbellMusicVolumeResponse);

#endif
