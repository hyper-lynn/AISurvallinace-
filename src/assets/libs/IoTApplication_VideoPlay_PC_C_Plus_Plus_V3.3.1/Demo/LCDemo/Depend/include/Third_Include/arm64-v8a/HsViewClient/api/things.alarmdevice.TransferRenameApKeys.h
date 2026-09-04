/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferRenameApKeys_H_
#define _HSVIEW_CLIENT_API_TransferRenameApKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报警网关配件钥匙命名

transferContent内容说明参考PaaS协议：[报警网关配件钥匙设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%AE%BE%E7%BD%AE%E9%92%A5%E5%8C%99.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferRenameApKeysRequest 
{
	HsviewRequest base;

	struct TransferRenameApKeysRequestData
	{
		
		/** struct of TransferRenameApKeysRequestData_TransferContent */
		struct TransferRenameApKeysRequestData_TransferContent {
			/** define a list with struct of TransferRenameApKeysRequestData_TransferContent_KeysElement */
			DECLARE_LIST(struct TransferRenameApKeysRequestData_TransferContent_KeysElement
			{
				/** [O]xxxx */
				CSTR oldKey;
				/** 钥匙类型 */
				CSTR type;
				/** [O]钥匙名称 */
				CSTR name;
				/** [O]20170418T162832 */
				CSTR failedLocalTime;
				/** 密码、卡、指纹的唯一标示符 */
				CSTR keyId;
				/** [O]20170418T162832Z */
				CSTR failedUtcTime;
				/** [O]true */
				CSTR enable;
				/** [O]xxxx */
				CSTR newKey;
			}) keys;
		} transferContent;
		/** 配件id */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferRenameApKeysRequest;

C_API TransferRenameApKeysRequest *HSAPI_INIT(TransferRenameApKeysRequest);

typedef struct TransferRenameApKeysResponse 
{
	HsviewResponse base;

	struct TransferRenameApKeysResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferRenameApKeysResponse;

C_API TransferRenameApKeysResponse *HSAPI_INIT(TransferRenameApKeysResponse);

#endif
