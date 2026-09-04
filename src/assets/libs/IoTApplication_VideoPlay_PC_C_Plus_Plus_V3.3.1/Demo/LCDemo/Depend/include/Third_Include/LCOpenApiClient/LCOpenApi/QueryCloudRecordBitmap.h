/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225946, Author: 112352, Date: 2024-03-06 14:20:43 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordBitmap_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordBitmap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有报警云录像的日期（以“天”为单位）

 */

typedef struct QueryCloudRecordBitmapRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordBitmapRequestData
	{
		
		/** [int]年 */
		int year;
		/** [cstr]queryCloudRecordBitmap */
		#define _STATIC_QueryCloudRecordBitmapRequestData_method "queryCloudRecordBitmap"
		CSTR method;
		/** [int]月 */
		int month;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** [bool]是否过滤通道。不带该参数或为true：根据通道查询；false：同时查询双通道录像，并通过按位或操作合并成单个掩码 */
		BOOL filterByChannel;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordBitmapRequest;

C_API QueryCloudRecordBitmapRequest *LCOPENAPI_INIT(QueryCloudRecordBitmapRequest);

typedef struct QueryCloudRecordBitmapResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordBitmapResponseData
	{
		
		/** 日掩码-1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryCloudRecordBitmapResponse;

C_API QueryCloudRecordBitmapResponse *LCOPENAPI_INIT(QueryCloudRecordBitmapResponse);

#endif
