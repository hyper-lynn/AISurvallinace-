/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLive_DelPublicLive_H_
#define _HSVIEW_CLIENT_API_deviceLive_DelPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
关闭直播分享。


【使用平台账号签名】
 */

typedef struct deviceLive_DelPublicLiveRequest 
{
	HsviewRequest base;

	struct deviceLive_DelPublicLiveRequestData
	{
		
		/** [O]直播分享的token */
		CSTR token;
		/** 通道号 */
		CSTR channelId;
		/** [O]项目ID,app为LC,开放平台为LCO,不传则代表LC */
		CSTR pid;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceLive_DelPublicLiveRequest;

C_API deviceLive_DelPublicLiveRequest *HSAPI_INIT(deviceLive_DelPublicLiveRequest);

typedef struct deviceLive_DelPublicLiveResponse 
{
	HsviewResponse base;

	struct deviceLive_DelPublicLiveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceLive_DelPublicLiveResponse;

C_API deviceLive_DelPublicLiveResponse *HSAPI_INIT(deviceLive_DelPublicLiveResponse);

#endif
