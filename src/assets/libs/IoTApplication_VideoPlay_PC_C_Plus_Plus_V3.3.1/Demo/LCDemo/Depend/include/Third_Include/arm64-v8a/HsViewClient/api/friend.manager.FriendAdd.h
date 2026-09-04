/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendAdd_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加好友

【使用平台账号签名】
 */

typedef struct friendManager_FriendAddRequest 
{
	HsviewRequest base;

	struct friendManager_FriendAddRequestData
	{
		
		/** 需要添加的好友账号，手机号或者邮箱号 */
		CSTR account;

	} data;

} friendManager_FriendAddRequest;

C_API friendManager_FriendAddRequest *HSAPI_INIT(friendManager_FriendAddRequest);

typedef struct friendManager_FriendAddResponse 
{
	HsviewResponse base;

	struct friendManager_FriendAddResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} friendManager_FriendAddResponse;

C_API friendManager_FriendAddResponse *HSAPI_INIT(friendManager_FriendAddResponse);

#endif
