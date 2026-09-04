/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetEncryptPermisson_H_
#define _HSVIEW_CLIENT_API_GetEncryptPermisson_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户是否授权云解码
【使用平台账号签名】
 */

typedef struct GetEncryptPermissonRequest 
{
	HsviewRequest base;

	struct GetEncryptPermissonRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetEncryptPermissonRequest;

C_API GetEncryptPermissonRequest *HSAPI_INIT(GetEncryptPermissonRequest);

typedef struct GetEncryptPermissonResponse 
{
	HsviewResponse base;

	struct GetEncryptPermissonResponseData
	{
		
		/** [bool] true-授权  false-未授权 */
		BOOL encryptFlag;
 
	} data;

} GetEncryptPermissonResponse;

C_API GetEncryptPermissonResponse *HSAPI_INIT(GetEncryptPermissonResponse);

#endif
