/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferTime_TimeGet_H_
#define _HSVIEW_CLIENT_API_transferTime_TimeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备UTC时间

参考PaaS协议：[获取设备UTC时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E9%97%B4%2F%E8%8E%B7%E5%8F%96%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferTime_TimeGetRequest 
{
	HsviewRequest base;

	struct transferTime_TimeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/time/query */
		#define _STATIC_transferTime_TimeGetRequestData_url "/device/time/query"
		CSTR url;

	} data;

} transferTime_TimeGetRequest;

C_API transferTime_TimeGetRequest *HSAPI_INIT(transferTime_TimeGetRequest);

typedef struct transferTime_TimeGetResponse 
{
	HsviewResponse base;

	struct transferTime_TimeGetResponseData
	{
		
		/** UTC时间。yyyyMMddTHHmmssZ例如20170613T160000Z */
		CSTR time;
 
	} data;

} transferTime_TimeGetResponse;

C_API transferTime_TimeGetResponse *HSAPI_INIT(transferTime_TimeGetResponse);

#endif
