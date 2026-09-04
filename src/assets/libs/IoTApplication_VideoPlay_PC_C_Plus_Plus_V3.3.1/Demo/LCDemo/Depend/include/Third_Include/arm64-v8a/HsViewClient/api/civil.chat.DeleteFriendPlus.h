/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteFriendPlus_H_
#define _HSVIEW_CLIENT_API_DeleteFriendPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除橙聊好友。
【使用平台账号签名】
 */

typedef struct DeleteFriendPlusRequest 
{
	HsviewRequest base;

	struct DeleteFriendPlusRequestData
	{
		
		/** 需要删除的好友用户ID */
		CSTR userId;

	} data;

} DeleteFriendPlusRequest;

C_API DeleteFriendPlusRequest *HSAPI_INIT(DeleteFriendPlusRequest);

typedef struct DeleteFriendPlusResponse 
{
	HsviewResponse base;

	struct DeleteFriendPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteFriendPlusResponse;

C_API DeleteFriendPlusResponse *HSAPI_INIT(DeleteFriendPlusResponse);

#endif
