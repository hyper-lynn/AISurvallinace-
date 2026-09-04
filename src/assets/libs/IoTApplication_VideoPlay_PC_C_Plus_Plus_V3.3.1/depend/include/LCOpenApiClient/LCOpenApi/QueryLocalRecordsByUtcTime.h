/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecordsByUtcTime_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecordsByUtcTime_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按照UTC开始和结束时间查询设备录像

 */

typedef struct QueryLocalRecordsByUtcTimeRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordsByUtcTimeRequestData
	{
		
		/** 类型,Manual、Event、All */
		CSTR type;
		/** [cstr]queryLocalRecordsByUtcTime */
		#define _STATIC_QueryLocalRecordsByUtcTimeRequestData_method "queryLocalRecordsByUtcTime"
		CSTR method;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 设备ID */
		CSTR deviceId;
		/** 限制查询数量，取值范围为[1,100] */
		CSTR limit;
		/** 产品ID */
		CSTR productId;
		/** 开始条数，从1开始 */
		CSTR start;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;

	} data;

} QueryLocalRecordsByUtcTimeRequest;

C_API QueryLocalRecordsByUtcTimeRequest *LCOPENAPI_INIT(QueryLocalRecordsByUtcTimeRequest);

typedef struct QueryLocalRecordsByUtcTimeResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordsByUtcTimeResponseData
	{
		
		/** MediaFileSession0 */
		CSTR sessionId;
		/** 是否逆序输出文件列表,可选,当该字段不存在,或者'false',按照正序输出 */
		CSTR reverseOrder;
		/** [int]录像条目数 */
		int recordNum;
		/** define a list with struct of QueryLocalRecordsByUtcTimeResponseData_RecordsElement */
		DECLARE_LIST(struct QueryLocalRecordsByUtcTimeResponseData_RecordsElement
		{
			/** 类型，Manual、Event、All */
			CSTR type;
			/** 本地录像文件名 */
			CSTR fileName;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR endTime;
			/** 录像文件名 */
			CSTR recordId;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR beginTime;
			/** 通道ID */
			CSTR channelID;
			/** [long]录像文件长度 */
			int64 fileLength;
		}) records;
 
	} data;

} QueryLocalRecordsByUtcTimeResponse;

C_API QueryLocalRecordsByUtcTimeResponse *LCOPENAPI_INIT(QueryLocalRecordsByUtcTimeResponse);

#endif
