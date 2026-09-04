/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserAuthorizationList_H_
#define _HSVIEW_CLIENT_API_GetUserAuthorizationList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取授权列表
【需要使用平台账号签名】

 */

typedef struct GetUserAuthorizationListRequest 
{
	HsviewRequest base;

	struct GetUserAuthorizationListRequestData
	{
		
		/** [long]从该授权ID开始查询。若要从最新开始查，填-1 */
		int64 authId;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetUserAuthorizationListRequest;

C_API GetUserAuthorizationListRequest *HSAPI_INIT(GetUserAuthorizationListRequest);

typedef struct GetUserAuthorizationListResponse 
{
	HsviewResponse base;

	struct GetUserAuthorizationListResponseData
	{
		
		/** define a list with struct of GetUserAuthorizationListResponseData_AuthorizationsElement */
		DECLARE_LIST(struct GetUserAuthorizationListResponseData_AuthorizationsElement
		{
			/** struct of GetUserAuthorizationListResponseData_AuthorizationsElement_Role */
			struct GetUserAuthorizationListResponseData_AuthorizationsElement_Role {
				/** [long]角色Id */
				int64 roleId;
				/** 角色名称 */
				CSTR roleName;
				/** 权限列表 */
				CSTR authFunctions;
			} role;
			/** define a list with struct of GetUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetFirendsElement */
			DECLARE_LIST(struct GetUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetFirendsElement
			{
				/** 好友自己的昵称 */
				CSTR nickname;
				/** 好友备注说明 */
				CSTR remark;
				/** 用户名称 */
				CSTR username;
				/** 好友别名 */
				CSTR alias;
				/** [long]好友Id */
				int64 firendId;
			}) authTargetFirends;
			/** [long]授权Id */
			int64 authId;
			/** 授权名称 */
			CSTR authName;
			/** define a list with struct of GetUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetGroupsElement */
			DECLARE_LIST(struct GetUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetGroupsElement
			{
				/** 授权分组名称 */
				CSTR name;
				/** [long]分组Id */
				int64 groupId;
			}) authTargetGroups;
			/** define a list with struct of GetUserAuthorizationListResponseData_AuthorizationsElement_AuthDevicesElement */
			DECLARE_LIST(struct GetUserAuthorizationListResponseData_AuthorizationsElement_AuthDevicesElement
			{
				/** 设备序列号 */
				CSTR deviceCode;
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
			}) authDevices;
		}) authorizations;
 
	} data;

} GetUserAuthorizationListResponse;

C_API GetUserAuthorizationListResponse *HSAPI_INIT(GetUserAuthorizationListResponse);

#endif
