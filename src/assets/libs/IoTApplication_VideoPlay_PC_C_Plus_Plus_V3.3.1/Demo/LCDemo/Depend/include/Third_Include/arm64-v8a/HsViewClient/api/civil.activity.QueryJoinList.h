/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryJoinList_H_
#define _HSVIEW_CLIENT_API_QueryJoinList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户获取参加活动信息
data内的数据为json格式的字符串，平台不对具体内容做限制和校验

【需要乐橙账号鉴权】
 */

typedef struct QueryJoinListRequest 
{
	HsviewRequest base;

	struct QueryJoinListRequestData
	{
		
		/** [long]活动id */
		int64 activityId;
		/** 分页获取,从第几条到第几条，如[1-100],闭区间,最多一次查询100条 */
		CSTR need;
		/** [int]排序类型  0-最新 （缺省）1-最热 2-获奖 */
		int sortType;

	} data;

} QueryJoinListRequest;

C_API QueryJoinListRequest *HSAPI_INIT(QueryJoinListRequest);

typedef struct QueryJoinListResponse 
{
	HsviewResponse base;

	struct QueryJoinListResponseData
	{
		
		/** define a list with struct of QueryJoinListResponseData_JoinListElement */
		DECLARE_LIST(struct QueryJoinListResponseData_JoinListElement
		{
			/** 用户昵称 */
			CSTR nickname;
			/** [bool]当前登录用户是否对上面的userId参与当前活动内容点赞 */
			BOOL isUserLike;
			/** [long][O]楼层信息 */
			int64 floor;
			/** [long]参加活动的unix时间 */
			int64 joinTime;
			/** [long]乐橙用户id */
			int64 userId;
			/** [long]点赞次数 */
			int64 userLikeTimes;
			/** 用户头像 */
			CSTR userIcon;
			/** [O]获奖标签 */
			CSTR prizeTag;
			/** 参加活动提交的内容，格式为json串 */
			CSTR data;
		}) joinList;
 
	} data;

} QueryJoinListResponse;

C_API QueryJoinListResponse *HSAPI_INIT(QueryJoinListResponse);

#endif
