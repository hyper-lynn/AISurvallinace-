/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdatePlayTimes_H_
#define _HSVIEW_CLIENT_API_UpdatePlayTimes_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新直播活动中当前直播通道源的播放次数。
每次客户端在点击播放直播通道源时调用此接口。
调用1次，播放次数就会加1。
返回当前活动总的播放次数，以及所有直播源的token和对应的播放次数。

错误码：
1、1504 ：直播活动不存在
2、1502 : 视频直播源不存在

【不鉴权】
 */

typedef struct UpdatePlayTimesRequest 
{
	HsviewRequest base;

	struct UpdatePlayTimesRequestData
	{
		
		/** [long]活动id */
		int64 activityId;
		/** 直播源token */
		CSTR token;

	} data;

} UpdatePlayTimesRequest;

C_API UpdatePlayTimesRequest *HSAPI_INIT(UpdatePlayTimesRequest);

typedef struct UpdatePlayTimesResponse 
{
	HsviewResponse base;

	struct UpdatePlayTimesResponseData
	{
		
		/** [int]播放次数 */
		int playTimes;
		/** define a list with struct of UpdatePlayTimesResponseData_LivesElement */
		DECLARE_LIST(struct UpdatePlayTimesResponseData_LivesElement
		{
			/** 直播源的token */
			CSTR token;
			/** [int]当前直播通道的播放次数 */
			int playTimes;
		}) lives;
 
	} data;

} UpdatePlayTimesResponse;

C_API UpdatePlayTimesResponse *HSAPI_INIT(UpdatePlayTimesResponse);

#endif
