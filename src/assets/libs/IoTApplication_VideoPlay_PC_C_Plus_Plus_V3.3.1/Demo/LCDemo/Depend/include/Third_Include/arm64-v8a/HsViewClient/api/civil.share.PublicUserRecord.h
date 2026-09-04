/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PublicUserRecord_H_
#define _HSVIEW_CLIENT_API_PublicUserRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
公开某个用户上传录像，得到视频页面URL。
【需要使用平台账号签名】
 */

typedef struct PublicUserRecordRequest 
{
	HsviewRequest base;

	struct PublicUserRecordRequestData
	{
		
		/** [O]分享的标题 */
		CSTR title;
		/** [long]用户录像索引ID */
		int64 userRecordId;

	} data;

} PublicUserRecordRequest;

C_API PublicUserRecordRequest *HSAPI_INIT(PublicUserRecordRequest);

typedef struct PublicUserRecordResponse 
{
	HsviewResponse base;

	struct PublicUserRecordResponseData
	{
		
		/** 公开视频的Token */
		CSTR token;
		/** 公开视频的页面URL */
		CSTR pageUrl;
 
	} data;

} PublicUserRecordResponse;

C_API PublicUserRecordResponse *HSAPI_INIT(PublicUserRecordResponse);

#endif
