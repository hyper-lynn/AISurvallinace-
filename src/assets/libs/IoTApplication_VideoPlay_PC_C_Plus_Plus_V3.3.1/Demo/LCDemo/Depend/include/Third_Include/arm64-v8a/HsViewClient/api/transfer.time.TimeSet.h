/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferTime_TimeSet_H_
#define _HSVIEW_CLIENT_API_transferTime_TimeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备UTC时间

参考PaaS协议：[设置设备UTC时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E9%97%B4%2F%E8%AE%BE%E7%BD%AE%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferTime_TimeSetRequest 
{
	HsviewRequest base;

	struct transferTime_TimeSetRequestData
	{
		
		/** [cstr]/device/time/config */
		#define _STATIC_transferTime_TimeSetRequestData_url "/device/time/config"
		CSTR url;
		/** struct of transferTime_TimeSetRequestData_Content */
		struct transferTime_TimeSetRequestData_Content {
			/** UTC时间。yyyyMMddTHHmmssZ例如20170613T160000Z */
			CSTR time;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferTime_TimeSetRequest;

C_API transferTime_TimeSetRequest *HSAPI_INIT(transferTime_TimeSetRequest);

typedef struct transferTime_TimeSetResponse 
{
	HsviewResponse base;

	struct transferTime_TimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferTime_TimeSetResponse;

C_API transferTime_TimeSetResponse *HSAPI_INIT(transferTime_TimeSetResponse);

#endif
