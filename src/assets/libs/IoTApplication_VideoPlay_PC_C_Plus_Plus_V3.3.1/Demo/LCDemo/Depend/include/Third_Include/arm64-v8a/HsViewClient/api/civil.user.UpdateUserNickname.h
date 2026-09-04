/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdateUserNickname_H_
#define _HSVIEW_CLIENT_API_UpdateUserNickname_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新用户昵称。
【使用平台账号签名】
 */

typedef struct UpdateUserNicknameRequest 
{
	HsviewRequest base;

	struct UpdateUserNicknameRequestData
	{
		
		/** 昵称 */
		CSTR nickname;

	} data;

} UpdateUserNicknameRequest;

C_API UpdateUserNicknameRequest *HSAPI_INIT(UpdateUserNicknameRequest);

typedef struct UpdateUserNicknameResponse 
{
	HsviewResponse base;

	struct UpdateUserNicknameResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpdateUserNicknameResponse;

C_API UpdateUserNicknameResponse *HSAPI_INIT(UpdateUserNicknameResponse);

#endif
