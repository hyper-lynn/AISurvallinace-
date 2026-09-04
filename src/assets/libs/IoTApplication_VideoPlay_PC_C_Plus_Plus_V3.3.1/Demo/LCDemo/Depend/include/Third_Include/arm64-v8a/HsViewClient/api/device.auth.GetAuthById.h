/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_GetAuthById_H_
#define _HSVIEW_CLIENT_API_deviceAuth_GetAuthById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   根据ID查询授权详情
【需要使用平台账号签名】

 */

typedef struct deviceAuth_GetAuthByIdRequest 
{
	HsviewRequest base;

	struct deviceAuth_GetAuthByIdRequestData
	{
		
		/** [long]授权ID */
		int64 id;

	} data;

} deviceAuth_GetAuthByIdRequest;

C_API deviceAuth_GetAuthByIdRequest *HSAPI_INIT(deviceAuth_GetAuthByIdRequest);

typedef struct deviceAuth_GetAuthByIdResponse 
{
	HsviewResponse base;

	struct deviceAuth_GetAuthByIdResponseData
	{
		
		/** struct of deviceAuth_GetAuthByIdResponseData_Role */
		struct deviceAuth_GetAuthByIdResponseData_Role {
			/** [long]角色Id */
			int64 roleId;
			/** 角色名称 */
			CSTR roleName;
			/** 权限列表 */
			CSTR authFunctions;
		} role;
		/** define a list with struct of deviceAuth_GetAuthByIdResponseData_AuthTargetElement */
		DECLARE_LIST(struct deviceAuth_GetAuthByIdResponseData_AuthTargetElement
		{
			/** [O]授权分组名称 */
			CSTR groupName;
			/** [int]成员类型，1为分组，0为好友，好友和分组分批展示 */
			int memberType;
			/** [long][O]好友Id */
			int64 friendId;
			/** [long][O]分组Id */
			int64 groupId;
		}) authTarget;
		/** [long]授权Id */
		int64 id;
		/** define a list with struct of deviceAuth_GetAuthByIdResponseData_AuthChannelsElement */
		DECLARE_LIST(struct deviceAuth_GetAuthByIdResponseData_AuthChannelsElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authChannels;
		/** 授权名称 */
		CSTR authName;
 
	} data;

} deviceAuth_GetAuthByIdResponse;

C_API deviceAuth_GetAuthByIdResponse *HSAPI_INIT(deviceAuth_GetAuthByIdResponse);

#endif
