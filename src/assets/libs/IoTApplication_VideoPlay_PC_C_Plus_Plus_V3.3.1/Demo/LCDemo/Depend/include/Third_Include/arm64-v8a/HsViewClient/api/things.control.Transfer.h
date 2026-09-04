/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_Transfer_H_
#define _HSVIEW_CLIENT_API_thingsControl_Transfer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

响应内容说明参考PaaS协议：[paas下行透传协议](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%80%8F%E4%BC%A0%E5%8D%8F%E8%AE%AE%2F%E4%B8%8B%E8%A1%8C%E9%80%8F%E4%BC%A0%E6%8E%A5%E5%8F%A3.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_TransferRequest 
{
	HsviewRequest base;

	struct thingsControl_TransferRequestData
	{
		
		/** [O]透传内容 */
		CSTR content;
		/** [O]透传协议url */
		CSTR url;
		/** [O]方法 */
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsControl_TransferRequest;

C_API thingsControl_TransferRequest *HSAPI_INIT(thingsControl_TransferRequest);

typedef struct thingsControl_TransferResponse 
{
	HsviewResponse base;

	struct thingsControl_TransferResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_TransferResponse;

C_API thingsControl_TransferResponse *HSAPI_INIT(thingsControl_TransferResponse);

#endif
