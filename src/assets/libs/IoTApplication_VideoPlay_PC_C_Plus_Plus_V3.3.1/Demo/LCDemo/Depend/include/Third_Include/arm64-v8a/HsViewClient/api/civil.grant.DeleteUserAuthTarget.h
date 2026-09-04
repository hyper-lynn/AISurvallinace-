/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteUserAuthTarget_H_
#define _HSVIEW_CLIENT_API_DeleteUserAuthTarget_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   删除授权对象
【需要使用平台账号签名】

 */

typedef struct DeleteUserAuthTargetRequest 
{
	HsviewRequest base;

	struct DeleteUserAuthTargetRequestData
	{
		
		/** [long]好友Id */
		DECLARE_LIST(int64) friends;
		/** [long]好友分组Id */
		DECLARE_LIST(int64) groups;
		/** [long]授权Id */
		int64 authId;

	} data;

} DeleteUserAuthTargetRequest;

C_API DeleteUserAuthTargetRequest *HSAPI_INIT(DeleteUserAuthTargetRequest);

typedef struct DeleteUserAuthTargetResponse 
{
	HsviewResponse base;

	struct DeleteUserAuthTargetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserAuthTargetResponse;

C_API DeleteUserAuthTargetResponse *HSAPI_INIT(DeleteUserAuthTargetResponse);

#endif
