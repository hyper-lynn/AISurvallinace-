/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225946, Author: 112352, Date: 2024-03-06 14:20:43 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordByToken_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordByToken_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据云录像token或告警id查询设备云录像片段信息

 */

typedef struct QueryCloudRecordByTokenRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordByTokenRequestData
	{
		
		/** 告警id；paas设备必填 */
		CSTR alarmId;
		/** 云录像token */
		CSTR cloudToken;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** [cstr]queryCloudRecordByToken */
		#define _STATIC_QueryCloudRecordByTokenRequestData_method "queryCloudRecordByToken"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} QueryCloudRecordByTokenRequest;

C_API QueryCloudRecordByTokenRequest *LCOPENAPI_INIT(QueryCloudRecordByTokenRequest);

typedef struct QueryCloudRecordByTokenResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordByTokenResponseData
	{
		
		/** 区域 */
		CSTR region;
		/** 录像ID */
		CSTR recordId;
		/** 录像Id */
		CSTR recordRegionId;
		/** 录像地址 */
		CSTR recordPath;
		/** 缩略图URL */
		CSTR thumbUrl;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
		int encryptMode;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** 云录像的大小，单位byte */
		CSTR size;
 
	} data;

} QueryCloudRecordByTokenResponse;

C_API QueryCloudRecordByTokenResponse *LCOPENAPI_INIT(QueryCloudRecordByTokenResponse);

#endif
