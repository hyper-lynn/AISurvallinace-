/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLive_GetPublicLive_H_
#define _HSVIEW_CLIENT_API_deviceLive_GetPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取直播分享信息。

【使用平台账号签名】
 */

typedef struct deviceLive_GetPublicLiveRequest 
{
	HsviewRequest base;

	struct deviceLive_GetPublicLiveRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** [O]直播分享的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceLive_GetPublicLiveRequest;

C_API deviceLive_GetPublicLiveRequest *HSAPI_INIT(deviceLive_GetPublicLiveRequest);

typedef struct deviceLive_GetPublicLiveResponse 
{
	HsviewResponse base;

	struct deviceLive_GetPublicLiveResponseData
	{
		
		/** define a list with struct of deviceLive_GetPublicLiveResponseData_StreamsElement */
		DECLARE_LIST(struct deviceLive_GetPublicLiveResponseData_StreamsElement
		{
			/** [int] 0表示主码流，1表示辅码流 */
			int streamId;
			/** 直播流hls访问地址 */
			CSTR url;
			/** 状态,0:正在直播中,1:正在直播中，但是视频封面异常,2:视频源异常,3:码流转换异常,4:云存储访问异常,5:直播未开始,10:直播暂停中,11:设备离线 */
			CSTR state;
		}) streams;
		/** 直播网页地址 */
		CSTR page;
		/** [long]直播分享的剩余时间，单位秒 */
		int64 publicTime;
 
	} data;

} deviceLive_GetPublicLiveResponse;

C_API deviceLive_GetPublicLiveResponse *HSAPI_INIT(deviceLive_GetPublicLiveResponse);

#endif
