/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdatePublicLive_H_
#define _HSVIEW_CLIENT_API_UpdatePublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新公共视频的到期时间。
若修改成非公共视频，则返回字段url和page都为空。
【使用平台账号签名】
 */

typedef struct UpdatePublicLiveRequest 
{
	HsviewRequest base;

	struct UpdatePublicLiveRequestData
	{
		
		/** 公开视频的token */
		CSTR token;
		/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
		int64 publicExpire;

	} data;

} UpdatePublicLiveRequest;

C_API UpdatePublicLiveRequest *HSAPI_INIT(UpdatePublicLiveRequest);

typedef struct UpdatePublicLiveResponse 
{
	HsviewResponse base;

	struct UpdatePublicLiveResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
		/** 直播流hls访问地址 */
		CSTR url;
 
	} data;

} UpdatePublicLiveResponse;

C_API UpdatePublicLiveResponse *HSAPI_INIT(UpdatePublicLiveResponse);

#endif
