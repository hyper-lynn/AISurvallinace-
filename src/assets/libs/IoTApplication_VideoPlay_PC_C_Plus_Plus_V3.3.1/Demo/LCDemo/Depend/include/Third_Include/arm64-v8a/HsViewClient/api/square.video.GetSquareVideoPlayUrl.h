/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoPlayUrl_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoPlayUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取播放url地址
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareVideoPlayUrlRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareVideoPlayUrlRequestData
	{
		
		/** [O]码流类型:hls,flv，rtmp,默认取flv */
		CSTR streamType;
		/** [O]直播分享的token */
		CSTR token;
		/** [long]分享id */
		int64 shareVideoId;
		/** [O][int]播放类型: 0:后台直播源添加，1：直播分享,2:开放平台直播创建 */
		CSTR playType;
		/** 客户端类型:IOS,Android,open */
		CSTR clientType;

	} data;

} squareVideo_GetSquareVideoPlayUrlRequest;

C_API squareVideo_GetSquareVideoPlayUrlRequest *HSAPI_INIT(squareVideo_GetSquareVideoPlayUrlRequest);

typedef struct squareVideo_GetSquareVideoPlayUrlResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareVideoPlayUrlResponseData
	{
		
		/** [int][O]高度 */
		int height;
		/** url地址 */
		CSTR playUrl;
		/** [O]封面图地址 */
		CSTR picUrl;
		/** [int][O]宽度 */
		int width;
 
	} data;

} squareVideo_GetSquareVideoPlayUrlResponse;

C_API squareVideo_GetSquareVideoPlayUrlResponse *HSAPI_INIT(squareVideo_GetSquareVideoPlayUrlResponse);

#endif
