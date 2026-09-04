/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetUserAuthTarget_H_
#define _HSVIEW_CLIENT_API_SetUserAuthTarget_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   设置授权对象
【需要使用平台账号签名】

 */

typedef struct SetUserAuthTargetRequest 
{
	HsviewRequest base;

	struct SetUserAuthTargetRequestData
	{
		
		/** [long]好友Id */
		DECLARE_LIST(int64) friends;
		/** [long]好友分组Id */
		DECLARE_LIST(int64) groups;
		/** [long]授权Id */
		int64 authId;

	} data;

} SetUserAuthTargetRequest;

C_API SetUserAuthTargetRequest *HSAPI_INIT(SetUserAuthTargetRequest);

typedef struct SetUserAuthTargetResponse 
{
	HsviewResponse base;

	struct SetUserAuthTargetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetUserAuthTargetResponse;

C_API SetUserAuthTargetResponse *HSAPI_INIT(SetUserAuthTargetResponse);

#endif
