/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SwitchZBDevice_H_
#define _HSVIEW_CLIENT_API_SwitchZBDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
手动开关指定通道号的插座。
 */

typedef struct SwitchZBDeviceRequest 
{
	HsviewRequest base;

	struct SwitchZBDeviceRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SwitchZBDeviceRequestData_METHOD "POST"
		/** [cstr]ihg-cmd/setZBDeviceManualSwitch */
		#define _STATIC_SwitchZBDeviceRequestData_CMD "ihg-cmd/setZBDeviceManualSwitch"
		/** struct of SwitchZBDeviceRequestData_Body */
		struct SwitchZBDeviceRequestData_Body {
			/** 配件ID */
			CSTR ZBDeviceID;
			/** on或off */
			CSTR Operation;
		} body;

	} data;

} SwitchZBDeviceRequest;

C_API SwitchZBDeviceRequest *HSAPI_INIT(SwitchZBDeviceRequest);

typedef struct SwitchZBDeviceResponse 
{
	HsviewResponse base;

	struct SwitchZBDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SwitchZBDeviceResponse;

C_API SwitchZBDeviceResponse *HSAPI_INIT(SwitchZBDeviceResponse);

#endif
