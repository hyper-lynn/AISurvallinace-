/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGrowupVideo_H_
#define _HSVIEW_CLIENT_API_GetGrowupVideo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据浓缩视频录像ID获取视频可播放URL地址。
【使用平台账号签名】
 */

typedef struct GetGrowupVideoRequest 
{
	HsviewRequest base;

	struct GetGrowupVideoRequestData
	{
		
		/** [long]成长记录的浓缩视频录像ID */
		int64 recordId;

	} data;

} GetGrowupVideoRequest;

C_API GetGrowupVideoRequest *HSAPI_INIT(GetGrowupVideoRequest);

typedef struct GetGrowupVideoResponse 
{
	HsviewResponse base;

	struct GetGrowupVideoResponseData
	{
		
		/** 用于播放的视频URL地址 */
		CSTR url;
 
	} data;

} GetGrowupVideoResponse;

C_API GetGrowupVideoResponse *HSAPI_INIT(GetGrowupVideoResponse);

#endif
