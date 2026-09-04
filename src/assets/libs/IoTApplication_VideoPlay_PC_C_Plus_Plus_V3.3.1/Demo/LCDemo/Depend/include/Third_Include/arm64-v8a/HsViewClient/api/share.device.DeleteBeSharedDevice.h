/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_DeleteBeSharedDevice_H_
#define _HSVIEW_CLIENT_API_shareDevice_DeleteBeSharedDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除设备共享，删除TA分享给我的

【需要使用平台账号签名】
 */

typedef struct shareDevice_DeleteBeSharedDeviceRequest 
{
	HsviewRequest base;

	struct shareDevice_DeleteBeSharedDeviceRequestData
	{
		
		/** 设备ID */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} shareDevice_DeleteBeSharedDeviceRequest;

C_API shareDevice_DeleteBeSharedDeviceRequest *HSAPI_INIT(shareDevice_DeleteBeSharedDeviceRequest);

typedef struct shareDevice_DeleteBeSharedDeviceResponse 
{
	HsviewResponse base;

	struct shareDevice_DeleteBeSharedDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareDevice_DeleteBeSharedDeviceResponse;

C_API shareDevice_DeleteBeSharedDeviceResponse *HSAPI_INIT(shareDevice_DeleteBeSharedDeviceResponse);

#endif
