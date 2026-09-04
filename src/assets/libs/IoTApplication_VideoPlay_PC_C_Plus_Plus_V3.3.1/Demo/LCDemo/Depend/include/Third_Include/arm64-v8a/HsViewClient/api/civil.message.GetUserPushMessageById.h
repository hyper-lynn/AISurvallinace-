/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserPushMessageById_H_
#define _HSVIEW_CLIENT_API_GetUserPushMessageById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询用户的推送消息
【使用平台账号签名】
 */

typedef struct GetUserPushMessageByIdRequest 
{
	HsviewRequest base;

	struct GetUserPushMessageByIdRequestData
	{
		
		/** [long]消息id */
		int64 msgId;

	} data;

} GetUserPushMessageByIdRequest;

C_API GetUserPushMessageByIdRequest *HSAPI_INIT(GetUserPushMessageByIdRequest);

typedef struct GetUserPushMessageByIdResponse 
{
	HsviewResponse base;

	struct GetUserPushMessageByIdResponseData
	{
		
		/** [O]通道的ID */
		CSTR channelId;
		/** [int]消息类型 */
		int type;
		/** 标题 */
		CSTR title;
		/** [long]产生时间UNIX时间戳秒 */
		int64 time;
		/** [long]消息ID */
		int64 msgId;
		/** 个人推送消息的网页Url地址 */
		CSTR url;
		/** 内容 */
		CSTR content;
		/** [O]设备ID */
		CSTR deviceId;
 
	} data;

} GetUserPushMessageByIdResponse;

C_API GetUserPushMessageByIdResponse *HSAPI_INIT(GetUserPushMessageByIdResponse);

#endif
