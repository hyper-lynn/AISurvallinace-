/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_EncryptPermissonSet_H_
#define _HSVIEW_CLIENT_API_deviceManager_EncryptPermissonSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户授权云解码
【使用平台账号签名】
 */

typedef struct deviceManager_EncryptPermissonSetRequest 
{
	HsviewRequest base;

	struct deviceManager_EncryptPermissonSetRequestData
	{
		
		/** [bool] true-授权  false-取消授权 */
		BOOL encryptFlag;

	} data;

} deviceManager_EncryptPermissonSetRequest;

C_API deviceManager_EncryptPermissonSetRequest *HSAPI_INIT(deviceManager_EncryptPermissonSetRequest);

typedef struct deviceManager_EncryptPermissonSetResponse 
{
	HsviewResponse base;

	struct deviceManager_EncryptPermissonSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_EncryptPermissonSetResponse;

C_API deviceManager_EncryptPermissonSetResponse *HSAPI_INIT(deviceManager_EncryptPermissonSetResponse);

#endif
