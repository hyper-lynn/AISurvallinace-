/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_TimeFormatGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_TimeFormatGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取时间格式

设备需要有TimeFormat能力集才支持

format：[String]，时间格式：
	yyyy-MM-dd：年月日，符合年月日顺序的都认为是该格式，如yy-M-d, yy-MM-d, yy-M-dd, yy-MM-dd, yyyy-M-d, yyyy-MM-d, yyyy-M-dd, yyyy-MM-dd；
	MM-dd-yyyy：月日年，符合月日年顺序的都认为是该格式，同上；
	dd-MM-yyyy：日月年，符合日月年顺序的都认为是该格式，同上；

参考PaaS协议：[获取时间格式](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E9%97%B4%E6%A0%BC%E5%BC%8F%2F%E8%8E%B7%E5%8F%96%E6%97%B6%E9%97%B4%E6%A0%BC%E5%BC%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_TimeFormatGetRequest 
{
	HsviewRequest base;

	struct transferDevice_TimeFormatGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/time/format/query */
		#define _STATIC_transferDevice_TimeFormatGetRequestData_url "/device/time/format/query"
		CSTR url;

	} data;

} transferDevice_TimeFormatGetRequest;

C_API transferDevice_TimeFormatGetRequest *HSAPI_INIT(transferDevice_TimeFormatGetRequest);

typedef struct transferDevice_TimeFormatGetResponse 
{
	HsviewResponse base;

	struct transferDevice_TimeFormatGetResponseData
	{
		
		/** 时间格式:如yyyy-MM-dd */
		CSTR format;
 
	} data;

} transferDevice_TimeFormatGetResponse;

C_API transferDevice_TimeFormatGetResponse *HSAPI_INIT(transferDevice_TimeFormatGetResponse);

#endif
