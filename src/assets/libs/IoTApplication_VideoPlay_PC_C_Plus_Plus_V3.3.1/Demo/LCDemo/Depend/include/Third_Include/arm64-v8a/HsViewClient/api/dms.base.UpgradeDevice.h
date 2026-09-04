/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpgradeDevice_H_
#define _HSVIEW_CLIENT_API_UpgradeDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
升级设备。
请求中告知设备升级包的URL
 */

typedef struct UpgradeDeviceRequest 
{
	HsviewRequest base;

	struct UpgradeDeviceRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_UpgradeDeviceRequestData_METHOD "POST"
		/** [cstr]upgrade */
		#define _STATIC_UpgradeDeviceRequestData_CMD "upgrade"
		/** struct of UpgradeDeviceRequestData_Body */
		struct UpgradeDeviceRequestData_Body {
			/** 升级包地址 */
			CSTR Package;
		} body;

	} data;

} UpgradeDeviceRequest;

C_API UpgradeDeviceRequest *HSAPI_INIT(UpgradeDeviceRequest);

typedef struct UpgradeDeviceResponse 
{
	HsviewResponse base;

	struct UpgradeDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpgradeDeviceResponse;

C_API UpgradeDeviceResponse *HSAPI_INIT(UpgradeDeviceResponse);

#endif
