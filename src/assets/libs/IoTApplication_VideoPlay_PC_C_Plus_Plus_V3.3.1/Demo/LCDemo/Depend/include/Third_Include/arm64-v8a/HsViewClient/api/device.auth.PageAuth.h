/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_PageAuth_H_
#define _HSVIEW_CLIENT_API_deviceAuth_PageAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取授权列表
【需要使用平台账号签名】

 */

typedef struct deviceAuth_PageAuthRequest 
{
	HsviewRequest base;

	struct deviceAuth_PageAuthRequestData
	{
		
		/** 每页条数 */
		CSTR pageSize;
		/** 页码 */
		CSTR pageNo;

	} data;

} deviceAuth_PageAuthRequest;

C_API deviceAuth_PageAuthRequest *HSAPI_INIT(deviceAuth_PageAuthRequest);

typedef struct deviceAuth_PageAuthResponse 
{
	HsviewResponse base;

	struct deviceAuth_PageAuthResponseData
	{
		
		/** define a list with struct of deviceAuth_PageAuthResponseData_ListElement */
		DECLARE_LIST(struct deviceAuth_PageAuthResponseData_ListElement
		{
			/** struct of deviceAuth_PageAuthResponseData_ListElement_Role */
			struct deviceAuth_PageAuthResponseData_ListElement_Role {
				/** [long]角色Id */
				int64 roleId;
				/** 角色名称 */
				CSTR roleName;
				/** 权限列表 */
				CSTR authFunctions;
			} role;
			/** define a list with struct of deviceAuth_PageAuthResponseData_ListElement_AuthTargetsElement */
			DECLARE_LIST(struct deviceAuth_PageAuthResponseData_ListElement_AuthTargetsElement
			{
				/** [O]授权分组名称 */
				CSTR groupName;
				/** [int]成员类型，1为分组，0为好友，好友和分组分批展示 */
				int memberType;
				/** [long][O]好友Id */
				int64 friendId;
				/** [long][O]分组Id */
				int64 groupId;
			}) authTargets;
			/** [long]授权Id */
			int64 id;
			/** define a list with struct of deviceAuth_PageAuthResponseData_ListElement_AuthChannelsElement */
			DECLARE_LIST(struct deviceAuth_PageAuthResponseData_ListElement_AuthChannelsElement
			{
				/** 设备序列号 */
				CSTR deviceCode;
				/** 通道号 */
				CSTR channelId;
			}) authChannels;
			/** 授权名称 */
			CSTR authName;
		}) list;
		/** 总数目 */
		CSTR totalCount;
		/** 每页条数 */
		CSTR pageSize;
		/** 页码 */
		CSTR pageNo;
 
	} data;

} deviceAuth_PageAuthResponse;

C_API deviceAuth_PageAuthResponse *HSAPI_INIT(deviceAuth_PageAuthResponse);

#endif
