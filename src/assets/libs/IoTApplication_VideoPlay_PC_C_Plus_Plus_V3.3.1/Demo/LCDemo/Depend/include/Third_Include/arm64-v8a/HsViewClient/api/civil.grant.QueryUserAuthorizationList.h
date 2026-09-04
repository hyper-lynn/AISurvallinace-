/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryUserAuthorizationList_H_
#define _HSVIEW_CLIENT_API_QueryUserAuthorizationList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   分页获取授权列表，开放平台适用（无分组）
【需要使用平台账号签名】

 */

typedef struct QueryUserAuthorizationListRequest 
{
	HsviewRequest base;

	struct QueryUserAuthorizationListRequestData
	{
		
		/** [long]从该授权ID开始查询。若要从最新开始查，填-1 */
		int64 authId;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} QueryUserAuthorizationListRequest;

C_API QueryUserAuthorizationListRequest *HSAPI_INIT(QueryUserAuthorizationListRequest);

typedef struct QueryUserAuthorizationListResponse 
{
	HsviewResponse base;

	struct QueryUserAuthorizationListResponseData
	{
		
		/** define a list with struct of QueryUserAuthorizationListResponseData_AuthorizationsElement */
		DECLARE_LIST(struct QueryUserAuthorizationListResponseData_AuthorizationsElement
		{
			/** struct of QueryUserAuthorizationListResponseData_AuthorizationsElement_Role */
			struct QueryUserAuthorizationListResponseData_AuthorizationsElement_Role {
				/** [long]角色Id */
				int64 roleId;
				/** 角色名称 */
				CSTR roleName;
				/** 权限列表 */
				CSTR authFunctions;
			} role;
			/** define a list with struct of QueryUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetsElement */
			DECLARE_LIST(struct QueryUserAuthorizationListResponseData_AuthorizationsElement_AuthTargetsElement
			{
				/** 用户名称 */
				CSTR username;
				/** 手机号 */
				CSTR userPhone;
				/** 用户ID */
				CSTR userId;
			}) authTargets;
			/** [long]授权Id */
			int64 authId;
			/** 授权名称 */
			CSTR authName;
			/** define a list with struct of QueryUserAuthorizationListResponseData_AuthorizationsElement_AuthDevicesElement */
			DECLARE_LIST(struct QueryUserAuthorizationListResponseData_AuthorizationsElement_AuthDevicesElement
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

} QueryUserAuthorizationListResponse;

C_API QueryUserAuthorizationListResponse *HSAPI_INIT(QueryUserAuthorizationListResponse);

#endif
