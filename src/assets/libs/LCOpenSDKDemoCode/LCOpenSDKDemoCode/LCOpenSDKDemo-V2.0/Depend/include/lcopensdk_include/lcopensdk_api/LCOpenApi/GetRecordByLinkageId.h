/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetRecordByLinkageId_H_
#define _LC_OPENAPI_CLIENT_GetRecordByLinkageId_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据联动消息ID获取云录像

 */

typedef struct GetRecordByLinkageIdRequest 
{
	LCOpenApiRequest base;

	struct GetRecordByLinkageIdRequestData
	{
		
		/** 录像类型,1000报警云录像,2000定时云录像,3000透传报警录像 */
		CSTR type;
		/** [cstr]getRecordByLinkageId */
		#define _STATIC_GetRecordByLinkageIdRequestData_method "getRecordByLinkageId"
		CSTR method;
		/** 联动消息id */
		CSTR linkageId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetRecordByLinkageIdRequest;

C_API GetRecordByLinkageIdRequest *LCOPENAPI_INIT(GetRecordByLinkageIdRequest);

typedef struct GetRecordByLinkageIdResponse 
{
	LCOpenApiResponse base;

	struct GetRecordByLinkageIdResponseData
	{
		
		/** 设备本地结束时间 */
		CSTR localEndTime;
		/** 录像文件路径 */
		CSTR recordPath;
		/** 缩略图URL */
		CSTR thumbUrl;
		/** 区域 */
		CSTR region;
		/** 录像ID */
		CSTR recordId;
		/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
		int encryptMode;
		/** 设备本地开始时间 */
		CSTR localBeginTime;
		/** 云录像的大小，单位byte */
		CSTR size;
 
	} data;

} GetRecordByLinkageIdResponse;

C_API GetRecordByLinkageIdResponse *LCOPENAPI_INIT(GetRecordByLinkageIdResponse);

#endif
