/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_StorageFormat_H_
#define _HSVIEW_CLIENT_API_transferDevice_StorageFormat_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
存储介质格式化

参考PaaS协议：[存储介质格式化](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AD%98%E5%82%A8%E4%BB%8B%E8%B4%A8%E9%85%8D%E7%BD%AE%2F%E5%AD%98%E5%82%A8%E4%BB%8B%E8%B4%A8%E6%A0%BC%E5%BC%8F%E5%8C%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_StorageFormatRequest 
{
	HsviewRequest base;

	struct transferDevice_StorageFormatRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/storage/format */
		#define _STATIC_transferDevice_StorageFormatRequestData_url "/device/storage/format"
		CSTR url;

	} data;

} transferDevice_StorageFormatRequest;

C_API transferDevice_StorageFormatRequest *HSAPI_INIT(transferDevice_StorageFormatRequest);

typedef struct transferDevice_StorageFormatResponse 
{
	HsviewResponse base;

	struct transferDevice_StorageFormatResponseData
	{
		
		/** 存储介质状态，format: 开始格式化;formating: 正在格式化;formated: 已被格式化 */
		CSTR status;
 
	} data;

} transferDevice_StorageFormatResponse;

C_API transferDevice_StorageFormatResponse *HSAPI_INIT(transferDevice_StorageFormatResponse);

#endif
