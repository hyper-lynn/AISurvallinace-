/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PublishComment_H_
#define _HSVIEW_CLIENT_API_PublishComment_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据活动id发表评论或者回复某人。

reply为空，表示发表评论。
reply不为空，表示回复某人。

错误码：
1、1504 ：直播活动不存在

【使用平台账号签名】
 */

typedef struct PublishCommentRequest 
{
	HsviewRequest base;

	struct PublishCommentRequestData
	{
		
		/** [long]活动id */
		int64 activityId;
		/** struct of PublishCommentRequestData_Reply */
		struct PublishCommentRequestData_Reply {
			/** 被回复者的id */
			CSTR userId;
			/** [int]被回复用户的类型, 0表示乐橙用户,1表示授权微信公众号登录用户 */
			int userType;
		} reply;
		/** 评论内容 */
		CSTR content;

	} data;

} PublishCommentRequest;

C_API PublishCommentRequest *HSAPI_INIT(PublishCommentRequest);

typedef struct PublishCommentResponse 
{
	HsviewResponse base;

	struct PublishCommentResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PublishCommentResponse;

C_API PublishCommentResponse *HSAPI_INIT(PublishCommentResponse);

#endif
