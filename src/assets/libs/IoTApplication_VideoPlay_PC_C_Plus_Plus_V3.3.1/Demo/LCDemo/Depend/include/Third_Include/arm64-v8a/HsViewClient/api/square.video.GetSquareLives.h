/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareLives_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareLives_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
发现页面获取推荐直播列表，其中直播源包括摄像头和短片。
morePageUrl为更多页面路径
ShareVideoId为点击直播播放跳转url需要的Id。
deviceId是直播源为摄像头时默认直播封面地址的解码秘钥
【无需签名认证】【默认鉴权】
 */

typedef struct squareVideo_GetSquareLivesRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareLivesRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;

	} data;

} squareVideo_GetSquareLivesRequest;

C_API squareVideo_GetSquareLivesRequest *HSAPI_INIT(squareVideo_GetSquareLivesRequest);

typedef struct squareVideo_GetSquareLivesResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareLivesResponseData
	{
		
		/** 更多页面路径 */
		CSTR morePageUrl;
		/** define a list with struct of squareVideo_GetSquareLivesResponseData_LivesElement */
		DECLARE_LIST(struct squareVideo_GetSquareLivesResponseData_LivesElement
		{
			/** 直播名称 */
			CSTR liveName;
			/** [int]视频类型,0表示短片,1表示实时摄像头 */
			int type;
			/** 视频播放页面地址 */
			CSTR playUrl;
			/** 直播封面地址 */
			CSTR coverPicUrl;
			/** [int]浏览量 */
			int browseCount;
			/** [int]点赞数 */
			int prizeCount;
			/** [O]设备ID */
			CSTR deviceId;
		}) lives;
 
	} data;

} squareVideo_GetSquareLivesResponse;

C_API squareVideo_GetSquareLivesResponse *HSAPI_INIT(squareVideo_GetSquareLivesResponse);

#endif
