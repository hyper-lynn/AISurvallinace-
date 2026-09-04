/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225946, Author: 112352, Date: 2024-03-06 14:20:43 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteCloudRecordByTime_H_
#define _LC_OPENAPI_CLIENT_DeleteCloudRecordByTime_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除动检云录像片段

 */

typedef struct DeleteCloudRecordByTimeRequest 
{
	LCOpenApiRequest base;

	struct DeleteCloudRecordByTimeRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** define a list with struct of DeleteCloudRecordByTimeRequestData_RecordInfosElement */
		DECLARE_LIST(struct DeleteCloudRecordByTimeRequestData_RecordInfosElement
		{
			/** 结束时间, 格式20231021T235959 */
			CSTR endTime;
			/** 通道ID */
			CSTR channelId;
			/** 开始时间, 格式20231021T000000 */
			CSTR beginTime;
		}) recordInfos;
		/** 结束时间, 格式20231021T235959 */
		CSTR endTime;
		/** 通道ID */
		CSTR channelId;
		/** 开始时间, 格式20231021T000000 */
		CSTR beginTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteCloudRecordByTimeRequest;

C_API DeleteCloudRecordByTimeRequest *LCOPENAPI_INIT(DeleteCloudRecordByTimeRequest);

typedef struct DeleteCloudRecordByTimeResponse 
{
	LCOpenApiResponse base;

	struct DeleteCloudRecordByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteCloudRecordByTimeResponse;

C_API DeleteCloudRecordByTimeResponse *LCOPENAPI_INIT(DeleteCloudRecordByTimeResponse);

#endif
