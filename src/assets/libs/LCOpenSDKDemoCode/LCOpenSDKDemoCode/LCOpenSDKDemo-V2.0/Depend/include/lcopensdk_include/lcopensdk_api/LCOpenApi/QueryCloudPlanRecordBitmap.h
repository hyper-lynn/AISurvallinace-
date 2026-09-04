/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudPlanRecordBitmap_H_
#define _LC_OPENAPI_CLIENT_QueryCloudPlanRecordBitmap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有定时云录像的日期（以“天”为单位）

 */

typedef struct QueryCloudPlanRecordBitmapRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudPlanRecordBitmapRequestData
	{
		
		/** [cstr]queryCloudPlanRecordBitmap */
		#define _STATIC_QueryCloudPlanRecordBitmapRequestData_method "queryCloudPlanRecordBitmap"
		CSTR method;
		/** [int]月 */
		int month;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** [int]年 */
		int year;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudPlanRecordBitmapRequest;

C_API QueryCloudPlanRecordBitmapRequest *LCOPENAPI_INIT(QueryCloudPlanRecordBitmapRequest);

typedef struct QueryCloudPlanRecordBitmapResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudPlanRecordBitmapResponseData
	{
		
		/** 日掩码-1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryCloudPlanRecordBitmapResponse;

C_API QueryCloudPlanRecordBitmapResponse *LCOPENAPI_INIT(QueryCloudPlanRecordBitmapResponse);

#endif
