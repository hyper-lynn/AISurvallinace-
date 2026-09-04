/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByDeviceId_H_
#define _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByDeviceId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除某个设备所有录像。

类型 - 含义                  - 是否加密    -  备注
2    - 留言                  -    是       -  TC5S需求
1000 - 告警（移动检测）录像  -    是       -  动检报警录像
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像

【使用平台账号签名】
 */

typedef struct cloudRecord_DeleteCloudRecordByDeviceIdRequest 
{
	HsviewRequest base;

	struct cloudRecord_DeleteCloudRecordByDeviceIdRequestData
	{
		
		/** [O]通道号 */
		CSTR channelId;
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_DeleteCloudRecordByDeviceIdRequest;

C_API cloudRecord_DeleteCloudRecordByDeviceIdRequest *HSAPI_INIT(cloudRecord_DeleteCloudRecordByDeviceIdRequest);

typedef struct cloudRecord_DeleteCloudRecordByDeviceIdResponse 
{
	HsviewResponse base;

	struct cloudRecord_DeleteCloudRecordByDeviceIdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudRecord_DeleteCloudRecordByDeviceIdResponse;

C_API cloudRecord_DeleteCloudRecordByDeviceIdResponse *HSAPI_INIT(cloudRecord_DeleteCloudRecordByDeviceIdResponse);

#endif
