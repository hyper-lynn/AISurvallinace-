/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GeneratePublicLiveRecord_H_
#define _HSVIEW_CLIENT_API_GeneratePublicLiveRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
生成直播录像

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct GeneratePublicLiveRecordRequest 
{
	HsviewRequest base;

	struct GeneratePublicLiveRecordRequestData
	{
		
		/** [bool]是否生成录像封面 */
		BOOL isCover;
		/** 直播token */
		CSTR token;
		/** [long]结束时间,unix时间戳,秒 */
		int64 endTime;
		/** [long]开始时间,unix时间戳,秒 */
		int64 beginTime;
		/** [bool]是否永久保存,默认false */
		BOOL isSave;

	} data;

} GeneratePublicLiveRecordRequest;

C_API GeneratePublicLiveRecordRequest *HSAPI_INIT(GeneratePublicLiveRecordRequest);

typedef struct GeneratePublicLiveRecordResponse 
{
	HsviewResponse base;

	struct GeneratePublicLiveRecordResponseData
	{
		
		/** 录像存储地址 */
		CSTR storageUrl;
		/** 录像封面地址,为空表示录像封面不存在 */
		CSTR coverUrl;
 
	} data;

} GeneratePublicLiveRecordResponse;

C_API GeneratePublicLiveRecordResponse *HSAPI_INIT(GeneratePublicLiveRecordResponse);

#endif
