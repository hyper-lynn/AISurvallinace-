/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_SetUserExperienceSwitch_H_
#define _HSVIEW_CLIENT_API_userPush_SetUserExperienceSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置用户体验开关。

【使用平台账号签名】
 */

typedef struct userPush_SetUserExperienceSwitchRequest 
{
	HsviewRequest base;

	struct userPush_SetUserExperienceSwitchRequestData
	{
		
		/** on打开,off关闭 */
		CSTR enable;

	} data;

} userPush_SetUserExperienceSwitchRequest;

C_API userPush_SetUserExperienceSwitchRequest *HSAPI_INIT(userPush_SetUserExperienceSwitchRequest);

typedef struct userPush_SetUserExperienceSwitchResponse 
{
	HsviewResponse base;

	struct userPush_SetUserExperienceSwitchResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userPush_SetUserExperienceSwitchResponse;

C_API userPush_SetUserExperienceSwitchResponse *HSAPI_INIT(userPush_SetUserExperienceSwitchResponse);

#endif
