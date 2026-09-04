/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetLiveActivities_H_
#define _HSVIEW_CLIENT_API_GetLiveActivities_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取发现页推荐直播列表

【不鉴权】
 */

typedef struct GetLiveActivitiesRequest 
{
	HsviewRequest base;

	struct GetLiveActivitiesRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetLiveActivitiesRequest;

C_API GetLiveActivitiesRequest *HSAPI_INIT(GetLiveActivitiesRequest);

typedef struct GetLiveActivitiesResponse 
{
	HsviewResponse base;

	struct GetLiveActivitiesResponseData
	{
		
		/** define a list with struct of GetLiveActivitiesResponseData_ActivitiesElement */
		DECLARE_LIST(struct GetLiveActivitiesResponseData_ActivitiesElement
		{
			/** [int]直播类型, 0:即将直播，1:正在直播，2:历史直播 */
			int type;
			/** 活动名称 */
			CSTR name;
			/** 活动封面地址 */
			CSTR coverUrl;
			/** [long]活动id */
			int64 activityId;
			/** [int]播放次数 */
			int playTimes;
		}) activities;
 
	} data;

} GetLiveActivitiesResponse;

C_API GetLiveActivitiesResponse *HSAPI_INIT(GetLiveActivitiesResponse);

#endif
