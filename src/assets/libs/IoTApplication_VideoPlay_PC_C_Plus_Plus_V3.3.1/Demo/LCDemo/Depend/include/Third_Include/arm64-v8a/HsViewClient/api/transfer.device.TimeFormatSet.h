/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_TimeFormatSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_TimeFormatSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置时间格式

设备需要有TimeFormat能力集才支持

format：[String]，时间格式：
	yyyy-MM-dd：年月日，对应到设备为yyyy-MM-dd HH:mm:ss；
	MM-dd-yyyy：月日年，对应到设备为MM-dd-yyyy HH:mm:ss；
	dd-MM-yyyy：日月年，对应到设备为dd-MM-yyyy HH:mm:ss；

参考PaaS协议：[设置时间格式](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E9%97%B4%E6%A0%BC%E5%BC%8F%2F%E8%AE%BE%E7%BD%AE%E6%97%B6%E9%97%B4%E6%A0%BC%E5%BC%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_TimeFormatSetRequest 
{
	HsviewRequest base;

	struct transferDevice_TimeFormatSetRequestData
	{
		
		/** [cstr]/device/time/format/config */
		#define _STATIC_transferDevice_TimeFormatSetRequestData_url "/device/time/format/config"
		CSTR url;
		/** struct of transferDevice_TimeFormatSetRequestData_Content */
		struct transferDevice_TimeFormatSetRequestData_Content {
			/** 时间格式:yyyy-MM-dd */
			CSTR format;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_TimeFormatSetRequest;

C_API transferDevice_TimeFormatSetRequest *HSAPI_INIT(transferDevice_TimeFormatSetRequest);

typedef struct transferDevice_TimeFormatSetResponse 
{
	HsviewResponse base;

	struct transferDevice_TimeFormatSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_TimeFormatSetResponse;

C_API transferDevice_TimeFormatSetResponse *HSAPI_INIT(transferDevice_TimeFormatSetResponse);

#endif
