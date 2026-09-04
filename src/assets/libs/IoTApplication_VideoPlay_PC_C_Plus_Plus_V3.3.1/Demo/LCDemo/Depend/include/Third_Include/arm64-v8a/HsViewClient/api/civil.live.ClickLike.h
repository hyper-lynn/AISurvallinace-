/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ClickLike_H_
#define _HSVIEW_CLIENT_API_ClickLike_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据活动id对活动进行点赞，返回活动的总点赞数
当请求参数type为2时，userId为必须字段
错误码：
1、1504 ：直播活动不存在

【使用平台账号签名】
 */

typedef struct ClickLikeRequest 
{
	HsviewRequest base;

	struct ClickLikeRequestData
	{
		
		/** [long]活动id */
		int64 activityId;
		/** [int]点赞类型 1-对该文章或活动点赞  2-对userId参加该活动的内容点赞 */
		int type;
		/** [long][O]用户ID */
		int64 userId;

	} data;

} ClickLikeRequest;

C_API ClickLikeRequest *HSAPI_INIT(ClickLikeRequest);

typedef struct ClickLikeResponse 
{
	HsviewResponse base;

	struct ClickLikeResponseData
	{
		
		/** [long]type为1表示当前文章或活动总的点赞次数；type为2表示对userId参加该活动的总点赞次数 */
		int64 likeTimes;
 
	} data;

} ClickLikeResponse;

C_API ClickLikeResponse *HSAPI_INIT(ClickLikeResponse);

#endif
