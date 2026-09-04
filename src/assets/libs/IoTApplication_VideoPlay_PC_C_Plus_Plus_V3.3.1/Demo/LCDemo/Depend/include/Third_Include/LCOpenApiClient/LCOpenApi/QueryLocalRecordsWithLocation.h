/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227439, Author: 426167, Date: 2024-10-12 14:00:49 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecordsWithLocation_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecordsWithLocation_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按照开始和结束时间查询设备录像

 */

typedef struct QueryLocalRecordsWithLocationRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordsWithLocationRequestData
	{
		
		/** 从第几条到第几条,单次查询上限100,1-100表示第1条到第100条,包含100,云录像查询相同 */
		CSTR queryRange;
		/** 类型,Manual、Event、All */
		CSTR type;
		/** [cstr]queryLocalRecords */
		#define _STATIC_QueryLocalRecordsWithLocationRequestData_method "queryLocalRecords"
		CSTR method;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 设备ID */
		CSTR deviceId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 分页查询的数量，最大30条 */
		CSTR count;
		/** device-设备录像 3rdcloud-下级中心录像 all-融合录像。默认设备录像 */
		CSTR location;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** 用于本地录像查询优化,有此参数的情况下设备会优先使用此参数查询 */
		CSTR sessionId;
		/** 通道ID */
		CSTR channelId;

	} data;

} QueryLocalRecordsWithLocationRequest;

C_API QueryLocalRecordsWithLocationRequest *LCOPENAPI_INIT(QueryLocalRecordsWithLocationRequest);

typedef struct QueryLocalRecordsWithLocationResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordsWithLocationResponseData
	{
		
		/** define a list with struct of QueryLocalRecordsWithLocationResponseData_RecordsElement */
		DECLARE_LIST(struct QueryLocalRecordsWithLocationResponseData_RecordsElement
		{
			/** 类型，Manual、Event、All */
			CSTR type;
			/**  */
			CSTR recordRegionId;
			/** [int]加密模式（0：默认加密模式；1：用户加密模式） */
			int encryptMode;
			/** 录像文件名 */
			CSTR recordId;
			/** 过期时间 */
			CSTR expireTime;
			/** 加密秘钥 */
			CSTR encryptSecret;
			/** 设备ID */
			CSTR deviceId;
			/** 码流类型 main:主码流，extraX:辅码流，缺省按照默认查询 */
			CSTR streamType;
			/** 录像文件地址路径 */
			CSTR recordPath;
			/** 加密图片下载地址 */
			CSTR thumbUrl;
			/** 文件大小 */
			CSTR size;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR endTime;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR beginTime;
			/** 通道ID */
			CSTR channelID;
			/** [long]录像文件长度 */
			int64 fileLength;
		}) records;
		/** MediaFileSession0 */
		CSTR sessionId;
 
	} data;

} QueryLocalRecordsWithLocationResponse;

C_API QueryLocalRecordsWithLocationResponse *LCOPENAPI_INIT(QueryLocalRecordsWithLocationResponse);

#endif
