/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoShareInfos_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoShareInfos_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取分享的视频、摄像头信息列表
deviceId是直播源为摄像头时默认直播封面地址的解码秘钥
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareVideoShareInfosRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareVideoShareInfosRequestData
	{
		
		/** [long]视频类型id */
		int64 categoryId;
		/** [int]记录数 */
		int pageCount;
		/** 设备访问权限 */
		CSTR accessKey;
		/** [O]标题关键字，用于搜索 */
		CSTR titleKey;
		/** [int]页号 */
		int pageNo;

	} data;

} squareVideo_GetSquareVideoShareInfosRequest;

C_API squareVideo_GetSquareVideoShareInfosRequest *HSAPI_INIT(squareVideo_GetSquareVideoShareInfosRequest);

typedef struct squareVideo_GetSquareVideoShareInfosResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareVideoShareInfosResponseData
	{
		
		/** define a list with struct of squareVideo_GetSquareVideoShareInfosResponseData_ShareVideoInfosElement */
		DECLARE_LIST(struct squareVideo_GetSquareVideoShareInfosResponseData_ShareVideoInfosElement
		{
			/** [long]视频类型id */
			int64 categoryId;
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
			/** 分享的视频标题 */
			CSTR title;
			/** [int]评论数 */
			int commentCount;
			/** 封面图 */
			CSTR coverPicUrl;
			/** [int]点赞数 */
			int prizeCount;
			/** [long]分享视频的ID */
			int64 shareVideoId;
		}) shareVideoInfos;
		/** [int]分享视频的总数 */
		int shareVideoTotalCount;
 
	} data;

} squareVideo_GetSquareVideoShareInfosResponse;

C_API squareVideo_GetSquareVideoShareInfosResponse *HSAPI_INIT(squareVideo_GetSquareVideoShareInfosResponse);

#endif
