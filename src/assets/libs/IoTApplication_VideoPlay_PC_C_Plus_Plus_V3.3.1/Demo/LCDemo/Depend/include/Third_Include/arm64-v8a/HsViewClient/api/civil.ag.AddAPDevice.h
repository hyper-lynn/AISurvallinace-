/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddAPDevice_H_
#define _HSVIEW_CLIENT_API_AddAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加配件。
【需要使用平台账号签名】
 */

typedef struct AddAPDeviceRequest 
{
	HsviewRequest base;

	struct AddAPDeviceRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 配件的型号 */
		CSTR type;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} AddAPDeviceRequest;

C_API AddAPDeviceRequest *HSAPI_INIT(AddAPDeviceRequest);

typedef struct AddAPDeviceResponse 
{
	HsviewResponse base;

	struct AddAPDeviceResponseData
	{
		
		/** [int]配件的使能:1-使能开启 ，0-使能关闭 */
		int apEnable;
		/** 报警网关配件id */
		CSTR apId;
		/** [int]配件的在线状态：1-在线  0-离线 */
		int apStatus;
		/** 配件的类型 */
		CSTR apType;
		/** 配件的型号 */
		CSTR apModel;
		/** 配件的版本号 */
		CSTR apVersion;
		/** 配件名称 */
		CSTR apName;
		/** 网关的设备ID */
		CSTR deviceId;
 
	} data;

} AddAPDeviceResponse;

C_API AddAPDeviceResponse *HSAPI_INIT(AddAPDeviceResponse);

#endif
