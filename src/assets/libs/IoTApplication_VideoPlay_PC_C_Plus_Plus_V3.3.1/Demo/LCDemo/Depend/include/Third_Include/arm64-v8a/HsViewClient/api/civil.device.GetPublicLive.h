/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPublicLive_H_
#define _HSVIEW_CLIENT_API_GetPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取摄像头公共视频。
【使用平台账号签名】
 */

typedef struct GetPublicLiveRequest 
{
	HsviewRequest base;

	struct GetPublicLiveRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPublicLiveRequest;

C_API GetPublicLiveRequest *HSAPI_INIT(GetPublicLiveRequest);

typedef struct GetPublicLiveResponse 
{
	HsviewResponse base;

	struct GetPublicLiveResponseData
	{
		
		/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示非公共视频。 */
		int64 publicExpire;
		/** 直播流hls访问地址 */
		CSTR url;
		/** 直播网页http地址 */
		CSTR page;
		/** 公开视频的token */
		CSTR token;
 
	} data;

} GetPublicLiveResponse;

C_API GetPublicLiveResponse *HSAPI_INIT(GetPublicLiveResponse);

#endif
