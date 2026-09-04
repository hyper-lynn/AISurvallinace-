/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetActivityList_H_
#define _HSVIEW_CLIENT_API_GetActivityList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取活动列表

【不鉴权】
 */

typedef struct GetActivityListRequest 
{
	HsviewRequest base;

	struct GetActivityListRequestData
	{
		
		/** 分页获取,从第几条到第几条，如[1-100],闭区间,最多一次查询100条 */
		CSTR need;
		/** [int]直播类型, 0:即将直播，1:正在直播，2:历史直播 */
		int type;

	} data;

} GetActivityListRequest;

C_API GetActivityListRequest *HSAPI_INIT(GetActivityListRequest);

typedef struct GetActivityListResponse 
{
	HsviewResponse base;

	struct GetActivityListResponseData
	{
		
		/** define a list with struct of GetActivityListResponseData_ActivitiesElement */
		DECLARE_LIST(struct GetActivityListResponseData_ActivitiesElement
		{
			/** [long]活动id */
			int64 activityId;
			/** [int]播放次数 */
			int playTimes;
			/** 活动名称 */
			CSTR name;
			/** 活动封面地址 */
			CSTR coverUrl;
		}) activities;
 
	} data;

} GetActivityListResponse;

C_API GetActivityListResponse *HSAPI_INIT(GetActivityListResponse);

#endif
