/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserAuthorizationById_H_
#define _HSVIEW_CLIENT_API_GetUserAuthorizationById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   根据ID查询授权详情
【需要使用平台账号签名】

 */

typedef struct GetUserAuthorizationByIdRequest 
{
	HsviewRequest base;

	struct GetUserAuthorizationByIdRequestData
	{
		
		/** [long]授权ID */
		int64 authId;

	} data;

} GetUserAuthorizationByIdRequest;

C_API GetUserAuthorizationByIdRequest *HSAPI_INIT(GetUserAuthorizationByIdRequest);

typedef struct GetUserAuthorizationByIdResponse 
{
	HsviewResponse base;

	struct GetUserAuthorizationByIdResponseData
	{
		
		/** struct of GetUserAuthorizationByIdResponseData_Authorization */
		struct GetUserAuthorizationByIdResponseData_Authorization {
			/** struct of GetUserAuthorizationByIdResponseData_Authorization_Role */
			struct GetUserAuthorizationByIdResponseData_Authorization_Role {
				/** [long]角色Id */
				int64 roleId;
				/** 角色名称 */
				CSTR roleName;
				/** 权限列表 */
				CSTR authFunctions;
			} role;
			/** define a list with struct of GetUserAuthorizationByIdResponseData_Authorization_AuthTargetFirendsElement */
			DECLARE_LIST(struct GetUserAuthorizationByIdResponseData_Authorization_AuthTargetFirendsElement
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
			/** [long]授权Id */
			int64 authId;
			/** 授权名称 */
			CSTR authName;
			/** define a list with struct of GetUserAuthorizationByIdResponseData_Authorization_AuthTargetGroupsElement */
			DECLARE_LIST(struct GetUserAuthorizationByIdResponseData_Authorization_AuthTargetGroupsElement
			{
				/** 分组中第一个好友头像 */
				CSTR userIcon;
				/** 授权分组名称 */
				CSTR name;
				/** [long]分组Id */
				int64 groupId;
			}) authTargetGroups;
			/** define a list with struct of GetUserAuthorizationByIdResponseData_Authorization_AuthDevicesElement */
			DECLARE_LIST(struct GetUserAuthorizationByIdResponseData_Authorization_AuthDevicesElement
			{
				/** 设备序列号 */
				CSTR deviceCode;
				/** 通道号 */
				CSTR channelId;
				/** [int]剩余共享数量 */
				int leftShareCount;
				/** 通道名称 */
				CSTR channelName;
			}) authDevices;
		} authorization;
 
	} data;

} GetUserAuthorizationByIdResponse;

C_API GetUserAuthorizationByIdResponse *HSAPI_INIT(GetUserAuthorizationByIdResponse);

#endif
