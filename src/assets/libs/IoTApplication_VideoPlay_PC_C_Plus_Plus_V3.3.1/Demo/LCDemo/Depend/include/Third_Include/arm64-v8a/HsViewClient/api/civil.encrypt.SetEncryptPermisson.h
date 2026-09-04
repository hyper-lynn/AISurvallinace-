/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetEncryptPermisson_H_
#define _HSVIEW_CLIENT_API_SetEncryptPermisson_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户授权云解码
【使用平台账号签名】
 */

typedef struct SetEncryptPermissonRequest 
{
	HsviewRequest base;

	struct SetEncryptPermissonRequestData
	{
		
		/** [bool] true-授权  false-取消授权 */
		BOOL encryptFlag;

	} data;

} SetEncryptPermissonRequest;

C_API SetEncryptPermissonRequest *HSAPI_INIT(SetEncryptPermissonRequest);

typedef struct SetEncryptPermissonResponse 
{
	HsviewResponse base;

	struct SetEncryptPermissonResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetEncryptPermissonResponse;

C_API SetEncryptPermissonResponse *HSAPI_INIT(SetEncryptPermissonResponse);

#endif
