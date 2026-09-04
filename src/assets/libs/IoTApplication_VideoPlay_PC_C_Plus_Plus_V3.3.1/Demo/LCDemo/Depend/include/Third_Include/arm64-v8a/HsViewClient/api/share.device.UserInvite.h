/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_UserInvite_H_
#define _HSVIEW_CLIENT_API_shareDevice_UserInvite_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 共享设备用户邀请

【使用平台账号签名】
 */

typedef struct shareDevice_UserInviteRequest 
{
	HsviewRequest base;

	struct shareDevice_UserInviteRequestData
	{
		
		/** define a list with struct of shareDevice_UserInviteRequestData_InviteInfosElement */
		DECLARE_LIST(struct shareDevice_UserInviteRequestData_InviteInfosElement
		{
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被邀请用户账号，海外使用邮箱 */
			CSTR account;
		}) inviteInfos;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_UserInviteRequest;

C_API shareDevice_UserInviteRequest *HSAPI_INIT(shareDevice_UserInviteRequest);

typedef struct shareDevice_UserInviteResponse 
{
	HsviewResponse base;

	struct shareDevice_UserInviteResponseData
	{
		
		/** define a list with struct of shareDevice_UserInviteResponseData_ItemsElement */
		DECLARE_LIST(struct shareDevice_UserInviteResponseData_ItemsElement
		{
			/** 被邀请用户账号哈希值 */
			CSTR accountHash;
		}) items;
 
	} data;

} shareDevice_UserInviteResponse;

C_API shareDevice_UserInviteResponse *HSAPI_INIT(shareDevice_UserInviteResponse);

#endif
