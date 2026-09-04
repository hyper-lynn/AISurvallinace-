/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_JoinActivity_H_
#define _HSVIEW_CLIENT_API_JoinActivity_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户提交参加活动信息
data内的数据为json格式的字符串，平台不对具体内容做限制和校验


错误码：
1、1504 ：直播活动不存在
2、1506 ：活动未发布
3、1507 ：活动未开始 
4、1508 ：活动已结束
5、1510 ：用户已参加活动
【需要乐橙账号鉴权】
 */

typedef struct JoinActivityRequest 
{
	HsviewRequest base;

	struct JoinActivityRequestData
	{
		
		/** [long]活动id */
		int64 activityId;
		/** 提交的参加活动内容，格式为json串 */
		CSTR data;

	} data;

} JoinActivityRequest;

C_API JoinActivityRequest *HSAPI_INIT(JoinActivityRequest);

typedef struct JoinActivityResponse 
{
	HsviewResponse base;

	struct JoinActivityResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} JoinActivityResponse;

C_API JoinActivityResponse *HSAPI_INIT(JoinActivityResponse);

#endif
