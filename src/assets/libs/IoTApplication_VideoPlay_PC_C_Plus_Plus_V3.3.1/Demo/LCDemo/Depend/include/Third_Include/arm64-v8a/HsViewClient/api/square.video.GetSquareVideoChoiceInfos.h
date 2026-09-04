/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoChoiceInfos_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoChoiceInfos_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
每种视频类型获取若干个视频，用于精选页面展示
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareVideoChoiceInfosRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareVideoChoiceInfosRequestData
	{
		
		/** [int]每种视频类型获取的数量 */
		int count;
		/** 设备访问权限 */
		CSTR accessKey;

	} data;

} squareVideo_GetSquareVideoChoiceInfosRequest;

C_API squareVideo_GetSquareVideoChoiceInfosRequest *HSAPI_INIT(squareVideo_GetSquareVideoChoiceInfosRequest);

typedef struct squareVideo_GetSquareVideoChoiceInfosResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareVideoChoiceInfosResponseData
	{
		
		/** define a list with struct of squareVideo_GetSquareVideoChoiceInfosResponseData_ShareVideoInfosElement */
		DECLARE_LIST(struct squareVideo_GetSquareVideoChoiceInfosResponseData_ShareVideoInfosElement
		{
			/** [int]视频类型 */
			int categoryId;
			/** define a list with struct of squareVideo_GetSquareVideoChoiceInfosResponseData_ShareVideoInfosElement_VideoInfosElement */
			DECLARE_LIST(struct squareVideo_GetSquareVideoChoiceInfosResponseData_ShareVideoInfosElement_VideoInfosElement
			{
				/** [int]视频类型,0表示短片,1表示实时摄像头 */
				int type;
				/** 分享的视频描述 */
				CSTR description;
				/** [bool]是否被收藏，true：被收藏，false：未被收藏 */
				BOOL isCollected;
				/** [int]浏览数 */
				int browseCount;
				/** [O]设备ID */
				CSTR deviceId;
				/** [long]分享视频的ID */
				int64 shareVideoId;
				/** [int]评论数 */
				int commentCount;
				/** 封面图 */
				CSTR coverPicUrl;
				/** [int]点赞数 */
				int prizeCount;
				/** 分享的视频标题 */
				CSTR title;
			}) videoInfos;
			/** 视频类型名称 */
			CSTR categoryName;
		}) shareVideoInfos;
 
	} data;

} squareVideo_GetSquareVideoChoiceInfosResponse;

C_API squareVideo_GetSquareVideoChoiceInfosResponse *HSAPI_INIT(squareVideo_GetSquareVideoChoiceInfosResponse);

#endif
