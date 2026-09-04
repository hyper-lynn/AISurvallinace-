/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicFlowList_H_
#define _HSVIEW_CLIENT_API_QueryPublicFlowList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询相应时间段内每小时或者每天的直播产生的流量

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicFlowListRequest 
{
	HsviewRequest base;

	struct QueryPublicFlowListRequestData
	{
		
		/** define a list with struct of QueryPublicFlowListRequestData_LivesElement */
		DECLARE_LIST(struct QueryPublicFlowListRequestData_LivesElement
		{
			/** 直播流类型，可选rtsp,hls,rtmp */
			CSTR type;
			/** 直播分享的token */
			CSTR token;
			/** 201607062300, 结束时间，格式为yyyyMMddHHmm */
			CSTR endTime;
			/** 201607061258，起始时间，格式为yyyyMMddHHmm */
			CSTR startTime;
			/** 可选day，hour */
			CSTR countType;
		}) lives;

	} data;

} QueryPublicFlowListRequest;

C_API QueryPublicFlowListRequest *HSAPI_INIT(QueryPublicFlowListRequest);

typedef struct QueryPublicFlowListResponse 
{
	HsviewResponse base;

	struct QueryPublicFlowListResponseData
	{
		
		/** define a list with struct of QueryPublicFlowListResponseData_FlowsElement */
		DECLARE_LIST(struct QueryPublicFlowListResponseData_FlowsElement
		{
			/** 直播分享的token */
			CSTR token;
			/** define a list with struct of QueryPublicFlowListResponseData_FlowsElement_TimeFlowElement */
			DECLARE_LIST(struct QueryPublicFlowListResponseData_FlowsElement_TimeFlowElement
			{
				/** [O]时间，格式为yyyyMMddHHmm */
				CSTR time;
				/** [long]流量，单位MB */
				int64 flow;
			}) timeFlow;
		}) flows;
 
	} data;

} QueryPublicFlowListResponse;

C_API QueryPublicFlowListResponse *HSAPI_INIT(QueryPublicFlowListResponse);

#endif
