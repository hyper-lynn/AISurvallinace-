/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LiveList_H_
#define _LC_OPENAPI_CLIENT_LiveList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取直播列表
 */

typedef struct LiveListRequest 
{
	LCOpenApiRequest base;

	struct LiveListRequestData
	{
		
		/** 授权的管理员token(accessToken) */
		CSTR token;
		/** 单次查询上限100,1-30表示第1条到第30条,包含30 */
		CSTR queryRange;

	} data;

} LiveListRequest;

C_API LiveListRequest *LCOPENAPI_INIT(LiveListRequest);

typedef struct LiveListResponse 
{
	LCOpenApiResponse base;

	struct LiveListResponseData
	{
		
		/** [int] 当前抽取设备总数 */
		int count;
		/** define a list with struct of LiveListResponseData_LivesElement */
		DECLARE_LIST(struct LiveListResponseData_LivesElement
		{
			/** define a list with struct of LiveListResponseData_LivesElement_JobElement */
			DECLARE_LIST(struct LiveListResponseData_LivesElement_JobElement
			{
				/** [bool][可选]直播计划状态（true:开；false:关） */
				BOOL status;
				/** 开始时间 */
				CSTR beginTime;
				/** 任务周期 */
				CSTR period;
				/** 结束时间 */
				CSTR endTime;
			}) job;
			/** 直播授权token */
			CSTR liveToken;
			/** define a list with struct of LiveListResponseData_LivesElement_StreamsElement */
			DECLARE_LIST(struct LiveListResponseData_LivesElement_StreamsElement
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
		}) lives;
 
	} data;

} LiveListResponse;

C_API LiveListResponse *LCOPENAPI_INIT(LiveListResponse);

#endif
