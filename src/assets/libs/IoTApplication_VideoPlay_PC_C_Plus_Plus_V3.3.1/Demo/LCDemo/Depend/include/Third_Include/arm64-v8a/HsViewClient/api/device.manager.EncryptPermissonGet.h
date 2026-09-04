/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_EncryptPermissonGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_EncryptPermissonGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户是否授权云解码
【使用平台账号签名】
 */

typedef struct deviceManager_EncryptPermissonGetRequest 
{
	HsviewRequest base;

	struct deviceManager_EncryptPermissonGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} deviceManager_EncryptPermissonGetRequest;

C_API deviceManager_EncryptPermissonGetRequest *HSAPI_INIT(deviceManager_EncryptPermissonGetRequest);

typedef struct deviceManager_EncryptPermissonGetResponse 
{
	HsviewResponse base;

	struct deviceManager_EncryptPermissonGetResponseData
	{
		
		/** [bool] true-授权  false-未授权 */
		BOOL encryptFlag;
 
	} data;

} deviceManager_EncryptPermissonGetResponse;

C_API deviceManager_EncryptPermissonGetResponse *HSAPI_INIT(deviceManager_EncryptPermissonGetResponse);

#endif
