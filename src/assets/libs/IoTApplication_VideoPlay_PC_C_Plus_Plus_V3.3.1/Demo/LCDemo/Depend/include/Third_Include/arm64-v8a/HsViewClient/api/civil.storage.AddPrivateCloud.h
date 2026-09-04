/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddPrivateCloud_H_
#define _HSVIEW_CLIENT_API_AddPrivateCloud_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
加入一个IPC到私有云中。
【使用平台账号签名】
 */

typedef struct AddPrivateCloudRequest 
{
	HsviewRequest base;

	struct AddPrivateCloudRequestData
	{
		
		/** IPC设备ID */
		CSTR ipcDeviceId;
		/** 智能网关（私有云）设备ID */
		CSTR ihgDeviceId;

	} data;

} AddPrivateCloudRequest;

C_API AddPrivateCloudRequest *HSAPI_INIT(AddPrivateCloudRequest);

typedef struct AddPrivateCloudResponse 
{
	HsviewResponse base;

	struct AddPrivateCloudResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddPrivateCloudResponse;

C_API AddPrivateCloudResponse *HSAPI_INIT(AddPrivateCloudResponse);

#endif
