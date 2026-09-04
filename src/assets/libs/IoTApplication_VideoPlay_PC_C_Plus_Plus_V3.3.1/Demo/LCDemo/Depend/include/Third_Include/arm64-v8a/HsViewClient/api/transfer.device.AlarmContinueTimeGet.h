/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_AlarmContinueTimeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_AlarmContinueTimeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警持续时间

报警持续时间配置能力集ACT

参考PaaS协议：[获取报警持续时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E6%8C%81%E7%BB%AD%E6%97%B6%E9%97%B4%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E6%8A%A5%E8%AD%A6%E6%8C%81%E7%BB%AD%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_AlarmContinueTimeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_AlarmContinueTimeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/alarm/continu/time/query */
		#define _STATIC_transferDevice_AlarmContinueTimeGetRequestData_url "/device/alarm/continu/time/query"
		CSTR url;

	} data;

} transferDevice_AlarmContinueTimeGetRequest;

C_API transferDevice_AlarmContinueTimeGetRequest *HSAPI_INIT(transferDevice_AlarmContinueTimeGetRequest);

typedef struct transferDevice_AlarmContinueTimeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_AlarmContinueTimeGetResponseData
	{
		
		/** 报警持续时间，单位为秒S */
		CSTR time;
 
	} data;

} transferDevice_AlarmContinueTimeGetResponse;

C_API transferDevice_AlarmContinueTimeGetResponse *HSAPI_INIT(transferDevice_AlarmContinueTimeGetResponse);

#endif
