/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkageDelete_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkageDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
解除门铃和铃铛的关联关系

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkageDeleteRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkageDeleteRequestData
	{
		
		/** 门铃的ID */
		CSTR doorId;
		/** 铃铛的ID */
		DECLARE_LIST(CSTR) bellIds;

	} data;

} deviceDoorbell_LinkageDeleteRequest;

C_API deviceDoorbell_LinkageDeleteRequest *HSAPI_INIT(deviceDoorbell_LinkageDeleteRequest);

typedef struct deviceDoorbell_LinkageDeleteResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkageDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceDoorbell_LinkageDeleteResponse;

C_API deviceDoorbell_LinkageDeleteResponse *HSAPI_INIT(deviceDoorbell_LinkageDeleteResponse);

#endif
