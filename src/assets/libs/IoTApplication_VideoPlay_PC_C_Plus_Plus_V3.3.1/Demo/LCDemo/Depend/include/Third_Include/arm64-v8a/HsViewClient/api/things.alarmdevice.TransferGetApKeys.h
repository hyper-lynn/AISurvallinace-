/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferGetApKeys_H_
#define _HSVIEW_CLIENT_API_TransferGetApKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警网关配件钥匙

响应内容说明参考PaaS协议：[获取报警网关配件钥匙](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E9%92%A5%E5%8C%99.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferGetApKeysRequest 
{
	HsviewRequest base;

	struct TransferGetApKeysRequestData
	{
		
		/** 配件id */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferGetApKeysRequest;

C_API TransferGetApKeysRequest *HSAPI_INIT(TransferGetApKeysRequest);

typedef struct TransferGetApKeysResponse 
{
	HsviewResponse base;

	struct TransferGetApKeysResponseData
	{
		
		/** define a list with struct of TransferGetApKeysResponseData_KeysElement */
		DECLARE_LIST(struct TransferGetApKeysResponseData_KeysElement
		{
			/** 钥匙类型 */
			CSTR type;
			/** [O]秘钥失效的UTC时间，遵循时间格式要求，如：20170418T162832Z */
			CSTR failedUtcTime;
			/** 密码、卡、指纹的唯一标示符 */
			CSTR keyId;
			/** [O]秘钥生成的UTC时间，遵循时间格式要求，如：20170418T162832Z */
			CSTR createUtcTime;
			/** [O]true */
			CSTR bManager;
			/** 钥匙名称 */
			CSTR name;
			/** [O]秘钥失效的设备本地时间，遵循时间格式要求，如：20170418T162832 */
			CSTR failedLocaltime;
			/** [O]密码、卡、指纹的归属账号 */
			CSTR accountNumber;
			/** [O]true */
			CSTR enable;
			/** [O]秘钥生成的设备本地时间，遵循时间格式要求，如：20170418T162832 */
			CSTR createLocaltime;
		}) keys;
 
	} data;

} TransferGetApKeysResponse;

C_API TransferGetApKeysResponse *HSAPI_INIT(TransferGetApKeysResponse);

#endif
