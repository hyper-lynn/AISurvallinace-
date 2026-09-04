/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoShareDetail_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoShareDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取分享的视频、摄像头详情
deviceId是直播源为摄像头时默认直播封面地址的解码秘钥
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareVideoShareDetailRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareVideoShareDetailRequestData
	{
		
		/** 设备访问权限 */
		CSTR accessKey;
		/** [int]需要获取的评论的数量 */
		int commentPageSize;
		/** [int]需要获取的评论的页号 */
		int commentPageNo;
		/** [long]分享视频的ID */
		int64 shareVideoId;

	} data;

} squareVideo_GetSquareVideoShareDetailRequest;

C_API squareVideo_GetSquareVideoShareDetailRequest *HSAPI_INIT(squareVideo_GetSquareVideoShareDetailRequest);

typedef struct squareVideo_GetSquareVideoShareDetailResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareVideoShareDetailResponseData
	{
		
		/** 其他信息 */
		CSTR other;
		/** 分享的视频描述 */
		CSTR description;
		/** [bool]是否已经点过赞 */
		BOOL isPrized;
		/** [bool]是否被收藏，true：被收藏，false：未被收藏 */
		BOOL isCollected;
		/** [int]浏览数 */
		int browseCount;
		/** 封面图 */
		CSTR coverPicUrl;
		/** [long]分享视频的ID */
		int64 shareVideoId;
		/** [int]点赞数 */
		int prizeCount;
		/** [long]视频类型id */
		int64 categoryId;
		/** [int]视频类型,0表示短片,1表示实时摄像头 */
		int type;
		/** [bool]是否可以评论 */
		BOOL isComment;
		/** [O]设备ID */
		CSTR deviceId;
		/** define a list with struct of squareVideo_GetSquareVideoShareDetailResponseData_CommentInfosElement */
		DECLARE_LIST(struct squareVideo_GetSquareVideoShareDetailResponseData_CommentInfosElement
		{
			/** [O]用户头像 */
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
		/** 分享视频的用户昵称 */
		CSTR shareUserNickName;
		/** 分享的视频标题 */
		CSTR title;
		/** 分享时间，yyyyMMddTHHmmssZ格式 */
		CSTR createTime;
		/** define a list with struct of squareVideo_GetSquareVideoShareDetailResponseData_ChannelsElement */
		DECLARE_LIST(struct squareVideo_GetSquareVideoShareDetailResponseData_ChannelsElement
		{
			/** 分享的视频标题 */
			CSTR title;
			/** 封面图 */
			CSTR coverPicUrl;
			/** [long]分享视频的ID */
			int64 shareVideoId;
			/** 设备ID */
			CSTR deviceId;
		}) channels;
		/** [int]评论数 */
		int commentCount;
 
	} data;

} squareVideo_GetSquareVideoShareDetailResponse;

C_API squareVideo_GetSquareVideoShareDetailResponse *HSAPI_INIT(squareVideo_GetSquareVideoShareDetailResponse);

#endif
