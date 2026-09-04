/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserDps_H_
#define _HSVIEW_CLIENT_API_GetUserDps_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取该账号下的设备密码种子，客户端每次使用前都进行调用更新。
【使用平台账号签名】
 */

typedef struct GetUserDpsRequest 
{
	HsviewRequest base;

	struct GetUserDpsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUserDpsRequest;

C_API GetUserDpsRequest *HSAPI_INIT(GetUserDpsRequest);

typedef struct GetUserDpsResponse 
{
	HsviewResponse base;

	struct GetUserDpsResponseData
	{
		
		/** 设备密码种子 */
		CSTR dps;
 
	} data;

} GetUserDpsResponse;

C_API GetUserDpsResponse *HSAPI_INIT(GetUserDpsResponse);

#endif
