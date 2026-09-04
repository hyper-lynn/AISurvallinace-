/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordNum_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordNum_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询报警云录像的数目（建议beginTime和endTime不要跨天）

 */

typedef struct QueryCloudRecordNumRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordNumRequestData
	{
		
		/** [cstr]queryCloudRecordNum */
		#define _STATIC_QueryCloudRecordNumRequestData_method "queryCloudRecordNum"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 通道ID */
		CSTR channelId;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordNumRequest;

C_API QueryCloudRecordNumRequest *LCOPENAPI_INIT(QueryCloudRecordNumRequest);

typedef struct QueryCloudRecordNumResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordNumResponseData
	{
		
		/** [int]录像总数 */
		int recordNum;
 
	} data;

} QueryCloudRecordNumResponse;

C_API QueryCloudRecordNumResponse *LCOPENAPI_INIT(QueryCloudRecordNumResponse);

#endif
