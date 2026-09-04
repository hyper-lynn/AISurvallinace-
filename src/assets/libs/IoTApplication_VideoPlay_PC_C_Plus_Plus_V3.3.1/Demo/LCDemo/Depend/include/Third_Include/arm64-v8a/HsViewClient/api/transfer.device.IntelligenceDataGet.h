/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_IntelligenceDataGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_IntelligenceDataGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
智能采集数据获取

参考PaaS协议：[智能采集数据获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%99%BA%E8%83%BD%E9%87%87%E9%9B%86%E6%95%B0%E6%8D%AE%E8%8E%B7%E5%8F%96%2F%E6%99%BA%E8%83%BD%E9%87%87%E9%9B%86%E6%95%B0%E6%8D%AE%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_IntelligenceDataGetRequest 
{
	HsviewRequest base;

	struct transferDevice_IntelligenceDataGetRequestData
	{
		
		/** [cstr]/device/intelligence/data */
		#define _STATIC_transferDevice_IntelligenceDataGetRequestData_url "/device/intelligence/data"
		CSTR url;
		/** struct of transferDevice_IntelligenceDataGetRequestData_Content */
		struct transferDevice_IntelligenceDataGetRequestData_Content {
			/** heatmap */
			CSTR type;
			/** UTC采集结束时间，yyyyMMddTHHmmssZ格式 */
			CSTR utcEndTime;
			/** 设备本地采集结束时间，yyyyMMddTHHmmss格式 */
			CSTR localEndTime;
			/** 通道号 */
			CSTR channelId;
			/** UTC采集开始时间，yyyyMMddTHHmmssZ格式 */
			CSTR utcBeginTime;
			/** 设备本地采集开始时间，yyyyMMddTHHmmss格式 */
			CSTR localBeginTime;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_IntelligenceDataGetRequest;

C_API transferDevice_IntelligenceDataGetRequest *HSAPI_INIT(transferDevice_IntelligenceDataGetRequest);

typedef struct transferDevice_IntelligenceDataGetResponse 
{
	HsviewResponse base;

	struct transferDevice_IntelligenceDataGetResponseData
	{
		
		/** struct of transferDevice_IntelligenceDataGetResponseData_Details */
		struct transferDevice_IntelligenceDataGetResponseData_Details {
			/** [O]热度最小值 */
			CSTR min;
			/** [O]热度最大值 */
			CSTR max;
			/** [O]图片高度 */
			CSTR height;
			/** [O]热度图原始数据灰阶位图，Base64(Binary Data) */
			CSTR heatData;
			/** [O]热度平均值 */
			CSTR average;
			/** [O]图片宽度 */
			CSTR width;
		} details;
 
	} data;

} transferDevice_IntelligenceDataGetResponse;

C_API transferDevice_IntelligenceDataGetResponse *HSAPI_INIT(transferDevice_IntelligenceDataGetResponse);

#endif
