/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByRecordIds_H_
#define _HSVIEW_CLIENT_API_cloudRecord_DeleteCloudRecordByRecordIds_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按录像id批量删除某个设备的录像。

【使用平台账号签名】
 */

typedef struct cloudRecord_DeleteCloudRecordByRecordIdsRequest 
{
	HsviewRequest base;

	struct cloudRecord_DeleteCloudRecordByRecordIdsRequestData
	{
		
		/** define a list with struct of cloudRecord_DeleteCloudRecordByRecordIdsRequestData_RecordsElement */
		DECLARE_LIST(struct cloudRecord_DeleteCloudRecordByRecordIdsRequestData_RecordsElement
		{
			/** [long]录像ID */
			int64 recordId;
			/** 区域唯一标识id */
			CSTR region;
		}) records;
		/** 通道号 */
		CSTR channelId;
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_DeleteCloudRecordByRecordIdsRequest;

C_API cloudRecord_DeleteCloudRecordByRecordIdsRequest *HSAPI_INIT(cloudRecord_DeleteCloudRecordByRecordIdsRequest);

typedef struct cloudRecord_DeleteCloudRecordByRecordIdsResponse 
{
	HsviewResponse base;

	struct cloudRecord_DeleteCloudRecordByRecordIdsResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudRecord_DeleteCloudRecordByRecordIdsResponse;

C_API cloudRecord_DeleteCloudRecordByRecordIdsResponse *HSAPI_INIT(cloudRecord_DeleteCloudRecordByRecordIdsResponse);

#endif
