/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225946, Author: 112352, Date: 2024-03-06 14:20:43 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteCloudRecords_H_
#define _LC_OPENAPI_CLIENT_DeleteCloudRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除动检云录像片段

 */

typedef struct DeleteCloudRecordsRequest 
{
	LCOpenApiRequest base;

	struct DeleteCloudRecordsRequestData
	{
		
		/** 云录像分区Id */
		CSTR recordRegionId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 云录像Id */
		CSTR recordId;
		/** 通道ID */
		CSTR channelId;
		/** define a list with struct of DeleteCloudRecordsRequestData_RecordInfosElement */
		DECLARE_LIST(struct DeleteCloudRecordsRequestData_RecordInfosElement
		{
			/** 云录像Id */
			CSTR recordId;
			/** 通道ID */
			CSTR channelId;
			/** 云录像分区Id */
			CSTR recordRegionId;
		}) recordInfos;

	} data;

} DeleteCloudRecordsRequest;

C_API DeleteCloudRecordsRequest *LCOPENAPI_INIT(DeleteCloudRecordsRequest);

typedef struct DeleteCloudRecordsResponse 
{
	LCOpenApiResponse base;

	struct DeleteCloudRecordsResponseData
	{
		
		/** define a list with struct of DeleteCloudRecordsResponseData_ErrInfosElement */
		DECLARE_LIST(struct DeleteCloudRecordsResponseData_ErrInfosElement
		{
			/** 错误码 */
			CSTR errCode;
			/** 错误信息 */
			CSTR msg;
			/** 云录像Id */
			CSTR recordId;
		}) errInfos;
 
	} data;

} DeleteCloudRecordsResponse;

C_API DeleteCloudRecordsResponse *LCOPENAPI_INIT(DeleteCloudRecordsResponse);

#endif
