/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetActivityAttendedList_H_
#define _HSVIEW_CLIENT_API_GetActivityAttendedList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取当前用户已参加的育儿活动列表
【使用平台账号签名】
 */

typedef struct GetActivityAttendedListRequest 
{
	HsviewRequest base;

	struct GetActivityAttendedListRequestData
	{
		
		/** 分页获取,从第几条到第几条，如[1-100],闭区间,最多一次查询100条 */
		CSTR need;

	} data;

} GetActivityAttendedListRequest;

C_API GetActivityAttendedListRequest *HSAPI_INIT(GetActivityAttendedListRequest);

typedef struct GetActivityAttendedListResponse 
{
	HsviewResponse base;

	struct GetActivityAttendedListResponseData
	{
		
		/** define a list with struct of GetActivityAttendedListResponseData_ActivityListElement */
		DECLARE_LIST(struct GetActivityAttendedListResponseData_ActivityListElement
		{
			/** [long]文章或活动的发布时间。Unix时间（单位秒） */
			int64 publishTime;
			/** [int]活动类型, 3：投稿活动，4：试用活动，5：线下活动 */
			int type;
			/** [O]获奖标签 */
			CSTR prizeTag;
			/** 当前用户参加该活动的拉票分享地址 */
			CSTR userShareUrl;
			/** [long]活动ID */
			int64 activityId;
			/** [long]用户参加活动的时间，Unix时间（单位秒） */
			int64 joinTime;
			/** 参加活动提交的内容，格式为json串 */
			CSTR data;
			/** [long]当前用户参加该活动的总点赞次数 */
			int64 userLikeTimes;
			/** 用户头像地址 */
			CSTR userHeadPic;
			/** [long]参加活动的用户数 */
			int64 joinNum;
			/** 活动的标题 */
			CSTR title;
			/** [bool]当前用户是否对自己参加的这个活动已点赞 */
			BOOL isUserLike;
			/** [int]活动状态 1-未发布，2-进行中，3-已结束 */
			int status;
			/** [long]开始时间。Unix时间（单位秒） */
			int64 beginTime;
			/** 活动的封面地址 */
			CSTR thumbUrl;
			/** [long]结束时间。Unix时间（单位秒） */
			int64 endTime;
		}) activityList;
 
	} data;

} GetActivityAttendedListResponse;

C_API GetActivityAttendedListResponse *HSAPI_INIT(GetActivityAttendedListResponse);

#endif
