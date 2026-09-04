/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_ModifyAPDevice_H_
#define _HSVIEW_CLIENT_API_agOperate_ModifyAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改配件名称。

有些特殊配件名称需要设置到配件，会带有配件名称配置能力集ModifyName，有该能力集的"toDevice"必须设置为yes；无该能力集设置no或不带该字段

参考PaaS协议：[设置配件名称](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%AE%BE%E7%BD%AE%E5%90%8D%E7%A7%B0.md&s=pd)


【需要使用平台账号签名】
 */

typedef struct agOperate_ModifyAPDeviceRequest 
{
	HsviewRequest base;

	struct agOperate_ModifyAPDeviceRequestData
	{
		
		/** [O]是否设置到设备：yes,no;没有该字段服务当no处理，不下发 */
		CSTR toDevice;
		/** 配件ID */
		CSTR apId;
		/** 配件名称 */
		CSTR apName;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_ModifyAPDeviceRequest;

C_API agOperate_ModifyAPDeviceRequest *HSAPI_INIT(agOperate_ModifyAPDeviceRequest);

typedef struct agOperate_ModifyAPDeviceResponse 
{
	HsviewResponse base;

	struct agOperate_ModifyAPDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_ModifyAPDeviceResponse;

C_API agOperate_ModifyAPDeviceResponse *HSAPI_INIT(agOperate_ModifyAPDeviceResponse);

#endif
