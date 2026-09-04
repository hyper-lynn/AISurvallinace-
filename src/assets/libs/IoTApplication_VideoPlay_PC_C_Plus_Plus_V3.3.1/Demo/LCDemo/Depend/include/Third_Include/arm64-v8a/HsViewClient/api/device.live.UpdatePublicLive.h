/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLive_UpdatePublicLive_H_
#define _HSVIEW_CLIENT_API_deviceLive_UpdatePublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新直播分享的时间以及开关直播流。

【使用平台账号签名】
 */

typedef struct deviceLive_UpdatePublicLiveRequest 
{
	HsviewRequest base;

	struct deviceLive_UpdatePublicLiveRequestData
	{
		
		/** [O]直播分享的token */
		CSTR token;
		/** [long]直播分享的时间长度，单位秒 */
		int64 publicTime;
		/** [O][bool]直播使能,true表示打开直播,false表示暂停直播 */
		CSTR enable;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceLive_UpdatePublicLiveRequest;

C_API deviceLive_UpdatePublicLiveRequest *HSAPI_INIT(deviceLive_UpdatePublicLiveRequest);

typedef struct deviceLive_UpdatePublicLiveResponse 
{
	HsviewResponse base;

	struct deviceLive_UpdatePublicLiveResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
 
	} data;

} deviceLive_UpdatePublicLiveResponse;

C_API deviceLive_UpdatePublicLiveResponse *HSAPI_INIT(deviceLive_UpdatePublicLiveResponse);

#endif
