/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryJoinInfo_H_
#define _HSVIEW_CLIENT_API_QueryJoinInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户获取参加活动信息

1、当userId为0时，表示当前登录鉴权用户；
2、当isJoin为true时，url为必须字段返回。


错误码：

1、1504 ：直播活动不存在

【需要乐橙账号鉴权】
 */

typedef struct QueryJoinInfoRequest 
{
	HsviewRequest base;

	struct QueryJoinInfoRequestData
	{
		
		/** [long]用户id */
		int64 userId;
		/** [long]活动id */
		int64 activityId;

	} data;

} QueryJoinInfoRequest;

C_API QueryJoinInfoRequest *HSAPI_INIT(QueryJoinInfoRequest);

typedef struct QueryJoinInfoResponse 
{
	HsviewResponse base;

	struct QueryJoinInfoResponseData
	{
		
		/** [bool]userId对应的用户是否参加过该活动 */
		BOOL isJoin;
		/** [O]userId对应的用户拉票分享的url */
		CSTR url;
 
	} data;

} QueryJoinInfoResponse;

C_API QueryJoinInfoResponse *HSAPI_INIT(QueryJoinInfoResponse);

#endif
