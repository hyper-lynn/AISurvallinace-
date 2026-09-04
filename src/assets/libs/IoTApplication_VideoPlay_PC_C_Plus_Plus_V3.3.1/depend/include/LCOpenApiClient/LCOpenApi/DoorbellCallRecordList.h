/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallRecordList_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallRecordList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取门铃的呼叫记录
 */

typedef struct DoorbellCallRecordListRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallRecordListRequestData
	{
		
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;
		/** 授权的token */
		CSTR token;
		/** [long]从该呼叫记录id开始查询。若要从最新开始查，填-1 */
		int64 callRecordId;
		/** [int]需要查的最大条数 */
		int count;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellCallRecordListRequest;

C_API DoorbellCallRecordListRequest *LCOPENAPI_INIT(DoorbellCallRecordListRequest);

typedef struct DoorbellCallRecordListResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallRecordListResponseData
	{
		
		/** define a list with struct of DoorbellCallRecordListResponseData_CallRecordsElement */
		DECLARE_LIST(struct DoorbellCallRecordListResponseData_CallRecordsElement
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

} DoorbellCallRecordListResponse;

C_API DoorbellCallRecordListResponse *LCOPENAPI_INIT(DoorbellCallRecordListResponse);

#endif
