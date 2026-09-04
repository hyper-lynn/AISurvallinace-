/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_DeleteVideoMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_DeleteVideoMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除留言消息。

【使用平台账号签名】
 */

typedef struct cloudMessage_DeleteVideoMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_DeleteVideoMessageRequestData
	{
		
		/** [long]需要删除的留言消息ID */
		DECLARE_LIST(int64) msgIds;

	} data;

} cloudMessage_DeleteVideoMessageRequest;

C_API cloudMessage_DeleteVideoMessageRequest *HSAPI_INIT(cloudMessage_DeleteVideoMessageRequest);

typedef struct cloudMessage_DeleteVideoMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_DeleteVideoMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_DeleteVideoMessageResponse;

C_API cloudMessage_DeleteVideoMessageResponse *HSAPI_INIT(cloudMessage_DeleteVideoMessageResponse);

#endif
