/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_InviteFriend_H_
#define _HSVIEW_CLIENT_API_InviteFriend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 邀请对方加入橙聊应用，平台收到该消息后向对方手机号发送一条邀请短信。
【使用平台账号签名】
 */

typedef struct InviteFriendRequest 
{
	HsviewRequest base;

	struct InviteFriendRequestData
	{
		
		/** 对方手机号 */
		CSTR phoneNumber;

	} data;

} InviteFriendRequest;

C_API InviteFriendRequest *HSAPI_INIT(InviteFriendRequest);

typedef struct InviteFriendResponse 
{
	HsviewResponse base;

	struct InviteFriendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} InviteFriendResponse;

C_API InviteFriendResponse *HSAPI_INIT(InviteFriendResponse);

#endif
