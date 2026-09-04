/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSystemMessageById_H_
#define _HSVIEW_CLIENT_API_GetSystemMessageById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询系统通知消息或活动消息
【使用平台账号签名】
 */

typedef struct GetSystemMessageByIdRequest 
{
	HsviewRequest base;

	struct GetSystemMessageByIdRequestData
	{
		
		/** [long]消息id */
		int64 msgId;

	} data;

} GetSystemMessageByIdRequest;

C_API GetSystemMessageByIdRequest *HSAPI_INIT(GetSystemMessageByIdRequest);

typedef struct GetSystemMessageByIdResponse 
{
	HsviewResponse base;

	struct GetSystemMessageByIdResponseData
	{
		
		/** [long]产生时间UNIX时间戳秒 */
		int64 time;
		/** 标题 */
		CSTR title;
		/** 标题图片的url */
		CSTR imgUrl;
		/** [long]消息ID */
		int64 msgId;
		/** 系统消息对应的网页url */
		CSTR url;
		/** 内容 */
		CSTR content;
		/** [int]消息类型：0-系统消息  1-活动消息  4-资讯消息 */
		int msgType;
 
	} data;

} GetSystemMessageByIdResponse;

C_API GetSystemMessageByIdResponse *HSAPI_INIT(GetSystemMessageByIdResponse);

#endif
