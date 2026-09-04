/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkageAdd_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkageAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
门铃关联铃铛

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkageAddRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkageAddRequestData
	{
		
		/** 门铃的ID */
		CSTR doorId;
		/** 铃铛的ID */
		DECLARE_LIST(CSTR) bellIds;

	} data;

} deviceDoorbell_LinkageAddRequest;

C_API deviceDoorbell_LinkageAddRequest *HSAPI_INIT(deviceDoorbell_LinkageAddRequest);

typedef struct deviceDoorbell_LinkageAddResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkageAddResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceDoorbell_LinkageAddResponse;

C_API deviceDoorbell_LinkageAddResponse *HSAPI_INIT(deviceDoorbell_LinkageAddResponse);

#endif
