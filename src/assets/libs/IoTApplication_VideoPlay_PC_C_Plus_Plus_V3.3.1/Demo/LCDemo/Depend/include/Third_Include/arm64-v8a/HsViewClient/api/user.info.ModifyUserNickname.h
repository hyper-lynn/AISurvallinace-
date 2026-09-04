/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userInfo_ModifyUserNickname_H_
#define _HSVIEW_CLIENT_API_userInfo_ModifyUserNickname_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新用户昵称。
【使用平台账号签名】
 */

typedef struct userInfo_ModifyUserNicknameRequest 
{
	HsviewRequest base;

	struct userInfo_ModifyUserNicknameRequestData
	{
		
		/** 昵称 */
		CSTR nickname;

	} data;

} userInfo_ModifyUserNicknameRequest;

C_API userInfo_ModifyUserNicknameRequest *HSAPI_INIT(userInfo_ModifyUserNicknameRequest);

typedef struct userInfo_ModifyUserNicknameResponse 
{
	HsviewResponse base;

	struct userInfo_ModifyUserNicknameResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userInfo_ModifyUserNicknameResponse;

C_API userInfo_ModifyUserNicknameResponse *HSAPI_INIT(userInfo_ModifyUserNicknameResponse);

#endif
