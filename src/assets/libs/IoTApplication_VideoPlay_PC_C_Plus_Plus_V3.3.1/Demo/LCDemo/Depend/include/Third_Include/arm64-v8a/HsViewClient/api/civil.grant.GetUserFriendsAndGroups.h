/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserFriendsAndGroups_H_
#define _HSVIEW_CLIENT_API_GetUserFriendsAndGroups_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取授权对象列表
【需要使用平台账号签名】

 */

typedef struct GetUserFriendsAndGroupsRequest 
{
	HsviewRequest base;

	struct GetUserFriendsAndGroupsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUserFriendsAndGroupsRequest;

C_API GetUserFriendsAndGroupsRequest *HSAPI_INIT(GetUserFriendsAndGroupsRequest);

typedef struct GetUserFriendsAndGroupsResponse 
{
	HsviewResponse base;

	struct GetUserFriendsAndGroupsResponseData
	{
		
		/** define a list with struct of GetUserFriendsAndGroupsResponseData_TargetsElement */
		DECLARE_LIST(struct GetUserFriendsAndGroupsResponseData_TargetsElement
		{
			/** define a list with struct of GetUserFriendsAndGroupsResponseData_TargetsElement_AuthTargetGroupsElement */
			DECLARE_LIST(struct GetUserFriendsAndGroupsResponseData_TargetsElement_AuthTargetGroupsElement
			{
				/** 分组中第一个好友头像 */
				CSTR userIcon;
				/** 授权分组名称 */
				CSTR name;
				/** [long]分组Id */
				int64 groupId;
			}) authTargetGroups;
			/** define a list with struct of GetUserFriendsAndGroupsResponseData_TargetsElement_AuthTargetFirendsElement */
			DECLARE_LIST(struct GetUserFriendsAndGroupsResponseData_TargetsElement_AuthTargetFirendsElement
			{
				/** 好友自己的昵称 */
				CSTR nickname;
				/** 好友头像 */
				CSTR userIcon;
				/** 好友备注说明 */
				CSTR remark;
				/** 授权好友手机 */
				CSTR userName;
				/** 好友别名 */
				CSTR alias;
				/** [long]好友Id */
				int64 firendId;
			}) authTargetFirends;
		}) targets;
 
	} data;

} GetUserFriendsAndGroupsResponse;

C_API GetUserFriendsAndGroupsResponse *HSAPI_INIT(GetUserFriendsAndGroupsResponse);

#endif
