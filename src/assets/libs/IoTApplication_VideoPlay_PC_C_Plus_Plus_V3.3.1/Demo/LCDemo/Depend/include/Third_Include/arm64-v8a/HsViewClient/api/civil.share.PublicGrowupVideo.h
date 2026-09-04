/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PublicGrowupVideo_H_
#define _HSVIEW_CLIENT_API_PublicGrowupVideo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
公开某个成长记录的浓缩视频。
公开后，平台需要把该视频文件挪到用户的云存储空间中，避免被云存储套餐删除。
【需要使用平台账号签名】
 */

typedef struct PublicGrowupVideoRequest 
{
	HsviewRequest base;

	struct PublicGrowupVideoRequestData
	{
		
		/** [long]浓缩视频录像ID（查询成长记录时得到） */
		int64 recordId;

	} data;

} PublicGrowupVideoRequest;

C_API PublicGrowupVideoRequest *HSAPI_INIT(PublicGrowupVideoRequest);

typedef struct PublicGrowupVideoResponse 
{
	HsviewResponse base;

	struct PublicGrowupVideoResponseData
	{
		
		/** 公开视频的页面URL */
		CSTR pageUrl;
 
	} data;

} PublicGrowupVideoResponse;

C_API PublicGrowupVideoResponse *HSAPI_INIT(PublicGrowupVideoResponse);

#endif
