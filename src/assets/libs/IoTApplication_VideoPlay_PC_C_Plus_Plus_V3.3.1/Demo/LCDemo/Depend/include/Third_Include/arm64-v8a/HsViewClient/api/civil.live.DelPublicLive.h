/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelPublicLive_H_
#define _HSVIEW_CLIENT_API_DelPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除摄像头直播分享。

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct DelPublicLiveRequest 
{
	HsviewRequest base;

	struct DelPublicLiveRequestData
	{
		
		/** 直播分享的token */
		CSTR token;

	} data;

} DelPublicLiveRequest;

C_API DelPublicLiveRequest *HSAPI_INIT(DelPublicLiveRequest);

typedef struct DelPublicLiveResponse 
{
	HsviewResponse base;

	struct DelPublicLiveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelPublicLiveResponse;

C_API DelPublicLiveResponse *HSAPI_INIT(DelPublicLiveResponse);

#endif
