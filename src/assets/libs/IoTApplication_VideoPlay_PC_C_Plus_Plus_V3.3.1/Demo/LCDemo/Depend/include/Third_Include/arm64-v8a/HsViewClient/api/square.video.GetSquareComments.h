/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareComments_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareComments_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取分享的视频、摄像头评论
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareCommentsRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareCommentsRequestData
	{
		
		/** 设备访问权限 */
		CSTR accessKey;
		/** [int]要查的评论页长 */
		int commentPageSize;
		/** [int]要查的评论页号 */
		int commentPageNo;
		/** [long]分享视频的ID */
		int64 shareVideoId;

	} data;

} squareVideo_GetSquareCommentsRequest;

C_API squareVideo_GetSquareCommentsRequest *HSAPI_INIT(squareVideo_GetSquareCommentsRequest);

typedef struct squareVideo_GetSquareCommentsResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareCommentsResponseData
	{
		
		/** define a list with struct of squareVideo_GetSquareCommentsResponseData_CommentInfosElement */
		DECLARE_LIST(struct squareVideo_GetSquareCommentsResponseData_CommentInfosElement
		{
			/** [O]用户头像地址 */
			CSTR userHeadPic;
			/** 评论用户昵称 */
			CSTR commentUserNickname;
			/** [long]评论ID */
			int64 commentId;
			/** 评论内容 */
			CSTR content;
			/** 评论时间，yyyyMMddTHHmmssZ格式 */
			CSTR commentCreateTime;
		}) commentInfos;
		/** [int]评论总数量 */
		int commentCount;
 
	} data;

} squareVideo_GetSquareCommentsResponse;

C_API squareVideo_GetSquareCommentsResponse *HSAPI_INIT(squareVideo_GetSquareCommentsResponse);

#endif
