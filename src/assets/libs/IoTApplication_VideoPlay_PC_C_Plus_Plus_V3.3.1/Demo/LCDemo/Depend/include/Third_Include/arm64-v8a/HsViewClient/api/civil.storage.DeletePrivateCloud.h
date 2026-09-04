/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeletePrivateCloud_H_
#define _HSVIEW_CLIENT_API_DeletePrivateCloud_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除一条私有云映射关系。
【使用平台账号签名】
 */

typedef struct DeletePrivateCloudRequest 
{
	HsviewRequest base;

	struct DeletePrivateCloudRequestData
	{
		
		/** IPC设备ID，必填 */
		CSTR ipcDeviceId;
		/** 智能网关（私有云）设备ID，必填 */
		CSTR ihgDeviceId;

	} data;

} DeletePrivateCloudRequest;

C_API DeletePrivateCloudRequest *HSAPI_INIT(DeletePrivateCloudRequest);

typedef struct DeletePrivateCloudResponse 
{
	HsviewResponse base;

	struct DeletePrivateCloudResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeletePrivateCloudResponse;

C_API DeletePrivateCloudResponse *HSAPI_INIT(DeletePrivateCloudResponse);

#endif
