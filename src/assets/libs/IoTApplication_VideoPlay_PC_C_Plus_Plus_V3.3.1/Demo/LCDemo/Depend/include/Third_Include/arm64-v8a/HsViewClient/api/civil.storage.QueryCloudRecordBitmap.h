/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryCloudRecordBitmap_H_
#define _HSVIEW_CLIENT_API_QueryCloudRecordBitmap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询云存储某年某月的录像覆盖的掩码。
返回bitmap，表示该月中每一天是否存在录像，1表示有录像，0表示没有录像。

类型 - 含义                  - 是否加密    -  备注
1    - 手动录像              -    否       -  X-MINI设备功能
2    - 留言                  -    是       -  TC5S需求
3    - 求救录像              -    是       -  TC5S需求（废弃）
1000 - 告警（移动检测）录像  -    是       -  同file-stream（原报警录像）
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像
注：为空表示原报警录像

【使用平台账号签名】
 */

typedef struct QueryCloudRecordBitmapRequest 
{
	HsviewRequest base;

	struct QueryCloudRecordBitmapRequestData
	{
		
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;
		/** [int]年 */
		int year;
		/** [int]月 */
		int month;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordBitmapRequest;

C_API QueryCloudRecordBitmapRequest *HSAPI_INIT(QueryCloudRecordBitmapRequest);

typedef struct QueryCloudRecordBitmapResponse 
{
	HsviewResponse base;

	struct QueryCloudRecordBitmapResponseData
	{
		
		/** 日掩码：1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryCloudRecordBitmapResponse;

C_API QueryCloudRecordBitmapResponse *HSAPI_INIT(QueryCloudRecordBitmapResponse);

#endif
