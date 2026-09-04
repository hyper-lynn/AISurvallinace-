/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddFriendGroup_H_
#define _HSVIEW_CLIENT_API_AddFriendGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户创建好友分组，添加成功后返回该分组的id

【需要使用平台账号签名】
 */

typedef struct AddFriendGroupRequest 
{
	HsviewRequest base;

	struct AddFriendGroupRequestData
	{
		
		/** 分组名称 */
		CSTR groupName;

	} data;

} AddFriendGroupRequest;

C_API AddFriendGroupRequest *HSAPI_INIT(AddFriendGroupRequest);

typedef struct AddFriendGroupResponse 
{
	HsviewResponse base;

	struct AddFriendGroupResponseData
	{
		
		/** [long]分组id */
		int64 groupId;
 
	} data;

} AddFriendGroupResponse;

C_API AddFriendGroupResponse *HSAPI_INIT(AddFriendGroupResponse);

#endif
