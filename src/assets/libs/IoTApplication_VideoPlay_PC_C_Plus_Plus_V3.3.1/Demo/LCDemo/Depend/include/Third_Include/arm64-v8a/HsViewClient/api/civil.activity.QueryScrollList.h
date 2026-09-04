/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryScrollList_H_
#define _HSVIEW_CLIENT_API_QueryScrollList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取滚屏的文章或活动列表

【不鉴权】
 */

typedef struct QueryScrollListRequest 
{
	HsviewRequest base;

	struct QueryScrollListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} QueryScrollListRequest;

C_API QueryScrollListRequest *HSAPI_INIT(QueryScrollListRequest);

typedef struct QueryScrollListResponse 
{
	HsviewResponse base;

	struct QueryScrollListResponseData
	{
		
		/** define a list with struct of QueryScrollListResponseData_ActivitiesElement */
		DECLARE_LIST(struct QueryScrollListResponseData_ActivitiesElement
		{
			/** [int]类型, 1:直播活动，2：资讯文章，3：投稿活动，4：试用活动，5：线下活动 */
			int type;
			/** 活动名称 */
			CSTR name;
			/** 活动封面地址 */
			CSTR coverUrl;
			/** [long]活动id */
			int64 activityId;
			/** 活动的页面url */
			CSTR url;
			/** [int]播放次数 */
			int playTimes;
		}) activities;
 
	} data;

} QueryScrollListResponse;

C_API QueryScrollListResponse *HSAPI_INIT(QueryScrollListResponse);

#endif
