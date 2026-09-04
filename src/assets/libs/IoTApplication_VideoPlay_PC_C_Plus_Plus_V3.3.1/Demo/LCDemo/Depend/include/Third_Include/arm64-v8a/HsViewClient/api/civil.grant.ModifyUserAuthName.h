/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyUserAuthName_H_
#define _HSVIEW_CLIENT_API_ModifyUserAuthName_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   修改授权名称
【需要使用平台账号签名】

 */

typedef struct ModifyUserAuthNameRequest 
{
	HsviewRequest base;

	struct ModifyUserAuthNameRequestData
	{
		
		/** [long]授权ID */
		int64 authId;
		/** 授权名称 */
		CSTR authName;

	} data;

} ModifyUserAuthNameRequest;

C_API ModifyUserAuthNameRequest *HSAPI_INIT(ModifyUserAuthNameRequest);

typedef struct ModifyUserAuthNameResponse 
{
	HsviewResponse base;

	struct ModifyUserAuthNameResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyUserAuthNameResponse;

C_API ModifyUserAuthNameResponse *HSAPI_INIT(ModifyUserAuthNameResponse);

#endif
