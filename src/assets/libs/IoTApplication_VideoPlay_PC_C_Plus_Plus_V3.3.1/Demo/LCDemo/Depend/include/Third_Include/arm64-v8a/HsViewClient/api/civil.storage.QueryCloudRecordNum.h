/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryCloudRecordNum_H_
#define _HSVIEW_CLIENT_API_QueryCloudRecordNum_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询云存储录像记录总数。

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

typedef struct QueryCloudRecordNumRequest 
{
	HsviewRequest base;

	struct QueryCloudRecordNumRequestData
	{
		
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;
		/** [long]结束时间，Unix时间戳，1970年秒数 */
		int64 endTime;
		/** [long]开始时间，Unix时间戳，1970年秒数 */
		int64 beginTime;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordNumRequest;

C_API QueryCloudRecordNumRequest *HSAPI_INIT(QueryCloudRecordNumRequest);

typedef struct QueryCloudRecordNumResponse 
{
	HsviewResponse base;

	struct QueryCloudRecordNumResponseData
	{
		
		/** [int]录像总数 */
		int recordNum;
 
	} data;

} QueryCloudRecordNumResponse;

C_API QueryCloudRecordNumResponse *HSAPI_INIT(QueryCloudRecordNumResponse);

#endif
