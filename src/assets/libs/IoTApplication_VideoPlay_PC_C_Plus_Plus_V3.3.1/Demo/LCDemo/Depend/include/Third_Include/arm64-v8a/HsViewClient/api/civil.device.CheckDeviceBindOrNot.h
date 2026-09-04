/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CheckDeviceBindOrNot_H_
#define _HSVIEW_CLIENT_API_CheckDeviceBindOrNot_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

检查设备是否已绑定。
若已绑定，检查设备是否属于签名账号。
	
【需要使用平台账号签名】

 */

typedef struct CheckDeviceBindOrNotRequest 
{
	HsviewRequest base;

	struct CheckDeviceBindOrNotRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} CheckDeviceBindOrNotRequest;

C_API CheckDeviceBindOrNotRequest *HSAPI_INIT(CheckDeviceBindOrNotRequest);

typedef struct CheckDeviceBindOrNotResponse 
{
	HsviewResponse base;

	struct CheckDeviceBindOrNotResponseData
	{
		
		/** [bool]是否被绑定到某个账号 */
		BOOL isBind;
		/** [bool]是否属于自己这个账号 */
		BOOL isMine;
 
	} data;

} CheckDeviceBindOrNotResponse;

C_API CheckDeviceBindOrNotResponse *HSAPI_INIT(CheckDeviceBindOrNotResponse);

#endif
