/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_EnablePublicLive_H_
#define _HSVIEW_CLIENT_API_EnablePublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
使能直播，将直播设置为打开或者暂停状态。

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct EnablePublicLiveRequest 
{
	HsviewRequest base;

	struct EnablePublicLiveRequestData
	{
		
		/** [bool]直播使能,true表示打开直播,false表示暂停直播 */
		BOOL enable;
		/** [O]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** 直播分享的token */
		CSTR token;
		/** [O]所属平台 open:开放平台 base:乐橙平台 */
		CSTR ownerType;

	} data;

} EnablePublicLiveRequest;

C_API EnablePublicLiveRequest *HSAPI_INIT(EnablePublicLiveRequest);

typedef struct EnablePublicLiveResponse 
{
	HsviewResponse base;

	struct EnablePublicLiveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} EnablePublicLiveResponse;

C_API EnablePublicLiveResponse *HSAPI_INIT(EnablePublicLiveResponse);

#endif
