/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicFlow_H_
#define _HSVIEW_CLIENT_API_QueryPublicFlow_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询相应时间段内的直播产生的流量

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicFlowRequest 
{
	HsviewRequest base;

	struct QueryPublicFlowRequestData
	{
		
		/** define a list with struct of QueryPublicFlowRequestData_LivesElement */
		DECLARE_LIST(struct QueryPublicFlowRequestData_LivesElement
		{
			/** 201607062300, 结束时间，格式为yyyyMMddHHmm */
			CSTR endTime;
			/** 201607061258，起始时间，格式为yyyyMMddHHmm */
			CSTR startTime;
			/** 直播分享的token */
			CSTR token;
			/** 直播流类型，可选rtsp,hls,rtmp */
			CSTR type;
		}) lives;

	} data;

} QueryPublicFlowRequest;

C_API QueryPublicFlowRequest *HSAPI_INIT(QueryPublicFlowRequest);

typedef struct QueryPublicFlowResponse 
{
	HsviewResponse base;

	struct QueryPublicFlowResponseData
	{
		
		/** define a list with struct of QueryPublicFlowResponseData_FlowsElement */
		DECLARE_LIST(struct QueryPublicFlowResponseData_FlowsElement
		{
			/** 直播分享的token */
			CSTR token;
			/** [long]10240, 指定时间内的总流量，单位MB */
			int64 totalFlow;
		}) flows;
 
	} data;

} QueryPublicFlowResponse;

C_API QueryPublicFlowResponse *HSAPI_INIT(QueryPublicFlowResponse);

#endif
