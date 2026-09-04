/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226113, Author: 112352, Date: 2024-04-11 09:32:00 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordMultiByToken_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordMultiByToken_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据云录像token或告警id查询双目设备云录像片段信息

 */

typedef struct QueryCloudRecordMultiByTokenRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordMultiByTokenRequestData
	{
		
		/** 告警id；paas设备必填 */
		CSTR alarmId;
		/** 云录像token */
		CSTR cloudToken;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** [cstr]queryCloudRecordByToken */
		#define _STATIC_QueryCloudRecordMultiByTokenRequestData_method "queryCloudRecordByToken"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} QueryCloudRecordMultiByTokenRequest;

C_API QueryCloudRecordMultiByTokenRequest *LCOPENAPI_INIT(QueryCloudRecordMultiByTokenRequest);

typedef struct QueryCloudRecordMultiByTokenResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordMultiByTokenResponseData
	{
		
		/** define a list with struct of QueryCloudRecordMultiByTokenResponseData_RecordsElement */
		DECLARE_LIST(struct QueryCloudRecordMultiByTokenResponseData_RecordsElement
		{
			/** 区域 */
			CSTR region;
			/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
			CSTR localBeginTime;
			/** 录像地址 */
			CSTR recordPath;
			/** 录像Id */
			CSTR recordRegionId;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** 录像ID */
			CSTR recordId;
			/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
			CSTR localEndTime;
			/** 设备通道号 */
			CSTR channelId;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 云录像的大小，单位byte */
			CSTR size;
		}) records;
 
	} data;

} QueryCloudRecordMultiByTokenResponse;

C_API QueryCloudRecordMultiByTokenResponse *LCOPENAPI_INIT(QueryCloudRecordMultiByTokenResponse);

#endif
