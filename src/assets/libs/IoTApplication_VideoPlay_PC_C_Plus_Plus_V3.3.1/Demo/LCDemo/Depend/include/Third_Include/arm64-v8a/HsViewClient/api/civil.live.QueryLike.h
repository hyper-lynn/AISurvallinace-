/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryLike_H_
#define _HSVIEW_CLIENT_API_QueryLike_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据活动id对活动进行点赞，返回活动的总点赞数以及自己是否点赞

错误码：
1、1504 ：直播活动不存在

【使用平台账号签名】
 */

typedef struct QueryLikeRequest 
{
	HsviewRequest base;

	struct QueryLikeRequestData
	{
		
		/** [long]活动id */
		int64 activityId;

	} data;

} QueryLikeRequest;

C_API QueryLikeRequest *HSAPI_INIT(QueryLikeRequest);

typedef struct QueryLikeResponse 
{
	HsviewResponse base;

	struct QueryLikeResponseData
	{
		
		/** [long]当前活动总的点赞次数 */
		int64 likeTimes;
		/** [bool]自己是否点赞 */
		BOOL clickedFlag;
 
	} data;

} QueryLikeResponse;

C_API QueryLikeResponse *HSAPI_INIT(QueryLikeResponse);

#endif
