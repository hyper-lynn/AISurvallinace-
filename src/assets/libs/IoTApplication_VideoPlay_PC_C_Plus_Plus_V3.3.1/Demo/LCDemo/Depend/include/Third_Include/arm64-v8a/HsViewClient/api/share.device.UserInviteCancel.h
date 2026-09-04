/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_UserInviteCancel_H_
#define _HSVIEW_CLIENT_API_shareDevice_UserInviteCancel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 共享设备用户取消邀请

【使用平台账号签名】
 */

typedef struct shareDevice_UserInviteCancelRequest 
{
	HsviewRequest base;

	struct shareDevice_UserInviteCancelRequestData
	{
		
		/** define a list with struct of shareDevice_UserInviteCancelRequestData_InviteInfosElement */
		DECLARE_LIST(struct shareDevice_UserInviteCancelRequestData_InviteInfosElement
		{
			/** 被邀请用户账号哈希值 */
			CSTR accountHash;
		}) inviteInfos;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_UserInviteCancelRequest;

C_API shareDevice_UserInviteCancelRequest *HSAPI_INIT(shareDevice_UserInviteCancelRequest);

typedef struct shareDevice_UserInviteCancelResponse 
{
	HsviewResponse base;

	struct shareDevice_UserInviteCancelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareDevice_UserInviteCancelResponse;

C_API shareDevice_UserInviteCancelResponse *HSAPI_INIT(shareDevice_UserInviteCancelResponse);

#endif
