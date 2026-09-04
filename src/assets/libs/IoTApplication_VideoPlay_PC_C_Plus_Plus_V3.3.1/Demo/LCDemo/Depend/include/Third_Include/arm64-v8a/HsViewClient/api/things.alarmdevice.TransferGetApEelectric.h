/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferGetApEelectric_H_
#define _HSVIEW_CLIENT_API_TransferGetApEelectric_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件电量查询

响应内容说明参考PaaS协议：[报警网关配件电量查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E7%94%B5%E9%87%8F%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferGetApEelectricRequest 
{
	HsviewRequest base;

	struct TransferGetApEelectricRequestData
	{
		
		/** 配件id */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferGetApEelectricRequest;

C_API TransferGetApEelectricRequest *HSAPI_INIT(TransferGetApEelectricRequest);

typedef struct TransferGetApEelectricResponse 
{
	HsviewResponse base;

	struct TransferGetApEelectricResponseData
	{
		
		/** [int]80,电量百分比 */
		int electric;
 
	} data;

} TransferGetApEelectricResponse;

C_API TransferGetApEelectricResponse *HSAPI_INIT(TransferGetApEelectricResponse);

#endif
