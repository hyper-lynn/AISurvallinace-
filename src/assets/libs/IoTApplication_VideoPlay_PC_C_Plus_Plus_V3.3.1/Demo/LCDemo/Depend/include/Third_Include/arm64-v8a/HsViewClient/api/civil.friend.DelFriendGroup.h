/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelFriendGroup_H_
#define _HSVIEW_CLIENT_API_DelFriendGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户删除好友分组

【需要使用平台账号签名】
 */

typedef struct DelFriendGroupRequest 
{
	HsviewRequest base;

	struct DelFriendGroupRequestData
	{
		
		/** [long]分组id */
		int64 groupId;

	} data;

} DelFriendGroupRequest;

C_API DelFriendGroupRequest *HSAPI_INIT(DelFriendGroupRequest);

typedef struct DelFriendGroupResponse 
{
	HsviewResponse base;

	struct DelFriendGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelFriendGroupResponse;

C_API DelFriendGroupResponse *HSAPI_INIT(DelFriendGroupResponse);

#endif
