/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225862, Author: 112352, Date: 2024-01-31 14:56:01 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GenerateRecordUrlById_H_
#define _LC_OPENAPI_CLIENT_GenerateRecordUrlById_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取云录像地址
错误码:
10004：超过指定路数，拒绝给予RTSP地址
10005：超过指定个流量，拒绝给予RTSP地址
备注：
beginTime和endTime为云睿私有化平台新增字段，解决PAAS平台不支持按文件（recordId）查询录像问题。

 */

typedef struct GenerateRecordUrlByIdRequest 
{
	LCOpenApiRequest base;

	struct GenerateRecordUrlByIdRequestData
	{
		
		/** 1000报警云录像,2000定时云录像 */
		CSTR type;
		/** 录像ID */
		CSTR recordId;
		/** 设备ID */
		CSTR deviceId;
		/** 录像regionId */
		CSTR recordRegionId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 录像记录（若下载dav文件，则为m3u中dav路径）；公有云专用 */
		CSTR recordPath;
		/** 通道ID */
		CSTR channelId;
		/** 结束时间，如2021-03-01 23:59:59 */
		CSTR endTime;
		/** 开始时间，如2021-03-01 00:00:00 */
		CSTR beginTime;

	} data;

} GenerateRecordUrlByIdRequest;

C_API GenerateRecordUrlByIdRequest *LCOPENAPI_INIT(GenerateRecordUrlByIdRequest);

typedef struct GenerateRecordUrlByIdResponse 
{
	LCOpenApiResponse base;

	struct GenerateRecordUrlByIdResponseData
	{
		
		/** 用于播放此段录像的临时令牌；公有云使用，有效期1小时，用于授权dav切片 */
		CSTR token;
		/** 返回的m3u8或dav下载地址 */
		CSTR url;
 
	} data;

} GenerateRecordUrlByIdResponse;

C_API GenerateRecordUrlByIdResponse *LCOPENAPI_INIT(GenerateRecordUrlByIdResponse);

#endif
