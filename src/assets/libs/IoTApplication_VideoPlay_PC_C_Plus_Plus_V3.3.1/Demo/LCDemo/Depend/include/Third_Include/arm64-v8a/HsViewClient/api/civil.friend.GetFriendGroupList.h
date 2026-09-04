/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFriendGroupList_H_
#define _HSVIEW_CLIENT_API_GetFriendGroupList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取用户的分组列表

【需要使用平台账号签名】

 */

typedef struct GetFriendGroupListRequest 
{
	HsviewRequest base;

	struct GetFriendGroupListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetFriendGroupListRequest;

C_API GetFriendGroupListRequest *HSAPI_INIT(GetFriendGroupListRequest);

typedef struct GetFriendGroupListResponse 
{
	HsviewResponse base;

	struct GetFriendGroupListResponseData
	{
		
		/** define a list with struct of GetFriendGroupListResponseData_GroupsElement */
		DECLARE_LIST(struct GetFriendGroupListResponseData_GroupsElement
		{
			/** 好友分组的封面，当前使用每个分组的第一个好友头像作为封面 */
			CSTR groupCover;
			/** [bool]是否已授权 */
			BOOL isAuth;
			/** 分组名称 */
			CSTR groupName;
			/** [long]分组id */
			int64 groupId;
		}) groups;
 
	} data;

} GetFriendGroupListResponse;

C_API GetFriendGroupListResponse *HSAPI_INIT(GetFriendGroupListResponse);

#endif
