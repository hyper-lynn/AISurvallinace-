/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferHangup_H_
#define _HSVIEW_CLIENT_API_TransferHangup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
挂断门口机呼叫

响应内容说明参考PaaS协议：[门口机挂断](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8C%82%E6%96%AD.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferHangupRequest 
{
	HsviewRequest base;

	struct TransferHangupRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} TransferHangupRequest;

C_API TransferHangupRequest *HSAPI_INIT(TransferHangupRequest);

typedef struct TransferHangupResponse 
{
	HsviewResponse base;

	struct TransferHangupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferHangupResponse;

C_API TransferHangupResponse *HSAPI_INIT(TransferHangupResponse);

#endif
