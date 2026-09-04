/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetCallRecordList_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetCallRecordList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备的呼叫记录。
【使用平台账号签名】
 */

typedef struct cloudMessage_GetCallRecordListRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetCallRecordListRequestData
	{
		
		/** [long]从该呼叫记录id开始查询。若要从最新开始查，填-1 */
		int64 callRecordId;
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;
		/** [int]需要查的最大条数 */
		int count;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_GetCallRecordListRequest;

C_API cloudMessage_GetCallRecordListRequest *HSAPI_INIT(cloudMessage_GetCallRecordListRequest);

typedef struct cloudMessage_GetCallRecordListResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetCallRecordListResponseData
	{
		
		/** define a list with struct of cloudMessage_GetCallRecordListResponseData_CallRecordsElement */
		DECLARE_LIST(struct cloudMessage_GetCallRecordListResponseData_CallRecordsElement
		{
			/**  answer:接听,call:未接听 */
			CSTR status;
			/** 展示文案 */
			CSTR title;
			/** 设备呼叫本地时间,yyyyMMddTHHmmss格式 */
			CSTR localTime;
			/** [long]呼叫记录id */
			int64 callRecordId;
		}) callRecords;
 
	} data;

} cloudMessage_GetCallRecordListResponse;

C_API cloudMessage_GetCallRecordListResponse *HSAPI_INIT(cloudMessage_GetCallRecordListResponse);

#endif
