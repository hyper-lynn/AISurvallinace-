/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserRecordList_H_
#define _HSVIEW_CLIENT_API_GetUserRecordList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户上传录像的列表。
【需要使用平台账号签名】
 */

typedef struct GetUserRecordListRequest 
{
	HsviewRequest base;

	struct GetUserRecordListRequestData
	{
		
		/** [long]起始的用户录像索引ID */
		int64 userRecordId;
		/** [int]需要获取的数量 */
		int count;

	} data;

} GetUserRecordListRequest;

C_API GetUserRecordListRequest *HSAPI_INIT(GetUserRecordListRequest);

typedef struct GetUserRecordListResponse 
{
	HsviewResponse base;

	struct GetUserRecordListResponseData
	{
		
		/** define a list with struct of GetUserRecordListResponseData_UserRecordsElement */
		DECLARE_LIST(struct GetUserRecordListResponseData_UserRecordsElement
		{
			/** [long]用户录像索引ID */
			int64 userRecordId;
			/** 标题 */
			CSTR title;
			/** 录像封面图URL */
			CSTR coverUrl;
			/** [long]上传时间，UNIX时间戳（秒） */
			int64 time;
			/** 视频文件的url */
			CSTR url;
			/** 上传录像的平台账号用户名 */
			CSTR username;
			/** 录像页面URL */
			CSTR pageUrl;
		}) userRecords;
 
	} data;

} GetUserRecordListResponse;

C_API GetUserRecordListResponse *HSAPI_INIT(GetUserRecordListResponse);

#endif
