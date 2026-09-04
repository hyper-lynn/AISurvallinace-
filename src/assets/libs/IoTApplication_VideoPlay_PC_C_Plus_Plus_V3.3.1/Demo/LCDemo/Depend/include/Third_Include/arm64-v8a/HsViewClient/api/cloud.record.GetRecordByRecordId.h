/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_GetRecordByRecordId_H_
#define _HSVIEW_CLIENT_API_cloudRecord_GetRecordByRecordId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据录像id获取对应的云录像。

主要是用于留言消息时获取对应的云录像。

【使用平台账号签名】
 */

typedef struct cloudRecord_GetRecordByRecordIdRequest 
{
	HsviewRequest base;

	struct cloudRecord_GetRecordByRecordIdRequestData
	{
		
		/** [long]录像id */
		int64 recordId;
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 区域唯一标识id */
		CSTR region;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} cloudRecord_GetRecordByRecordIdRequest;

C_API cloudRecord_GetRecordByRecordIdRequest *HSAPI_INIT(cloudRecord_GetRecordByRecordIdRequest);

typedef struct cloudRecord_GetRecordByRecordIdResponse 
{
	HsviewResponse base;

	struct cloudRecord_GetRecordByRecordIdResponseData
	{
		
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** 录像文件路径 */
		CSTR recordPath;
		/** 缩略图URL */
		CSTR thumbUrl;
		/** 区域 */
		CSTR region;
		/** [long]录像ID */
		int64 recordId;
		/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
		int encryptMode;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** [long]云录像的大小，单位byte */
		int64 size;
 
	} data;

} cloudRecord_GetRecordByRecordIdResponse;

C_API cloudRecord_GetRecordByRecordIdResponse *HSAPI_INIT(cloudRecord_GetRecordByRecordIdResponse);

#endif
