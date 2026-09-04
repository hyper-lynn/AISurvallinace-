/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_WakeupFriendClient_H_
#define _HSVIEW_CLIENT_API_WakeupFriendClient_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 唤醒好友客户端，用于主叫方在发起橙聊呼叫前先进行橙聊预准备工作-唤醒被叫好友的橙聊应用. 
【使用平台账号签名】
 */

typedef struct WakeupFriendClientRequest 
{
	HsviewRequest base;

	struct WakeupFriendClientRequestData
	{
		
		/** 好友账号 */
		CSTR username;

	} data;

} WakeupFriendClientRequest;

C_API WakeupFriendClientRequest *HSAPI_INIT(WakeupFriendClientRequest);

typedef struct WakeupFriendClientResponse 
{
	HsviewResponse base;

	struct WakeupFriendClientResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} WakeupFriendClientResponse;

C_API WakeupFriendClientResponse *HSAPI_INIT(WakeupFriendClientResponse);

#endif
