/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_BindP2PDevice_H_
#define _HSVIEW_CLIENT_API_BindP2PDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定p2p设备
【使用平台账号签名认证】
 */

typedef struct BindP2PDeviceRequest 
{
	HsviewRequest base;

	struct BindP2PDeviceRequestData
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

} BindP2PDeviceRequest;

C_API BindP2PDeviceRequest *HSAPI_INIT(BindP2PDeviceRequest);

typedef struct BindP2PDeviceResponse 
{
	HsviewResponse base;

	struct BindP2PDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindP2PDeviceResponse;

C_API BindP2PDeviceResponse *HSAPI_INIT(BindP2PDeviceResponse);

#endif
