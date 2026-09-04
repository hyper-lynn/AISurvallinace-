/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetHeatMapData_H_
#define _LC_OPENAPI_CLIENT_GetHeatMapData_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
热度图数据获取

 */

typedef struct GetHeatMapDataRequest 
{
	LCOpenApiRequest base;

	struct GetHeatMapDataRequestData
	{
		
		/** UTC采集结束时间 */
		CSTR utcEndTime;
		/** [cstr]getHeatMapData */
		#define _STATIC_GetHeatMapDataRequestData_method "getHeatMapData"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备本地采集结束时间 */
		CSTR localEndTime;
		/** 设备本地采集开始时间 */
		CSTR localBeginTime;
		/** 通道ID */
		CSTR channelId;
		/** UTC采集开始时间 */
		CSTR utcBeginTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetHeatMapDataRequest;

C_API GetHeatMapDataRequest *LCOPENAPI_INIT(GetHeatMapDataRequest);

typedef struct GetHeatMapDataResponse 
{
	LCOpenApiResponse base;

	struct GetHeatMapDataResponseData
	{
		
		/** struct of GetHeatMapDataResponseData_Details */
		struct GetHeatMapDataResponseData_Details {
			/** 可选(新增字段)，热度最小值 */
			CSTR min;
			/** 可选(新增字段)，热度最大值 */
			CSTR max;
			/** 图片高度 */
			CSTR height;
			/** 热度图原始数据灰阶位图，Base64(Binary Data) */
			CSTR heatData;
			/** 可选(新增字段)，热度均值 */
			CSTR average;
			/** 图片宽度 */
			CSTR width;
		} details;
 
	} data;

} GetHeatMapDataResponse;

C_API GetHeatMapDataResponse *LCOPENAPI_INIT(GetHeatMapDataResponse);

#endif
