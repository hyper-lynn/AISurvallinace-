/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryActivityList_H_
#define _HSVIEW_CLIENT_API_QueryActivityList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取活动列表

【不鉴权】
 */

typedef struct QueryActivityListRequest 
{
	HsviewRequest base;

	struct QueryActivityListRequestData
	{
		
		/** 分页获取,从第几条到第几条，如[1-100],闭区间,最多一次查询100条 */
		CSTR need;
		/** [O]活动对应的地区 */
		CSTR area;
		/** [int][O]活动适合年龄（单位为月） */
		int age;
		/** [int]类型, 1:直播活动，2：资讯文章，3：投稿活动，4：试用活动，5：线下活动 */
		DECLARE_LIST(int) types;

	} data;

} QueryActivityListRequest;

C_API QueryActivityListRequest *HSAPI_INIT(QueryActivityListRequest);

typedef struct QueryActivityListResponse 
{
	HsviewResponse base;

	struct QueryActivityListResponseData
	{
		
		/** define a list with struct of QueryActivityListResponseData_ActivitiesElement */
		DECLARE_LIST(struct QueryActivityListResponseData_ActivitiesElement
		{
			/** [long]文章或活动的发布时间。Unix时间（单位秒） */
			int64 publishTime;
			/** [long]活动id */
			int64 activityId;
			/** [int]播放次数 */
			int playTimes;
			/** [int][O]活动状态 2-进行中，3-已结束 */
			int status;
			/** [long][O]开始时间。Unix时间（单位秒） */
			int64 beginTime;
			/** [O]活动适应的地区信息，多个以逗号分开 */
			CSTR area;
			/** [int]类型, 1:直播活动，2：资讯文章，3：投稿活动，4：试用活动，5：线下活动 */
			int type;
			/** [long]点赞数 */
			int64 likeTimes;
			/** [long][O]结束时间。Unix时间（单位秒） */
			int64 endTime;
			/** [O]活动或文章适合的年龄,格式如：1-24（单位为月） */
			CSTR age;
			/** [long][O]参加用户数 */
			int64 joinNum;
			/** 活动名称 */
			CSTR name;
			/** 活动封面地址 */
			CSTR coverUrl;
			/** 活动的页面url */
			CSTR url;
			/** 文章或活动的概述 */
			CSTR summary;
			/** [long][O]阅读数 */
			int64 readTimes;
			/** 文章或活动的标签信息 */
			CSTR tag;
		}) activities;
 
	} data;

} QueryActivityListResponse;

C_API QueryActivityListResponse *HSAPI_INIT(QueryActivityListResponse);

#endif
