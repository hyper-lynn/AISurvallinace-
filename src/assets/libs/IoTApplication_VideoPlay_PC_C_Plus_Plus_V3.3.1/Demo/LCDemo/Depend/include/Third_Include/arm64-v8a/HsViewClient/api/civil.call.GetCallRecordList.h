/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetCallRecordList_H_
#define _HSVIEW_CLIENT_API_GetCallRecordList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备的呼叫记录。
【使用平台账号签名】
 */

typedef struct GetCallRecordListRequest 
{
	HsviewRequest base;

	struct GetCallRecordListRequestData
	{
		
		/** [long]从该呼叫记录id开始查询。若要从最新开始查，填-1 */
		int64 callRecordId;
		/** 通道号 */
		CSTR channelId;
		/** [int]需要查的最大条数 */
		int count;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetCallRecordListRequest;

C_API GetCallRecordListRequest *HSAPI_INIT(GetCallRecordListRequest);

typedef struct GetCallRecordListResponse 
{
	HsviewResponse base;

	struct GetCallRecordListResponseData
	{
		
		/** define a list with struct of GetCallRecordListResponseData_CallRecordsElement */
		DECLARE_LIST(struct GetCallRecordListResponseData_CallRecordsElement
		{
			/**  'call':未接, 'answer':接听 */
			CSTR status;
			/** [long],呼叫时间unix时间戳 */
			int64 callTime;
			/**  'phone':手机, 'indoor':室内机 */
			CSTR method;
			/** [long]呼叫记录id */
			int64 callRecordId;
		}) callRecords;
 
	} data;

} GetCallRecordListResponse;

C_API GetCallRecordListResponse *HSAPI_INIT(GetCallRecordListResponse);

#endif
