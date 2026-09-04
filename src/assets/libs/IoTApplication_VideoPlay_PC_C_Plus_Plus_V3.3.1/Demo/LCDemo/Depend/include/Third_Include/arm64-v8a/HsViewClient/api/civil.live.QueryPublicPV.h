/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPublicPV_H_
#define _HSVIEW_CLIENT_API_QueryPublicPV_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询相应时间段内访问次数，countType字段不填表示全部，否则为按天或者小时查询，默认包含开始天和结束天。

错误码：
1、1502 : 视频直播不存在

【使用平台账号签名】
 */

typedef struct QueryPublicPVRequest 
{
	HsviewRequest base;

	struct QueryPublicPVRequestData
	{
		
		/** define a list with struct of QueryPublicPVRequestData_LivesElement */
		DECLARE_LIST(struct QueryPublicPVRequestData_LivesElement
		{
			/** 直播流类型，可选rtsp,hls,rtmp */
			CSTR type;
			/** 直播分享的token */
			CSTR token;
			/** 201607062300, 结束时间，格式为yyyyMMddHHmm */
			CSTR endTime;
			/** 201607061258，起始时间，格式为yyyyMMddHHmm */
			CSTR startTime;
			/** [O]可选day，hour */
			CSTR countType;
		}) lives;

	} data;

} QueryPublicPVRequest;

C_API QueryPublicPVRequest *HSAPI_INIT(QueryPublicPVRequest);

typedef struct QueryPublicPVResponse 
{
	HsviewResponse base;

	struct QueryPublicPVResponseData
	{
		
		/** define a list with struct of QueryPublicPVResponseData_PVsStructElement */
		DECLARE_LIST(struct QueryPublicPVResponseData_PVsStructElement
		{
			/** 直播分享的token */
			CSTR token;
			/** define a list with struct of QueryPublicPVResponseData_PVsStructElement_PVStructElement */
			DECLARE_LIST(struct QueryPublicPVResponseData_PVsStructElement_PVStructElement
			{
				/** [O]时间，格式为yyyyMMddHHmm */
				CSTR time;
				/** [long]指定时间内的访问次数 */
				int64 counts;
			}) PV;
		}) PVs;
 
	} data;

} QueryPublicPVResponse;

C_API QueryPublicPVResponse *HSAPI_INIT(QueryPublicPVResponse);

#endif
