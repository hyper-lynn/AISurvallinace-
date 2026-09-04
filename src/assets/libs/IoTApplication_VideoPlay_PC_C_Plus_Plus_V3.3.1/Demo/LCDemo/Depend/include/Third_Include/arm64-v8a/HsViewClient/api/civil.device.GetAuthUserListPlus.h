/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAuthUserListPlus_H_
#define _HSVIEW_CLIENT_API_GetAuthUserListPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的授权信息。
针对同一个设备同一个通道授权给同一个人，列表中只有一个，functions权限列表会被合并。

【使用平台账号签名】
 */

typedef struct GetAuthUserListPlusRequest 
{
	HsviewRequest base;

	struct GetAuthUserListPlusRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAuthUserListPlusRequest;

C_API GetAuthUserListPlusRequest *HSAPI_INIT(GetAuthUserListPlusRequest);

typedef struct GetAuthUserListPlusResponse 
{
	HsviewResponse base;

	struct GetAuthUserListPlusResponseData
	{
		
		/** define a list with struct of GetAuthUserListPlusResponseData_ShareInfosElement */
		DECLARE_LIST(struct GetAuthUserListPlusResponseData_ShareInfosElement
		{
			/** 被授权者的昵称 */
			CSTR nickname;
			/** 授权的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被授权的手机号码 */
			CSTR phoneNumber;
			/** 被授权者的头像URL */
			CSTR userIcon;
			/** 被授权者的用户id */
			CSTR userId;
			/** 被授权者的用户名 */
			CSTR username;
		}) shareInfos;
		/** [int]剩余分享和授权的数量 */
		int leftShareCount;
		/** [int]允许分享数量, 999表示不限制,999表示为vip */
		int allowShareCount;
 
	} data;

} GetAuthUserListPlusResponse;

C_API GetAuthUserListPlusResponse *HSAPI_INIT(GetAuthUserListPlusResponse);

#endif
