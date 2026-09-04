/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_LightStatusSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_LightStatusSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
触发灯操作---------------仅Amcrest定制使用

参考PaaS协议：[触发灯操作](http://paas.dahuatech.com/wiki/?p=%2F%E5%AE%9A%E5%88%B6%E5%AE%A2%E6%88%B7%2Fzencam%2F%E8%A7%A6%E5%8F%91%E7%81%AF%E6%93%8D%E4%BD%9C.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_LightStatusSetRequest 
{
	HsviewRequest base;

	struct transferDevice_LightStatusSetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/light/status/config */
		#define _STATIC_transferDevice_LightStatusSetRequestData_url "/device/light/status/config"
		CSTR url;

	} data;

} transferDevice_LightStatusSetRequest;

C_API transferDevice_LightStatusSetRequest *HSAPI_INIT(transferDevice_LightStatusSetRequest);

typedef struct transferDevice_LightStatusSetResponse 
{
	HsviewResponse base;

	struct transferDevice_LightStatusSetResponseData
	{
		
		/** 灯状态，有三种，Light、Strobe、Off */
		CSTR status;
 
	} data;

} transferDevice_LightStatusSetResponse;

C_API transferDevice_LightStatusSetResponse *HSAPI_INIT(transferDevice_LightStatusSetResponse);

#endif
