/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetRecommendList_H_
#define _HSVIEW_CLIENT_API_GetRecommendList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取推荐的活动列表。
need值：暂时不关心，只取最近5条。


当type为0时，表示直播活动，activityId为直播活动id。
当type为1时，表示普通网页，activityId为普通网页链接URL。

当项目类型为X项目时，activityType有效。

【不鉴权】
 */

typedef struct GetRecommendListRequest 
{
	HsviewRequest base;

	struct GetRecommendListRequestData
	{
		
		/** 分页获取,从第几条到第几条，如[1-100],闭区间,最多一次查询100条 */
		CSTR need;

	} data;

} GetRecommendListRequest;

C_API GetRecommendListRequest *HSAPI_INIT(GetRecommendListRequest);

typedef struct GetRecommendListResponse 
{
	HsviewResponse base;

	struct GetRecommendListResponseData
	{
		
		/** define a list with struct of GetRecommendListResponseData_ActivitiesElement */
		DECLARE_LIST(struct GetRecommendListResponseData_ActivitiesElement
		{
			/** [int]推荐类型：0-自己创建的活动  1-普通网页 */
			int type;
			/** 活动名称 */
			CSTR name;
			/** 活动封面的url */
			CSTR coverUrl;
			/** 活动标识 */
			CSTR activityId;
			/** [int][O]活动类型：1-活动 2-文章 */
			int activityType;
		}) activities;
 
	} data;

} GetRecommendListResponse;

C_API GetRecommendListResponse *HSAPI_INIT(GetRecommendListResponse);

#endif
