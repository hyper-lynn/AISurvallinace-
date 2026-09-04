/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdateFriendGroup_H_
#define _HSVIEW_CLIENT_API_UpdateFriendGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户修改分组名称

【需要使用平台账号签名】

 */

typedef struct UpdateFriendGroupRequest 
{
	HsviewRequest base;

	struct UpdateFriendGroupRequestData
	{
		
		/** 分组名称 */
		CSTR groupName;
		/** [long]分组id */
		int64 groupId;

	} data;

} UpdateFriendGroupRequest;

C_API UpdateFriendGroupRequest *HSAPI_INIT(UpdateFriendGroupRequest);

typedef struct UpdateFriendGroupResponse 
{
	HsviewResponse base;

	struct UpdateFriendGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpdateFriendGroupResponse;

C_API UpdateFriendGroupResponse *HSAPI_INIT(UpdateFriendGroupResponse);

#endif
