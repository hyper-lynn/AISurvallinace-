/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicLive_H_
#define _HSVIEW_CLIENT_API_QueryPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取摄像头直播分享。
当直播方式是设备device时，返回的结果中streamId才会有效。
非设备方式，streamId无效。

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicLiveRequest 
{
	HsviewRequest base;

	struct QueryPublicLiveRequestData
	{
		
		/** 直播分享的token */
		CSTR token;

	} data;

} QueryPublicLiveRequest;

C_API QueryPublicLiveRequest *HSAPI_INIT(QueryPublicLiveRequest);

typedef struct QueryPublicLiveResponse 
{
	HsviewResponse base;

	struct QueryPublicLiveResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
		/** define a list with struct of QueryPublicLiveResponseData_StreamsElement */
		DECLARE_LIST(struct QueryPublicLiveResponseData_StreamsElement
		{
			/** [int] 0表示主码流，1表示辅码流,当前只针对device方式才有效 */
			int streamId;
			/** 直播流hls访问地址 */
			CSTR url;
			/** 直播实时视频的封面地址，为空表示没有开启实时封面 */
			CSTR coverUrl;
		}) streams;
 
	} data;

} QueryPublicLiveResponse;

C_API QueryPublicLiveResponse *HSAPI_INIT(QueryPublicLiveResponse);

#endif
