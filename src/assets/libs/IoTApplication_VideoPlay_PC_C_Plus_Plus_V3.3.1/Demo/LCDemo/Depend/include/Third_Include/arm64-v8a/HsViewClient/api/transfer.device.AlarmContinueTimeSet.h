/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_AlarmContinueTimeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_AlarmContinueTimeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警持续时间

报警持续时间配置能力集ACT

参考PaaS协议：[设置报警持续时间](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E6%8C%81%E7%BB%AD%E6%97%B6%E9%97%B4%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E6%8A%A5%E8%AD%A6%E6%8C%81%E7%BB%AD%E6%97%B6%E9%97%B4.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_AlarmContinueTimeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_AlarmContinueTimeSetRequestData
	{
		
		/** [cstr]/device/alarm/continu/time/config */
		#define _STATIC_transferDevice_AlarmContinueTimeSetRequestData_url "/device/alarm/continu/time/config"
		CSTR url;
		/** struct of transferDevice_AlarmContinueTimeSetRequestData_Content */
		struct transferDevice_AlarmContinueTimeSetRequestData_Content {
			/** 报警持续时间，单位为秒S */
			CSTR time;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_AlarmContinueTimeSetRequest;

C_API transferDevice_AlarmContinueTimeSetRequest *HSAPI_INIT(transferDevice_AlarmContinueTimeSetRequest);

typedef struct transferDevice_AlarmContinueTimeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_AlarmContinueTimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_AlarmContinueTimeSetResponse;

C_API transferDevice_AlarmContinueTimeSetResponse *HSAPI_INIT(transferDevice_AlarmContinueTimeSetResponse);

#endif
