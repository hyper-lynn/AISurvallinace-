/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferAnswer_H_
#define _HSVIEW_CLIENT_API_TransferAnswer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
接听门口机呼叫

响应内容说明参考PaaS协议：[门口机接听](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8B%92%E6%8E%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferAnswerRequest 
{
	HsviewRequest base;

	struct TransferAnswerRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} TransferAnswerRequest;

C_API TransferAnswerRequest *HSAPI_INIT(TransferAnswerRequest);

typedef struct TransferAnswerResponse 
{
	HsviewResponse base;

	struct TransferAnswerResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferAnswerResponse;

C_API TransferAnswerResponse *HSAPI_INIT(TransferAnswerResponse);

#endif
