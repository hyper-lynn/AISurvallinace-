/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChatServer_H_
#define _HSVIEW_CLIENT_API_GetChatServer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊服务器的地址。
【无需签名认证】
 */

typedef struct GetChatServerRequest 
{
	HsviewRequest base;

	struct GetChatServerRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetChatServerRequest;

C_API GetChatServerRequest *HSAPI_INIT(GetChatServerRequest);

typedef struct GetChatServerResponse 
{
	HsviewResponse base;

	struct GetChatServerResponseData
	{
		
		/** 橙聊服务器的IP地址，如202.123.56.78 */
		CSTR serverIp;
		/** [int]橙聊服务器的端口 */
		int serverPort;
 
	} data;

} GetChatServerResponse;

C_API GetChatServerResponse *HSAPI_INIT(GetChatServerResponse);

#endif
