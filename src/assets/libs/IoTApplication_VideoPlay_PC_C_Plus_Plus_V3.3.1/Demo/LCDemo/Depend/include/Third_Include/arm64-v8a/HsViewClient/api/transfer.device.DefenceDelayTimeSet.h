/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceDelayTimeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceDelayTimeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置布防延时时间

布防延时能力集DDT

参考PaaS协议：[设置布防延时时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%B8%83%E9%98%B2%E5%BB%B6%E6%97%B6%E6%97%B6%E9%97%B4%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E5%B8%83%E9%98%B2%E5%BB%B6%E6%97%B6%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceDelayTimeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceDelayTimeSetRequestData
	{
		
		/** [cstr]/device/defence/delay/time/config */
		#define _STATIC_transferDevice_DefenceDelayTimeSetRequestData_url "/device/defence/delay/time/config"
		CSTR url;
		/** struct of transferDevice_DefenceDelayTimeSetRequestData_Content */
		struct transferDevice_DefenceDelayTimeSetRequestData_Content {
			/** 布防延时时间，单位为秒S */
			CSTR time;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_DefenceDelayTimeSetRequest;

C_API transferDevice_DefenceDelayTimeSetRequest *HSAPI_INIT(transferDevice_DefenceDelayTimeSetRequest);

typedef struct transferDevice_DefenceDelayTimeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceDelayTimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_DefenceDelayTimeSetResponse;

C_API transferDevice_DefenceDelayTimeSetResponse *HSAPI_INIT(transferDevice_DefenceDelayTimeSetResponse);

#endif
