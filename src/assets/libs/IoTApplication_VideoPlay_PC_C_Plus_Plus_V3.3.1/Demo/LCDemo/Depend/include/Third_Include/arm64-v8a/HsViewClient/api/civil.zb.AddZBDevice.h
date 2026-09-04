/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddZBDevice_H_
#define _HSVIEW_CLIENT_API_AddZBDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加配件。
【需要使用平台账号签名】
 */

typedef struct AddZBDeviceRequest 
{
	HsviewRequest base;

	struct AddZBDeviceRequestData
	{
		
		/** 配件ID */
		CSTR zbDeviceId;
		/** 配件名称 */
		CSTR zbDeviceName;
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} AddZBDeviceRequest;

C_API AddZBDeviceRequest *HSAPI_INIT(AddZBDeviceRequest);

typedef struct AddZBDeviceResponse 
{
	HsviewResponse base;

	struct AddZBDeviceResponseData
	{
		
		/** 配件类型 */
		CSTR type;
		/** 配件ID */
		CSTR zbDeviceId;
		/** 配件名称 */
		CSTR zbDeviceName;
		/** 盒子的设备ID */
		CSTR deviceId;
		/** [int]在线状态 */
		int online;
		/** [int]强制升级标识。0或者为空表示不需要强制升级，1需要。 */
		int forceUpgrade;
		/** 配件型号 */
		CSTR model;
		/** 配件状态 */
		CSTR status;
		/** 通道号 */
		CSTR channelId;
 
	} data;

} AddZBDeviceResponse;

C_API AddZBDeviceResponse *HSAPI_INIT(AddZBDeviceResponse);

#endif
