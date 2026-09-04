/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByTime_H_
#define _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除某个设备一段时间内的录像，返回被删除的录像数。

类型 - 含义                  - 是否加密    -  备注
2    - 留言                  -    是       -  TC5S需求
1000 - 告警（移动检测）录像  -    是       -  动检报警录像
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像

【使用平台账号签名】
 */

typedef struct cloudRecord_DeleteCloudRecordByTimeRequest 
{
	HsviewRequest base;

	struct cloudRecord_DeleteCloudRecordByTimeRequestData
	{
		
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** 通道号 */
		CSTR channelId;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_DeleteCloudRecordByTimeRequest;

C_API cloudRecord_DeleteCloudRecordByTimeRequest *HSAPI_INIT(cloudRecord_DeleteCloudRecordByTimeRequest);

typedef struct cloudRecord_DeleteCloudRecordByTimeResponse 
{
	HsviewResponse base;

	struct cloudRecord_DeleteCloudRecordByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudRecord_DeleteCloudRecordByTimeResponse;

C_API cloudRecord_DeleteCloudRecordByTimeResponse *HSAPI_INIT(cloudRecord_DeleteCloudRecordByTimeResponse);

#endif
