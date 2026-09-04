/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPublicLiveStream_H_
#define _HSVIEW_CLIENT_API_GetPublicLiveStream_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取公共视频直播流，返回HLS的http地址。
设备ID、通道号和token必须匹配对应。
注：本接口无需签名认证。使用者只能拉取设置为公共视频的设备的直播流。拉取个人设备的直播流将会返回错误。
【无需签名认证】
 */

typedef struct GetPublicLiveStreamRequest 
{
	HsviewRequest base;

	struct GetPublicLiveStreamRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 公开视频的token */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPublicLiveStreamRequest;

C_API GetPublicLiveStreamRequest *HSAPI_INIT(GetPublicLiveStreamRequest);

typedef struct GetPublicLiveStreamResponse 
{
	HsviewResponse base;

	struct GetPublicLiveStreamResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
		/** 直播流hls访问地址 */
		CSTR url;
 
	} data;

} GetPublicLiveStreamResponse;

C_API GetPublicLiveStreamResponse *HSAPI_INIT(GetPublicLiveStreamResponse);

#endif
