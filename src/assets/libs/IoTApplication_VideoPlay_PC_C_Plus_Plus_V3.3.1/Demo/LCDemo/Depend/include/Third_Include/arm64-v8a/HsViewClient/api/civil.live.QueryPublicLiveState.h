/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicLiveState_H_
#define _HSVIEW_CLIENT_API_QueryPublicLiveState_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新摄像头直播分享的时间。
设备ID、通道号和token必须匹配对应。
直播的状态：
0:正在直播中,
1:正在直播中，但是视频封面异常,
2:视频源异常,
3:码流转换异常,
4:云存储访问异常,
5:直播未开始,
10:直播暂停中,
11:设备离线(视频源是设备device才会有这个状态)

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicLiveStateRequest 
{
	HsviewRequest base;

	struct QueryPublicLiveStateRequestData
	{
		
		/** 直播分享的token */
		CSTR token;

	} data;

} QueryPublicLiveStateRequest;

C_API QueryPublicLiveStateRequest *HSAPI_INIT(QueryPublicLiveStateRequest);

typedef struct QueryPublicLiveStateResponse 
{
	HsviewResponse base;

	struct QueryPublicLiveStateResponseData
	{
		
		/** 直播网页http地址 */
		CSTR page;
		/** define a list with struct of QueryPublicLiveStateResponseData_StreamsElement */
		DECLARE_LIST(struct QueryPublicLiveStateResponseData_StreamsElement
		{
			/** [int] 0表示主码流，1表示辅码流 */
			int streamId;
			/** 直播流hls访问地址 */
			CSTR url;
			/** 状态,0:正在直播中,1:正在直播中，但是视频封面异常,2:视频源异常,3:码流转换异常,4:云存储访问异常,5:直播未开始,10:直播暂停中,11:设备离线 */
			CSTR state;
		}) streams;
 
	} data;

} QueryPublicLiveStateResponse;

C_API QueryPublicLiveStateResponse *HSAPI_INIT(QueryPublicLiveStateResponse);

#endif
