/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecordBitmap_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecordBitmap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有设备录像的日期（以“天”为单位）

 */

typedef struct QueryLocalRecordBitmapRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordBitmapRequestData
	{
		
		/** [String，可选]type可传本地录像类型的指定值(all,normal,videomotion等类型) */
		CSTR type;
		/** [cstr]queryLocalRecordBitmap */
		#define _STATIC_QueryLocalRecordBitmapRequestData_method "queryLocalRecordBitmap"
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

} QueryLocalRecordBitmapRequest;

C_API QueryLocalRecordBitmapRequest *LCOPENAPI_INIT(QueryLocalRecordBitmapRequest);

typedef struct QueryLocalRecordBitmapResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordBitmapResponseData
	{
		
		/** 日掩码-1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryLocalRecordBitmapResponse;

C_API QueryLocalRecordBitmapResponse *LCOPENAPI_INIT(QueryLocalRecordBitmapResponse);

#endif
