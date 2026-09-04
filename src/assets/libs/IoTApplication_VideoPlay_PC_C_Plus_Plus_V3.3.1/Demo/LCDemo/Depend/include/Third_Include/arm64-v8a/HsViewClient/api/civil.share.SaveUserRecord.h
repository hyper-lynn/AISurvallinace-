/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SaveUserRecord_H_
#define _HSVIEW_CLIENT_API_SaveUserRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
保存用户上传的录像。
【需要使用平台账号签名】
 */

typedef struct SaveUserRecordRequest 
{
	HsviewRequest base;

	struct SaveUserRecordRequestData
	{
		
		/** 录像文件云存储路径，目前限定为mp4 */
		CSTR filePath;

	} data;

} SaveUserRecordRequest;

C_API SaveUserRecordRequest *HSAPI_INIT(SaveUserRecordRequest);

typedef struct SaveUserRecordResponse 
{
	HsviewResponse base;

	struct SaveUserRecordResponseData
	{
		
		/** [long]用户录像索引ID */
		int64 userRecordId;
 
	} data;

} SaveUserRecordResponse;

C_API SaveUserRecordResponse *HSAPI_INIT(SaveUserRecordResponse);

#endif
