/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPushMessageCenter_H_
#define _HSVIEW_CLIENT_API_GetPushMessageCenter_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询推送中心信息


【使用平台账号签名】
 */

typedef struct GetPushMessageCenterRequest 
{
	HsviewRequest base;

	struct GetPushMessageCenterRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetPushMessageCenterRequest;

C_API GetPushMessageCenterRequest *HSAPI_INIT(GetPushMessageCenterRequest);

typedef struct GetPushMessageCenterResponse 
{
	HsviewResponse base;

	struct GetPushMessageCenterResponseData
	{
		
		/** define a list with struct of GetPushMessageCenterResponseData_MessagesElement */
		DECLARE_LIST(struct GetPushMessageCenterResponseData_MessagesElement
		{
			/** [long]产生时间UNIX时间戳秒 */
			int64 time;
			/** 标题 */
			CSTR title;
			/** [O]标题图片的url */
			CSTR imgUrl;
			/** [long]消息ID */
			int64 msgId;
			/** [O]消息对应的网页url */
			CSTR url;
			/** [int]消息类型：0-系统消息  1-活动消息  2-个人消息 3-留言消息 4-资讯消息 */
			int msgType;
			/** [O]内容 */
			CSTR content;
		}) messages;
 
	} data;

} GetPushMessageCenterResponse;

C_API GetPushMessageCenterResponse *HSAPI_INIT(GetPushMessageCenterResponse);

#endif
