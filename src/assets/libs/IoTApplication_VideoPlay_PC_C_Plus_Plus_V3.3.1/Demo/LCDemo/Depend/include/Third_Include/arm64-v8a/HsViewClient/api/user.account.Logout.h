/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_Logout_H_
#define _HSVIEW_CLIENT_API_userAccount_Logout_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户注销、登录。
用户注销时该手机客户端推送配置下线状态

【使用平台账号签名】
 */

typedef struct userAccount_LogoutRequest 
{
	HsviewRequest base;

	struct userAccount_LogoutRequestData
	{
		
		/** 标识手机的唯一ID，用于推送 */
		CSTR clientPushId;

	} data;

} userAccount_LogoutRequest;

C_API userAccount_LogoutRequest *HSAPI_INIT(userAccount_LogoutRequest);

typedef struct userAccount_LogoutResponse 
{
	HsviewResponse base;

	struct userAccount_LogoutResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_LogoutResponse;

C_API userAccount_LogoutResponse *HSAPI_INIT(userAccount_LogoutResponse);

#endif
