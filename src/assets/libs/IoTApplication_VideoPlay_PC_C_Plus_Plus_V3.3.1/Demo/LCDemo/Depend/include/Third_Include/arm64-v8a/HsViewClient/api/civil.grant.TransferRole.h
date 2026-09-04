/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferRole_H_
#define _HSVIEW_CLIENT_API_TransferRole_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   授权角色转移
【需要使用平台账号签名】

 */

typedef struct TransferRoleRequest 
{
	HsviewRequest base;

	struct TransferRoleRequestData
	{
		
		/** [long]授权Id */
		int64 authId;
		/** [long]角色Id */
		int64 roleId;

	} data;

} TransferRoleRequest;

C_API TransferRoleRequest *HSAPI_INIT(TransferRoleRequest);

typedef struct TransferRoleResponse 
{
	HsviewResponse base;

	struct TransferRoleResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferRoleResponse;

C_API TransferRoleResponse *HSAPI_INIT(TransferRoleResponse);

#endif
