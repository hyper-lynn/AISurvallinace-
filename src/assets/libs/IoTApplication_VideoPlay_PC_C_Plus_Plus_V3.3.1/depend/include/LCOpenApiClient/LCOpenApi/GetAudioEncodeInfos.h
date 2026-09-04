/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221044, Author: 32500, Date: 2021-09-10 17:00:29 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAudioEncodeInfos_H_
#define _LC_OPENAPI_CLIENT_GetAudioEncodeInfos_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备音频编码能力集
 */

typedef struct GetAudioEncodeInfosRequest 
{
	LCOpenApiRequest base;

	struct GetAudioEncodeInfosRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAudioEncodeInfosRequest;

C_API GetAudioEncodeInfosRequest *LCOPENAPI_INIT(GetAudioEncodeInfosRequest);

typedef struct GetAudioEncodeInfosResponse 
{
	LCOpenApiResponse base;

	struct GetAudioEncodeInfosResponseData
	{
		
		/** define a list with struct of GetAudioEncodeInfosResponseData_EncodeInfosElement */
		DECLARE_LIST(struct GetAudioEncodeInfosResponseData_EncodeInfosElement
		{
			/** 编码格式，比如PCM，G711a，AMR，G711u，G726，AAC，OGG等 */
			CSTR encodeType;
			/** [int] 采样位数：8或16 */
			int bits;
			/** [int] 采样率：8000或16000 */
			int sampleRate;
		}) encodeInfos;
 
	} data;

} GetAudioEncodeInfosResponse;

C_API GetAudioEncodeInfosResponse *LCOPENAPI_INIT(GetAudioEncodeInfosResponse);

#endif
