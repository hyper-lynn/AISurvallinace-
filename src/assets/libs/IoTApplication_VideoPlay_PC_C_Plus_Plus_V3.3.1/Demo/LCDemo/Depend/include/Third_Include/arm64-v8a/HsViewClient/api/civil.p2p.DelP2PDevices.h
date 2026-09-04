/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelP2PDevices_H_
#define _HSVIEW_CLIENT_API_DelP2PDevices_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除p2p设备
【使用平台账号签名认证】
 */

typedef struct DelP2PDevicesRequest 
{
	HsviewRequest base;

	struct DelP2PDevicesRequestData
	{
		
		/** 设备编号 */
		DECLARE_LIST(CSTR) devices;

	} data;

} DelP2PDevicesRequest;

C_API DelP2PDevicesRequest *HSAPI_INIT(DelP2PDevicesRequest);

typedef struct DelP2PDevicesResponse 
{
	HsviewResponse base;

	struct DelP2PDevicesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelP2PDevicesResponse;

C_API DelP2PDevicesResponse *HSAPI_INIT(DelP2PDevicesResponse);

#endif
