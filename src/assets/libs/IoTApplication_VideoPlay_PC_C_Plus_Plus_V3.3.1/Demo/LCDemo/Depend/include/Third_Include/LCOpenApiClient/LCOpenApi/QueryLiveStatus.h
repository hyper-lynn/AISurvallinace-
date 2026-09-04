/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLiveStatus_H_
#define _LC_OPENAPI_CLIENT_QueryLiveStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取直播状态
 */

typedef struct QueryLiveStatusRequest 
{
	LCOpenApiRequest base;

	struct QueryLiveStatusRequestData
	{
		
		/** 授权的管理员token(accessToken) */
		CSTR token;
		/**  */
		CSTR liveToken;

	} data;

} QueryLiveStatusRequest;

C_API QueryLiveStatusRequest *LCOPENAPI_INIT(QueryLiveStatusRequest);

typedef struct QueryLiveStatusResponse 
{
	LCOpenApiResponse base;

	struct QueryLiveStatusResponseData
	{
		
		/** define a list with struct of QueryLiveStatusResponseData_StreamsElement */
		DECLARE_LIST(struct QueryLiveStatusResponseData_StreamsElement
		{
			/** [int]码流类型（0:主码流；1:辅码流） */
			int streamId;
			/** 0:正在直播中,1:正在直播中，但是视频封面异常,2:视频源异常,3:码流转换异常,4:云存储访问异常,10:直播暂停中 */
			CSTR status;
		}) streams;
 
	} data;

} QueryLiveStatusResponse;

C_API QueryLiveStatusResponse *LCOPENAPI_INIT(QueryLiveStatusResponse);

#endif
