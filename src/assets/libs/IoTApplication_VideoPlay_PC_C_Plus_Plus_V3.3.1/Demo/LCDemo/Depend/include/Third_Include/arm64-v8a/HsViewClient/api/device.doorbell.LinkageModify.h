/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkageModify_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkageModify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改关联的铃铛

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkageModifyRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkageModifyRequestData
	{
		
		/** 要关联的铃铛 */
		CSTR newBellId;
		/** 原来关联的铃铛 */
		CSTR oldBellId;
		/** 门铃的ID */
		CSTR doorId;

	} data;

} deviceDoorbell_LinkageModifyRequest;

C_API deviceDoorbell_LinkageModifyRequest *HSAPI_INIT(deviceDoorbell_LinkageModifyRequest);

typedef struct deviceDoorbell_LinkageModifyResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkageModifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceDoorbell_LinkageModifyResponse;

C_API deviceDoorbell_LinkageModifyResponse *HSAPI_INIT(deviceDoorbell_LinkageModifyResponse);

#endif
