/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferRecord_H_
#define _HSVIEW_CLIENT_API_TransferRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的转移记录。


【平台签名认证】
 */

typedef struct TransferRecordRequest 
{
	HsviewRequest base;

	struct TransferRecordRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferRecordRequest;

C_API TransferRecordRequest *HSAPI_INIT(TransferRecordRequest);

typedef struct TransferRecordResponse 
{
	HsviewResponse base;

	struct TransferRecordResponseData
	{
		
		/** 设备转移时间 utc时间格式20170418T162832Z */
		CSTR time;
		/** 转移人电话号码或者邮箱 */
		CSTR account;
 
	} data;

} TransferRecordResponse;

C_API TransferRecordResponse *HSAPI_INIT(TransferRecordResponse);

#endif
