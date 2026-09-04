/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAuthUserList_H_
#define _HSVIEW_CLIENT_API_GetAuthUserList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的授权信息。
针对同一个设备同一个通道授权给同一个人，列表中只有一个，functions权限列表会被合并。

【使用平台账号签名】
 */

typedef struct GetAuthUserListRequest 
{
	HsviewRequest base;

	struct GetAuthUserListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAuthUserListRequest;

C_API GetAuthUserListRequest *HSAPI_INIT(GetAuthUserListRequest);

typedef struct GetAuthUserListResponse 
{
	HsviewResponse base;

	struct GetAuthUserListResponseData
	{
		
		/** define a list with struct of GetAuthUserListResponseData_ShareInfosElement */
		DECLARE_LIST(struct GetAuthUserListResponseData_ShareInfosElement
		{
			/** 被授权者的用户名 */
			CSTR username;
			/** 授权的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被授权的手机号码 */
			CSTR phoneNumber;
			/** 被授权者的头像URL */
			CSTR userIcon;
			/** 被授权者的昵称 */
			CSTR nickname;
		}) shareInfos;
		/** [int]剩余分享和授权的数量 */
		int leftShareCount;
		/** [int]允许分享数量, 999表示不限制,999表示为vip */
		int allowShareCount;
 
	} data;

} GetAuthUserListResponse;

C_API GetAuthUserListResponse *HSAPI_INIT(GetAuthUserListResponse);

#endif
