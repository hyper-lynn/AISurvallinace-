/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AcceptFriendPlus_H_
#define _HSVIEW_CLIENT_API_AcceptFriendPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
接受好友请求。
【使用平台账号签名】
 */

typedef struct AcceptFriendPlusRequest 
{
	HsviewRequest base;

	struct AcceptFriendPlusRequestData
	{
		
		/** 接受的好友用户ID */
		CSTR userId;
		/** [bool]是否接受这个好友 */
		BOOL accept;

	} data;

} AcceptFriendPlusRequest;

C_API AcceptFriendPlusRequest *HSAPI_INIT(AcceptFriendPlusRequest);

typedef struct AcceptFriendPlusResponse 
{
	HsviewResponse base;

	struct AcceptFriendPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AcceptFriendPlusResponse;

C_API AcceptFriendPlusResponse *HSAPI_INIT(AcceptFriendPlusResponse);

#endif
