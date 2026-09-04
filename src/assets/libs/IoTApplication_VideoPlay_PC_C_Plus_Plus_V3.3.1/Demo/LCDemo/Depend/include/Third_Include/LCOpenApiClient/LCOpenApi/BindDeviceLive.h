/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDeviceLive_H_
#define _LC_OPENAPI_CLIENT_BindDeviceLive_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
创建设备源直播地址
 */

typedef struct BindDeviceLiveRequest 
{
	LCOpenApiRequest base;

	struct BindDeviceLiveRequestData
	{
		
		/** 授权的管理员token(accessToken) */
		CSTR token;
		/** [int]码流类型（0:主码流；1:辅码流） */
		int streamId;
		/** 通道号 */
		CSTR channelId;
		/** 直播类型（cdn:通用直播；proxy:经济型直播） */
		CSTR liveMode;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} BindDeviceLiveRequest;

C_API BindDeviceLiveRequest *LCOPENAPI_INIT(BindDeviceLiveRequest);

typedef struct BindDeviceLiveResponse 
{
	LCOpenApiResponse base;

	struct BindDeviceLiveResponseData
	{
		
		/** define a list with struct of BindDeviceLiveResponseData_JobElement */
		DECLARE_LIST(struct BindDeviceLiveResponseData_JobElement
		{
			/** [bool]直播计划状态（true:开；false:关） */
			BOOL status;
			/** 任务周期 */
			CSTR period;
		}) job;
		/** 直播授权token */
		CSTR liveToken;
		/** define a list with struct of BindDeviceLiveResponseData_StreamsElement */
		DECLARE_LIST(struct BindDeviceLiveResponseData_StreamsElement
		{
			/** 直播流hls访问地址 */
			CSTR hls;
			/** [int]码流类型（0:主码流；1:辅码流）(当直播地址由rtsp源生成时，无该字段) */
			int streamId;
			/** 视频封面url */
			CSTR coverUrl;
		}) streams;
		/** [int]视频封面更新频率（单位：s） */
		int coverUpdate;
		/** [int]直播状态（1：开启；2：暂停；3：流量不足） */
		int liveStatus;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;
		/** [int]直播源类型（1：设备；2：流地址） */
		int liveType;
 
	} data;

} BindDeviceLiveResponse;

C_API BindDeviceLiveResponse *LCOPENAPI_INIT(BindDeviceLiveResponse);

#endif
