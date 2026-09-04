/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_LightStatusGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_LightStatusGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取灯状态---------------仅Amcrest定制使用

参考PaaS协议：[获取灯状态](http://paas.dahuatech.com/wiki/?p=%2F%E5%AE%9A%E5%88%B6%E5%AE%A2%E6%88%B7%2Fzencam%2F%E8%8E%B7%E5%8F%96%E7%81%AF%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_LightStatusGetRequest 
{
	HsviewRequest base;

	struct transferDevice_LightStatusGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/light/status/query */
		#define _STATIC_transferDevice_LightStatusGetRequestData_url "/device/light/status/query"
		CSTR url;

	} data;

} transferDevice_LightStatusGetRequest;

C_API transferDevice_LightStatusGetRequest *HSAPI_INIT(transferDevice_LightStatusGetRequest);

typedef struct transferDevice_LightStatusGetResponse 
{
	HsviewResponse base;

	struct transferDevice_LightStatusGetResponseData
	{
		
		/** 灯状态，有三种，Light、Strobe、Off */
		CSTR status;
 
	} data;

} transferDevice_LightStatusGetResponse;

C_API transferDevice_LightStatusGetResponse *HSAPI_INIT(transferDevice_LightStatusGetResponse);

#endif
