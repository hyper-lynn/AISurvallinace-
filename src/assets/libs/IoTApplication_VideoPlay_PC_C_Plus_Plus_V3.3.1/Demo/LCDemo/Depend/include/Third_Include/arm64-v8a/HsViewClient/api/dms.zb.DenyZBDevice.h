/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DenyZBDevice_H_
#define _HSVIEW_CLIENT_API_DenyZBDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
拒绝指定ID的配件。
 */

typedef struct DenyZBDeviceRequest 
{
	HsviewRequest base;

	struct DenyZBDeviceRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_DenyZBDeviceRequestData_METHOD "POST"
		/** [cstr]ihg-cmd/denyZBDevice */
		#define _STATIC_DenyZBDeviceRequestData_CMD "ihg-cmd/denyZBDevice"
		/** struct of DenyZBDeviceRequestData_Body */
		struct DenyZBDeviceRequestData_Body {
			/** 配件ID */
			CSTR ZBDeviceID;
		} body;

	} data;

} DenyZBDeviceRequest;

C_API DenyZBDeviceRequest *HSAPI_INIT(DenyZBDeviceRequest);

typedef struct DenyZBDeviceResponse 
{
	HsviewResponse base;

	struct DenyZBDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DenyZBDeviceResponse;

C_API DenyZBDeviceResponse *HSAPI_INIT(DenyZBDeviceResponse);

#endif
