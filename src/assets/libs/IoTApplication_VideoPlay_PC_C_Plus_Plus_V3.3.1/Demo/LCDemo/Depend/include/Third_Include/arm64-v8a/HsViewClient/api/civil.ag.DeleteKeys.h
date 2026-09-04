/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteKeys_H_
#define _HSVIEW_CLIENT_API_DeleteKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除钥匙。

响应内容说明参考PaaS协议：[删除钥匙](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E5%88%A0%E9%99%A4%E9%92%A5%E5%8C%99.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct DeleteKeysRequest 
{
	HsviewRequest base;

	struct DeleteKeysRequestData
	{
		
		/** xxxx */
		CSTR keyId;
		/** 配件ID */
		CSTR apId;
		/** password:密码,card:卡,fingerPrint:指纹,snapkey:临时秘钥 */
		CSTR type;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} DeleteKeysRequest;

C_API DeleteKeysRequest *HSAPI_INIT(DeleteKeysRequest);

typedef struct DeleteKeysResponse 
{
	HsviewResponse base;

	struct DeleteKeysResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteKeysResponse;

C_API DeleteKeysResponse *HSAPI_INIT(DeleteKeysResponse);

#endif
