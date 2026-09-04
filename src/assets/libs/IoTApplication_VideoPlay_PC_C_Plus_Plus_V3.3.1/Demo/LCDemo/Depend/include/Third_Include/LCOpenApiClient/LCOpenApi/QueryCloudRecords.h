/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecords_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按照开始和结束时间查询报警云录像

 */

typedef struct QueryCloudRecordsRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordsRequestData
	{
		
		/** 从第几条到第几条,单次查询上限100,1-100表示第1条到第100条,包含100,云录像查询相同 */
		CSTR queryRange;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** [cstr]queryCloudRecords */
		#define _STATIC_QueryCloudRecordsRequestData_method "queryCloudRecords"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 通道ID */
		CSTR channelId;
		/** [bool]是否过滤通道。不带该参数或为true：根据通道查询；false：同时查询双通道录像 */
		BOOL filterByChannel;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordsRequest;

C_API QueryCloudRecordsRequest *LCOPENAPI_INIT(QueryCloudRecordsRequest);

typedef struct QueryCloudRecordsResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordsResponseData
	{
		
		/** define a list with struct of QueryCloudRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct QueryCloudRecordsResponseData_RecordsElement
		{
			/** paas专用 过期时间 */
			CSTR expireTime;
			/** 录像ID */
			CSTR recordId;
			/** [int]加密模式（0：默认加密模式；1：用户加密模式） */
			int encryptMode;
			/** paas专用 录像文件路径 */
			CSTR recordPath;
			/** 设备ID */
			CSTR deviceId;
			/** paas专用 录像加密秘钥 */
			CSTR encryptSecret;
			/** 录像RegionId */
			CSTR recordRegionId;
			/** define a list with struct of QueryCloudRecordsResponseData_RecordsElement_RecordInfosElement */
			DECLARE_LIST(struct QueryCloudRecordsResponseData_RecordsElement_RecordInfosElement
			{
				/** paas专用 过期时间 */
				CSTR expireTime;
				/** 录像ID */
				CSTR recordId;
				/** paas专用 录像文件路径 */
				CSTR recordPath;
				/** 设备ID */
				CSTR deviceId;
				/** paas专用 录像加密秘钥 */
				CSTR encryptSecret;
				/** 录像RegionId */
				CSTR recordRegionId;
				/** [int]加密模式（0：默认加密模式；1：用户加密模式） */
				int encryptMode;
				/** 加密图片下载地址 */
				CSTR thumbUrl;
				/** 结束时间，如2010-05-25 23:59:59 */
				CSTR endTime;
				/** 通道ID */
				CSTR channelId;
				/** 开始时间，如2010-05-25 00:00:00 */
				CSTR beginTime;
				/** 云录像的大小，单位byte */
				CSTR size;
			}) recordInfos;
			/** 加密图片下载地址 */
			CSTR thumbUrl;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR endTime;
			/** 通道ID */
			CSTR channelId;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR beginTime;
			/** 云录像的大小，单位byte */
			CSTR size;
		}) records;
 
	} data;

} QueryCloudRecordsResponse;

C_API QueryCloudRecordsResponse *LCOPENAPI_INIT(QueryCloudRecordsResponse);

#endif
