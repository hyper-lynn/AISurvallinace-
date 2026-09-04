/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetOpenLockRecords_H_
#define _HSVIEW_CLIENT_API_GetOpenLockRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取门锁开锁记录。最多取7天以内的开锁记录
【需要使用平台账号签名】
 */

typedef struct GetOpenLockRecordsRequest 
{
	HsviewRequest base;

	struct GetOpenLockRecordsRequestData
	{
		
		/** [long]从该次开锁记录的ID开始查询。若要从最新开始查，填-1 */
		int64 unlockRecordId;
		/** 配件ID */
		CSTR apId;
		/** [int]需要查的最大条数 */
		int count;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} GetOpenLockRecordsRequest;

C_API GetOpenLockRecordsRequest *HSAPI_INIT(GetOpenLockRecordsRequest);

typedef struct GetOpenLockRecordsResponse 
{
	HsviewResponse base;

	struct GetOpenLockRecordsResponseData
	{
		
		/** define a list with struct of GetOpenLockRecordsResponseData_UnlockRecordsElement */
		DECLARE_LIST(struct GetOpenLockRecordsResponseData_UnlockRecordsElement
		{
			/** [int]开锁尝试次数 */
			int number;
			/** 钥匙类型; 'password':密码；'fingerPrint'：指纹；'card'：卡 */
			CSTR type;
			/** 钥匙名称 */
			CSTR name;
			/** 钥匙唯一标示符 */
			CSTR keyId;
			/** [long]开锁记录id */
			int64 unlockRecordId;
			/** [bool]开锁结果，true：开锁成功，false：开锁失败 */
			BOOL result;
			/** [long]开锁时间,unix时间戳 */
			int64 unlockTime;
		}) unlockRecords;
 
	} data;

} GetOpenLockRecordsResponse;

C_API GetOpenLockRecordsResponse *HSAPI_INIT(GetOpenLockRecordsResponse);

#endif
