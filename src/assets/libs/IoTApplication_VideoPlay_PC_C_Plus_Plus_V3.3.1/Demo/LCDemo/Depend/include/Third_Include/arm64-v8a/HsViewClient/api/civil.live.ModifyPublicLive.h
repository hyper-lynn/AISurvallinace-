/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyPublicLive_H_
#define _HSVIEW_CLIENT_API_ModifyPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新摄像头直播分享的时间。
设备ID、通道号和token必须匹配对应。

当直播方式是设备device时，返回的结果中streamId才有效。
非设备方式，streamId无效。

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct ModifyPublicLiveRequest 
{
	HsviewRequest base;

	struct ModifyPublicLiveRequestData
	{
		
		/** [long]直播结束时间，UNIX时间戳，单位秒。必须设置为大于当前时间的有效时间 */
		int64 endTime;
		/** [long]直播开始时间，UNIX时间戳，单位秒 */
		int64 beginTime;
		/** 直播分享的token */
		CSTR token;
		/** [bool][O]直播的音频使能开关，默认为true */
		BOOL audioFlag;

	} data;

} ModifyPublicLiveRequest;

C_API ModifyPublicLiveRequest *HSAPI_INIT(ModifyPublicLiveRequest);

typedef struct ModifyPublicLiveResponse 
{
	HsviewResponse base;

	struct ModifyPublicLiveResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
		/** define a list with struct of ModifyPublicLiveResponseData_StreamsElement */
		DECLARE_LIST(struct ModifyPublicLiveResponseData_StreamsElement
		{
			/** [int] 0表示主码流，1表示辅码流,当前只针对device方式才有效 */
			int streamId;
			/** 直播流hls访问地址 */
			CSTR url;
			/** 直播实时视频的封面地址，为空表示没有开启实时封面 */
			CSTR coverUrl;
		}) streams;
 
	} data;

} ModifyPublicLiveResponse;

C_API ModifyPublicLiveResponse *HSAPI_INIT(ModifyPublicLiveResponse);

#endif
