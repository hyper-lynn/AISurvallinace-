/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFriendClient_H_
#define _HSVIEW_CLIENT_API_GetFriendClient_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊好友的客户端列表，用于发起呼叫。
【使用平台账号签名】
 */

typedef struct GetFriendClientRequest 
{
	HsviewRequest base;

	struct GetFriendClientRequestData
	{
		
		/** 平台账号 */
		CSTR username;

	} data;

} GetFriendClientRequest;

C_API GetFriendClientRequest *HSAPI_INIT(GetFriendClientRequest);

typedef struct GetFriendClientResponse 
{
	HsviewResponse base;

	struct GetFriendClientResponseData
	{
		
		/** define a list with struct of GetFriendClientResponseData_ClientsElement */
		DECLARE_LIST(struct GetFriendClientResponseData_ClientsElement
		{
			/** 客户端类型，“phone”代表手机，“box”代表盒子 */
			CSTR clientType;
			/** 客户端Id，与初始化视频服务器clientId相同 */
			CSTR clientId;
		}) clients;
 
	} data;

} GetFriendClientResponse;

C_API GetFriendClientResponse *HSAPI_INIT(GetFriendClientResponse);

#endif
