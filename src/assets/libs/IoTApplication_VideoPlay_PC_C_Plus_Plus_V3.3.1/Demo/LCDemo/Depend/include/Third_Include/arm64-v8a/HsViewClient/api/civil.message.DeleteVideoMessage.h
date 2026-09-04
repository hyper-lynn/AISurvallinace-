/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteVideoMessage_H_
#define _HSVIEW_CLIENT_API_DeleteVideoMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除留言消息。

msgIds为空，表示删除用户下所有的留言消息

【使用平台账号签名】
 */

typedef struct DeleteVideoMessageRequest 
{
	HsviewRequest base;

	struct DeleteVideoMessageRequestData
	{
		
		/** [long]需要删除的留言消息ID */
		DECLARE_LIST(int64) msgIds;

	} data;

} DeleteVideoMessageRequest;

C_API DeleteVideoMessageRequest *HSAPI_INIT(DeleteVideoMessageRequest);

typedef struct DeleteVideoMessageResponse 
{
	HsviewResponse base;

	struct DeleteVideoMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteVideoMessageResponse;

C_API DeleteVideoMessageResponse *HSAPI_INIT(DeleteVideoMessageResponse);

#endif
