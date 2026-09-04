/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AliasFriendPlus_H_
#define _HSVIEW_CLIENT_API_AliasFriendPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置橙聊好友别名和备注。
【使用平台账号签名】
 */

typedef struct AliasFriendPlusRequest 
{
	HsviewRequest base;

	struct AliasFriendPlusRequestData
	{
		
		/** 好友备注 */
		CSTR remark;
		/** 好友别名 */
		CSTR alias;
		/** 好友的用户ID */
		CSTR userId;

	} data;

} AliasFriendPlusRequest;

C_API AliasFriendPlusRequest *HSAPI_INIT(AliasFriendPlusRequest);

typedef struct AliasFriendPlusResponse 
{
	HsviewResponse base;

	struct AliasFriendPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AliasFriendPlusResponse;

C_API AliasFriendPlusResponse *HSAPI_INIT(AliasFriendPlusResponse);

#endif
