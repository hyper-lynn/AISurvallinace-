/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteUserRecord_H_
#define _HSVIEW_CLIENT_API_DeleteUserRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除用户上传的录像。
userRecordId 如果为-1，代表删除用户所有的分享记录
【需要使用平台账号签名】
 */

typedef struct DeleteUserRecordRequest 
{
	HsviewRequest base;

	struct DeleteUserRecordRequestData
	{
		
		/** [long]用户录像索引ID */
		int64 userRecordId;

	} data;

} DeleteUserRecordRequest;

C_API DeleteUserRecordRequest *HSAPI_INIT(DeleteUserRecordRequest);

typedef struct DeleteUserRecordResponse 
{
	HsviewResponse base;

	struct DeleteUserRecordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserRecordResponse;

C_API DeleteUserRecordResponse *HSAPI_INIT(DeleteUserRecordResponse);

#endif
