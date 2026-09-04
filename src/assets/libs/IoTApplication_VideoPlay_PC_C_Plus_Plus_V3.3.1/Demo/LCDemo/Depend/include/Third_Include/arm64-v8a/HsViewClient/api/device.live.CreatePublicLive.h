/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLive_CreatePublicLive_H_
#define _HSVIEW_CLIENT_API_deviceLive_CreatePublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建直播分享。

page格式如下：http://www.lechange.cn/civil/share/index.html?domain=www.lechange.cn&appId=lechange_weixinappid&id=token&type=live

【使用平台账号签名】
 */

typedef struct deviceLive_CreatePublicLiveRequest 
{
	HsviewRequest base;

	struct deviceLive_CreatePublicLiveRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** [long]直播分享的时间长度，单位秒 */
		int64 publicTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceLive_CreatePublicLiveRequest;

C_API deviceLive_CreatePublicLiveRequest *HSAPI_INIT(deviceLive_CreatePublicLiveRequest);

typedef struct deviceLive_CreatePublicLiveResponse 
{
	HsviewResponse base;

	struct deviceLive_CreatePublicLiveResponseData
	{
		
		/** 直播网页地址 */
		CSTR page;
 
	} data;

} deviceLive_CreatePublicLiveResponse;

C_API deviceLive_CreatePublicLiveResponse *HSAPI_INIT(deviceLive_CreatePublicLiveResponse);

#endif
