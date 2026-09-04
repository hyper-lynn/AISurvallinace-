/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_AddSquareComment_H_
#define _HSVIEW_CLIENT_API_squareVideo_AddSquareComment_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加分享视频的评论
【使用平台账号签名】
 */

typedef struct squareVideo_AddSquareCommentRequest 
{
	HsviewRequest base;

	struct squareVideo_AddSquareCommentRequestData
	{
		
		/** [long]分享的视频ID */
		int64 shareVideoId;
		/** 评论内容 */
		CSTR content;

	} data;

} squareVideo_AddSquareCommentRequest;

C_API squareVideo_AddSquareCommentRequest *HSAPI_INIT(squareVideo_AddSquareCommentRequest);

typedef struct squareVideo_AddSquareCommentResponse 
{
	HsviewResponse base;

	struct squareVideo_AddSquareCommentResponseData
	{
		
		/** 用户昵称 */
		CSTR userNickName;
		/** 用户头像URL */
		CSTR userHeadPic;
 
	} data;

} squareVideo_AddSquareCommentResponse;

C_API squareVideo_AddSquareCommentResponse *HSAPI_INIT(squareVideo_AddSquareCommentResponse);

#endif
