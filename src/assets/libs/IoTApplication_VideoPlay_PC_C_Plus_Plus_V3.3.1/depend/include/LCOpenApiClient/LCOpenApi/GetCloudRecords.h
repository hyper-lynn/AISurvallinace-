/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225946, Author: 112352, Date: 2024-03-06 14:20:43 +0800 
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
		
		/** [int]分页查询的数量 */
		int count;
		/** [cstr]getCloudRecords */
		#define _STATIC_GetCloudRecordsRequestData_method "getCloudRecords"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 开始时间，yyyy-MM-dd HH:mm:ss */
		CSTR beginTime;
		/** 结束时间，yyyy-MM-dd HH:mm:ss */
		CSTR endTime;
		/** 通道ID */
		CSTR channelId;
		/** [bool]是否过滤通道。不带该参数或为true：根据通道查询；false：同时查询双通道录像 */
		BOOL filterByChannel;
		/** 设备ID */
		CSTR deviceId;

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
			/** 录像类型：1000事件云录像，2000连续云录像，10001人形检测云录像 */
			CSTR type;
			/** paas专用 区域 */
			CSTR region;
			/** 录像Id */
			CSTR recordId;
			/** 缩略图Url */
			CSTR thumbUrl;
			/** paas专用 录像文件路径 */
			CSTR recordPath;
			/** 设备ID */
			CSTR deviceId;
			/** paas专用 录像加密秘钥 */
			CSTR encryptSecret;
			/** 录像recordRegionId */
			CSTR recordRegionId;
			/** define a list with struct of GetCloudRecordsResponseData_RecordsElement_RecordInfosElement */
			DECLARE_LIST(struct GetCloudRecordsResponseData_RecordsElement_RecordInfosElement
			{
				/** 录像类型：1000事件云录像，2000连续云录像，10001人形检测云录像 */
				CSTR type;
				/** paas专用 区域 */
				CSTR region;
				/** 录像Id */
				CSTR recordId;
				/** paas专用 录像文件路径 */
				CSTR recordPath;
				/** 设备ID */
				CSTR deviceId;
				/** paas专用 录像加密秘钥 */
				CSTR encryptSecret;
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
				/** 云录像大小，单位byte */
				CSTR size;
			}) recordInfos;
			/** 通道ID */
			CSTR channelId;
			/** 结束时间 */
			CSTR endTime;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** 开始时间 */
			CSTR beginTime;
			/** 云录像大小，单位byte */
			CSTR size;
		}) records;
 
	} data;

} GetCloudRecordsResponse;

C_API GetCloudRecordsResponse *LCOPENAPI_INIT(GetCloudRecordsResponse);

#endif
