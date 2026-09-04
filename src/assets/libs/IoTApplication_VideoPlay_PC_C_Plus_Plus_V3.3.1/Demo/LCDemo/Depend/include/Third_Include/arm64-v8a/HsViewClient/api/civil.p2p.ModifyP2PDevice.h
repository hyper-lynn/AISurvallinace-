/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyP2PDevice_H_
#define _HSVIEW_CLIENT_API_ModifyP2PDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改p2p设备信息
【使用平台账号签名认证】
 */

typedef struct ModifyP2PDeviceRequest 
{
	HsviewRequest base;

	struct ModifyP2PDeviceRequestData
	{
		
		/** 设备用户名 */
		CSTR username;
		/** 设备名称 */
		CSTR deviceName;
		/** 设备编号 */
		CSTR deviceCode;
		/** 回放码流类型:main-主码流，sub-辅码流 */
		CSTR preferStreamPlayback;
		/** 实时码流类型:main-主码流，sub-辅码流 */
		CSTR preferStreamReal;
		/** 设备密码 */
		CSTR password;

	} data;

} ModifyP2PDeviceRequest;

C_API ModifyP2PDeviceRequest *HSAPI_INIT(ModifyP2PDeviceRequest);

typedef struct ModifyP2PDeviceResponse 
{
	HsviewResponse base;

	struct ModifyP2PDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyP2PDeviceResponse;

C_API ModifyP2PDeviceResponse *HSAPI_INIT(ModifyP2PDeviceResponse);

#endif
