/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_GenerateRecordUrlById_H_
#define _HSVIEW_CLIENT_API_cloudRecord_GenerateRecordUrlById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
生成云存储录像的URL用于客户端播放。

【使用平台账号签名】
 */

typedef struct cloudRecord_GenerateRecordUrlByIdRequest 
{
	HsviewRequest base;

	struct cloudRecord_GenerateRecordUrlByIdRequestData
	{
		
		/** 录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 区域 */
		CSTR region;
		/** [long]录像ID */
		int64 recordId;
		/** 通道号 */
		CSTR channelId;
		/** 录像文件路径 */
		CSTR recordPath;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} cloudRecord_GenerateRecordUrlByIdRequest;

C_API cloudRecord_GenerateRecordUrlByIdRequest *HSAPI_INIT(cloudRecord_GenerateRecordUrlByIdRequest);

typedef struct cloudRecord_GenerateRecordUrlByIdResponse 
{
	HsviewResponse base;

	struct cloudRecord_GenerateRecordUrlByIdResponseData
	{
		
		/** 用于播放此段录像的临时令牌 */
		CSTR token;
		/** 用于播放的录像URL地址 */
		CSTR url;
 
	} data;

} cloudRecord_GenerateRecordUrlByIdResponse;

C_API cloudRecord_GenerateRecordUrlByIdResponse *HSAPI_INIT(cloudRecord_GenerateRecordUrlByIdResponse);

#endif
