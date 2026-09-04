/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_UpdateSquarePrize_H_
#define _HSVIEW_CLIENT_API_squareVideo_UpdateSquarePrize_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
对分享的视频的点赞数进行操作
【使用平台账号签名】
 */

typedef struct squareVideo_UpdateSquarePrizeRequest 
{
	HsviewRequest base;

	struct squareVideo_UpdateSquarePrizeRequestData
	{
		
		/** 设备访问权限 */
		CSTR accessKey;
		/** [int]1点赞，-1取消点赞 */
		int type;
		/** [long]分享的视频ID */
		int64 shareVideoId;

	} data;

} squareVideo_UpdateSquarePrizeRequest;

C_API squareVideo_UpdateSquarePrizeRequest *HSAPI_INIT(squareVideo_UpdateSquarePrizeRequest);

typedef struct squareVideo_UpdateSquarePrizeResponse 
{
	HsviewResponse base;

	struct squareVideo_UpdateSquarePrizeResponseData
	{
		
		/** [int]操作过后的点赞数 */
		int prizeNum;
 
	} data;

} squareVideo_UpdateSquarePrizeResponse;

C_API squareVideo_UpdateSquarePrizeResponse *HSAPI_INIT(squareVideo_UpdateSquarePrizeResponse);

#endif
