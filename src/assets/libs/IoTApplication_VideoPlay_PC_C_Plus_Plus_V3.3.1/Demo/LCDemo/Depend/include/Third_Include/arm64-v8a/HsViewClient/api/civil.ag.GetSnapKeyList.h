/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSnapKeyList_H_
#define _HSVIEW_CLIENT_API_GetSnapKeyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取门锁临时秘钥列表，默认按照秘钥生成时间倒序排序。
【需要使用平台账号签名】
 */

typedef struct GetSnapKeyListRequest 
{
	HsviewRequest base;

	struct GetSnapKeyListRequestData
	{
		
		/** [long]从该临时秘钥记录id开始查询。若要从最新开始查，填-1 */
		int64 snapKeyRecordId;
		/** 配件ID */
		CSTR apId;
		/** [int]需要查的最大条数 */
		int count;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} GetSnapKeyListRequest;

C_API GetSnapKeyListRequest *HSAPI_INIT(GetSnapKeyListRequest);

typedef struct GetSnapKeyListResponse 
{
	HsviewResponse base;

	struct GetSnapKeyListResponseData
	{
		
		/** define a list with struct of GetSnapKeyListResponseData_SnapKeysElement */
		DECLARE_LIST(struct GetSnapKeyListResponseData_SnapKeysElement
		{
			/** [long]临时秘钥记录id */
			int64 snapKeyRecordId;
			/** [long][O]秘钥使用时间（可为空，null表示未使用）,unix时间戳 */
			int64 usedTime;
			/** 临时秘钥的唯一标示符 */
			CSTR keyId;
			/** 门锁秘钥 */
			CSTR snapKey;
			/** [long][O]秘钥失效时间，unix时间戳 */
			int64 expired;
			/** [long]秘钥生成时间，unix时间戳 */
			int64 unusedTime;
			/** 秘钥状态，'Unused'：未使用；'Used'：已使用; 'Expired':已失效 */
			CSTR status;
		}) snapKeys;
 
	} data;

} GetSnapKeyListResponse;

C_API GetSnapKeyListResponse *HSAPI_INIT(GetSnapKeyListResponse);

#endif
