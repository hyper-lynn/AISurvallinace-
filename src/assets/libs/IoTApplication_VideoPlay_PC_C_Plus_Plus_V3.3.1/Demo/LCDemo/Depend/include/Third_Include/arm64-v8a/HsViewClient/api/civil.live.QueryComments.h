/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryComments_H_
#define _HSVIEW_CLIENT_API_QueryComments_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据活动id分页获取活动评论列表(倒序)

reply为空，表示发表评论。
reply不为空，表示回复某人。

错误码：
1、1504 ：直播活动不存在

【不鉴权】
 */

typedef struct QueryCommentsRequest 
{
	HsviewRequest base;

	struct QueryCommentsRequestData
	{
		
		/** [long]上次最后一个获取的评论id。若要从最新开始查，填-1 */
		int64 commentId;
		/** [int]需要查的最大条数,最大支持100 */
		int count;
		/** [long]活动id */
		int64 activityId;

	} data;

} QueryCommentsRequest;

C_API QueryCommentsRequest *HSAPI_INIT(QueryCommentsRequest);

typedef struct QueryCommentsResponse 
{
	HsviewResponse base;

	struct QueryCommentsResponseData
	{
		
		/** define a list with struct of QueryCommentsResponseData_CommentsElement */
		DECLARE_LIST(struct QueryCommentsResponseData_CommentsElement
		{
			/** 评论者昵称 */
			CSTR nickname;
			/** struct of QueryCommentsResponseData_CommentsElement_Reply */
			struct QueryCommentsResponseData_CommentsElement_Reply {
				/** [O]被回复者的昵称 */
				CSTR nickname;
				/** [O]被回复者的id */
				CSTR userId;
				/** [int][O]被回复用户的类型, 0表示乐橙用户,1表示授权微信公众号登录用户 */
				int userType;
			} reply;
			/** 用户头像URL */
			CSTR userIconUrl;
			/** [long]评论时间。Unix时间（单位秒） */
			int64 commentTime;
			/** [long]评论id */
			int64 commentId;
			/** 内容 */
			CSTR content;
			/** 评论者id */
			CSTR userId;
			/** [int]评论者的类型, 0表示乐橙用户,1表示授权微信公众号登录用户 */
			int userType;
		}) comments;
 
	} data;

} QueryCommentsResponse;

C_API QueryCommentsResponse *HSAPI_INIT(QueryCommentsResponse);

#endif
