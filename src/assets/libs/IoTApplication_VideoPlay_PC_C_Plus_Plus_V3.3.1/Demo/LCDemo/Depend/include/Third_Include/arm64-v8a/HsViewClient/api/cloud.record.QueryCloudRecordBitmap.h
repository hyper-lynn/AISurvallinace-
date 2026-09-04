/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_QueryCloudRecordBitmap_H_
#define _HSVIEW_CLIENT_API_cloudRecord_QueryCloudRecordBitmap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询云存储某年某月的录像覆盖的掩码。
返回bitmap，表示该月中每一天是否存在录像，1表示有录像，0表示没有录像。

类型 - 含义                  - 是否加密    -  备注
2    - 留言                  -    是       -  TC5S需求
1000 - 告警（移动检测）录像  -    是       -  动检报警录像
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像

【使用平台账号签名】
 */

typedef struct cloudRecord_QueryCloudRecordBitmapRequest 
{
	HsviewRequest base;

	struct cloudRecord_QueryCloudRecordBitmapRequestData
	{
		
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** [int]年 */
		int year;
		/** [int]月 */
		int month;
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_QueryCloudRecordBitmapRequest;

C_API cloudRecord_QueryCloudRecordBitmapRequest *HSAPI_INIT(cloudRecord_QueryCloudRecordBitmapRequest);

typedef struct cloudRecord_QueryCloudRecordBitmapResponse 
{
	HsviewResponse base;

	struct cloudRecord_QueryCloudRecordBitmapResponseData
	{
		
		/** 日掩码：1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} cloudRecord_QueryCloudRecordBitmapResponse;

C_API cloudRecord_QueryCloudRecordBitmapResponse *HSAPI_INIT(cloudRecord_QueryCloudRecordBitmapResponse);

#endif
