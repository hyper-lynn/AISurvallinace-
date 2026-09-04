/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryRecordBitmap_H_
#define _HSVIEW_CLIENT_API_QueryRecordBitmap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询设备某年某月的录像覆盖的掩码
请求通道ChannelID中，Year年Month月的录像覆盖掩码。
返回Bitmap，表示该月中每一天是否存在录像，1表示有录像，0表示没有录像。
如上例中，5月份一共返回31个字符。

ChannelID取值详见查询录像总数。
 */

typedef struct QueryRecordBitmapRequest 
{
	HsviewRequest base;

	struct QueryRecordBitmapRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_QueryRecordBitmapRequestData_METHOD "POST"
		/** [cstr]record-bitmap */
		#define _STATIC_QueryRecordBitmapRequestData_CMD "record-bitmap"
		/** struct of QueryRecordBitmapRequestData_Body */
		struct QueryRecordBitmapRequestData_Body {
			/** 通道号或通道的设备ID */
			CSTR ChannelID;
			/** [int]年 */
			int Year;
			/** [int]月 */
			int Month;
		} body;

	} data;

} QueryRecordBitmapRequest;

C_API QueryRecordBitmapRequest *HSAPI_INIT(QueryRecordBitmapRequest);

typedef struct QueryRecordBitmapResponse 
{
	HsviewResponse base;

	struct QueryRecordBitmapResponseData
	{
		
		/** 日掩码：1111100000111110000011111000001 */
		CSTR Bitmap;
 
	} data;

} QueryRecordBitmapResponse;

C_API QueryRecordBitmapResponse *HSAPI_INIT(QueryRecordBitmapResponse);

#endif
