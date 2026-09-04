/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AliasFriend_H_
#define _HSVIEW_CLIENT_API_AliasFriend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置橙聊好友别名和备注。
【使用平台账号签名】
 */

typedef struct AliasFriendRequest 
{
	HsviewRequest base;

	struct AliasFriendRequestData
	{
		
		/** 好友账号 */
		CSTR username;
		/** 好友别名 */
		CSTR alias;
		/** 好友备注 */
		CSTR remark;

	} data;

} AliasFriendRequest;

C_API AliasFriendRequest *HSAPI_INIT(AliasFriendRequest);

typedef struct AliasFriendResponse 
{
	HsviewResponse base;

	struct AliasFriendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AliasFriendResponse;

C_API AliasFriendResponse *HSAPI_INIT(AliasFriendResponse);

#endif
