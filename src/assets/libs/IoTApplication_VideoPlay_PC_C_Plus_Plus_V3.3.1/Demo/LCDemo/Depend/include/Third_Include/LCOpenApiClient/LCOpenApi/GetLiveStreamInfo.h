/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetLiveStreamInfo_H_
#define _LC_OPENAPI_CLIENT_GetLiveStreamInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据序列号获取直播地址和直播状态
 */

typedef struct GetLiveStreamInfoRequest 
{
	LCOpenApiRequest base;

	struct GetLiveStreamInfoRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetLiveStreamInfoRequest;

C_API GetLiveStreamInfoRequest *LCOPENAPI_INIT(GetLiveStreamInfoRequest);

typedef struct GetLiveStreamInfoResponse 
{
	LCOpenApiResponse base;

	struct GetLiveStreamInfoResponseData
	{
		
		/** define a list with struct of GetLiveStreamInfoResponseData_StreamsElement */
		DECLARE_LIST(struct GetLiveStreamInfoResponseData_StreamsElement
		{
			/** [int]码流类型（0:主码流；1:辅码流） */
			int streamId;
			/** 直播的token */
			CSTR liveToken;
			/** 状态 */
			CSTR status;
			/** 直播流hls访问地址 */
			CSTR hls;
		}) streams;
 
	} data;

} GetLiveStreamInfoResponse;

C_API GetLiveStreamInfoResponse *LCOPENAPI_INIT(GetLiveStreamInfoResponse);

#endif
