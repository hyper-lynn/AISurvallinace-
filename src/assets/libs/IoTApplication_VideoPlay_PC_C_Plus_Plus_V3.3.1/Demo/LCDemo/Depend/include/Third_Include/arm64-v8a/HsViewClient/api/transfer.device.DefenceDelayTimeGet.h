/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceDelayTimeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceDelayTimeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取布防延时时间

布防延时能力集DDT

参考PaaS协议：[获取布防延时时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%B8%83%E9%98%B2%E5%BB%B6%E6%97%B6%E6%97%B6%E9%97%B4%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E5%B8%83%E9%98%B2%E5%BB%B6%E6%97%B6%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceDelayTimeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceDelayTimeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/defence/delay/time/query */
		#define _STATIC_transferDevice_DefenceDelayTimeGetRequestData_url "/device/defence/delay/time/query"
		CSTR url;

	} data;

} transferDevice_DefenceDelayTimeGetRequest;

C_API transferDevice_DefenceDelayTimeGetRequest *HSAPI_INIT(transferDevice_DefenceDelayTimeGetRequest);

typedef struct transferDevice_DefenceDelayTimeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceDelayTimeGetResponseData
	{
		
		/** 布防延时时间，单位为秒S */
		CSTR time;
 
	} data;

} transferDevice_DefenceDelayTimeGetResponse;

C_API transferDevice_DefenceDelayTimeGetResponse *HSAPI_INIT(transferDevice_DefenceDelayTimeGetResponse);

#endif
