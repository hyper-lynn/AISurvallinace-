/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221031, Author: 21818, Date: 2021-09-09 19:24:33 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAudioTalkUrl_H_
#define _LC_OPENAPI_CLIENT_GetAudioTalkUrl_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取语音对讲地址
 */

typedef struct GetAudioTalkUrlRequest 
{
	LCOpenApiRequest base;

	struct GetAudioTalkUrlRequestData
	{
		
		/** [int]资源有效期 */
		int duration;
		/** 设备ID */
		CSTR deviceId;
		/** url类型，pull或者push，默认为pull */
		CSTR urlType;
		/** [int]采样位数，8或16 */
		int bits;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [bool]知否需要重定向 */
		BOOL locationEnable;
		/** 音频编码格式，比如PCM，G711a，AMR，G711u，G726，AAC，OGG等 */
		CSTR encodeType;
		/** 通道编号，字符串类型，通道对讲必填 */
		CSTR channelId;
		/** [int]采样率，8000或16000 */
		int sampleRate;
		/** 补充URI信息，deviceTalk为设备对讲，channelTalk为通道对讲 */
		CSTR appendUrl;

	} data;

} GetAudioTalkUrlRequest;

C_API GetAudioTalkUrlRequest *LCOPENAPI_INIT(GetAudioTalkUrlRequest);

typedef struct GetAudioTalkUrlResponse 
{
	LCOpenApiResponse base;

	struct GetAudioTalkUrlResponseData
	{
		
		/** 返回的rtsp地址 */
		CSTR url;
 
	} data;

} GetAudioTalkUrlResponse;

C_API GetAudioTalkUrlResponse *LCOPENAPI_INIT(GetAudioTalkUrlResponse);

#endif
