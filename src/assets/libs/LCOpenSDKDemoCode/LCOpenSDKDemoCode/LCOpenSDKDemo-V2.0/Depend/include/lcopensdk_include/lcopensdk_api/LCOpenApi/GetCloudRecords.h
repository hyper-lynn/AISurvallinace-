/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetCloudRecords_H_
#define _LC_OPENAPI_CLIENT_GetCloudRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按条件查询所有录像记录(倒序展示)

 */

typedef struct GetCloudRecordsRequest 
{
	LCOpenApiRequest base;

	struct GetCloudRecordsRequestData
	{
		
		/** 和nextRecordId选其一，SDK传nextRecordRegionId */
		CSTR nextRecordRegionId;
		/** [cstr]getCloudRecords */
		#define _STATIC_GetCloudRecordsRequestData_method "getCloudRecords"
		CSTR method;
		/** 结束时间，yyyy-MM-dd HH:mm:ss */
		CSTR endTime;
		/** 设备ID */
		CSTR deviceId;
		/** [int]分页查询的数量 */
		int count;
		/** 上次取到的最后录像的ID */
		CSTR nextRecordId;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 开始时间，yyyy-MM-dd HH:mm:ss */
		CSTR beginTime;

	} data;

} GetCloudRecordsRequest;

C_API GetCloudRecordsRequest *LCOPENAPI_INIT(GetCloudRecordsRequest);

typedef struct GetCloudRecordsResponse 
{
	LCOpenApiResponse base;

	struct GetCloudRecordsResponseData
	{
		
		/** define a list with struct of GetCloudRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct GetCloudRecordsResponseData_RecordsElement
		{
			/** 录像Id */
			CSTR recordId;
			/** 设备ID */
			CSTR deviceId;
			/** 录像recordRegionId */
			CSTR recordRegionId;
			/** 缩略图Url */
			CSTR thumbUrl;
			/** 通道ID */
			CSTR channelId;
			/** 结束时间 */
			CSTR endTime;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** 开始时间 */
			CSTR beginTime;
			/** [long]云录像大小，单位byte */
			int64 size;
		}) records;
 
	} data;

} GetCloudRecordsResponse;

C_API GetCloudRecordsResponse *LCOPENAPI_INIT(GetCloudRecordsResponse);

#endif
