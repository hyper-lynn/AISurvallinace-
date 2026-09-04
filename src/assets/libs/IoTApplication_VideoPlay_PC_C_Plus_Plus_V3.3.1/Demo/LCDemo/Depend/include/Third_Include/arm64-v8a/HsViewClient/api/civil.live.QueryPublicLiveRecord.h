/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicLiveRecord_H_
#define _HSVIEW_CLIENT_API_QueryPublicLiveRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
返回直播录像

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicLiveRecordRequest 
{
	HsviewRequest base;

	struct QueryPublicLiveRecordRequestData
	{
		
		/** [long]结束时间,unix时间戳,秒 */
		int64 endTime;
		/** [long]开始时间,unix时间戳,秒 */
		int64 beginTime;
		/** 直播token */
		CSTR token;

	} data;

} QueryPublicLiveRecordRequest;

C_API QueryPublicLiveRecordRequest *HSAPI_INIT(QueryPublicLiveRecordRequest);

typedef struct QueryPublicLiveRecordResponse 
{
	HsviewResponse base;

	struct QueryPublicLiveRecordResponseData
	{
		
		/** define a list with struct of QueryPublicLiveRecordResponseData_RecordsElement */
		DECLARE_LIST(struct QueryPublicLiveRecordResponseData_RecordsElement
		{
			/** 录像存储地址 */
			CSTR storageUrl;
			/** 录像封面地址,为空表示录像封面不存在 */
			CSTR coverUrl;
			/** [long]结束时间,unix时间戳,秒 */
			int64 endTime;
			/** [long]开始时间,unix时间戳,秒 */
			int64 beginTime;
			/** [bool]是否永久保存 */
			BOOL isSave;
		}) records;
 
	} data;

} QueryPublicLiveRecordResponse;

C_API QueryPublicLiveRecordResponse *HSAPI_INIT(QueryPublicLiveRecordResponse);

#endif
