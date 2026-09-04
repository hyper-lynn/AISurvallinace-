/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendListGet_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取好友列表。

当请求中userId不存在或者为空，表示获取全量所有好友列表。
当请求中userId存在且不为空时,只返回平台上存在的好友id对应的好友信息。

【使用平台账号签名】
 */

typedef struct friendManager_FriendListGetRequest 
{
	HsviewRequest base;

	struct friendManager_FriendListGetRequestData
	{
		
		/** [long]需要查询的好友用户ID */
		DECLARE_LIST(int64) userId;

	} data;

} friendManager_FriendListGetRequest;

C_API friendManager_FriendListGetRequest *HSAPI_INIT(friendManager_FriendListGetRequest);

typedef struct friendManager_FriendListGetResponse 
{
	HsviewResponse base;

	struct friendManager_FriendListGetResponseData
	{
		
		/** define a list with struct of friendManager_FriendListGetResponseData_FriendListElement */
		DECLARE_LIST(struct friendManager_FriendListGetResponseData_FriendListElement
		{
			/** [O]用户头像 */
			CSTR userIcon;
			/** [O]好友备注说明 */
			CSTR remark;
			/** [O]好友自己的昵称 */
			CSTR nickname;
			/** [O]自己设置的好友别名，APP上好友详情中设置的备注名 */
			CSTR alias;
			/** [long]用户ID */
			int64 userId;
			/** 平台账号, 账号中间会有*进行敏感信息加密 */
			CSTR account;
		}) friendList;
 
	} data;

} friendManager_FriendListGetResponse;

C_API friendManager_FriendListGetResponse *HSAPI_INIT(friendManager_FriendListGetResponse);

#endif
