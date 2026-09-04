/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CreateDevShareStrategy_H_
#define _HSVIEW_CLIENT_API_CreateDevShareStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建订单
【使用平台账号签名】
 */

typedef struct CreateDevShareStrategyRequest 
{
	HsviewRequest base;

	struct CreateDevShareStrategyRequestData
	{
		
		/** [long]套餐id */
		int64 strategyId;
		/** 第三方支付类型，alipay/weixin */
		CSTR thirdPay;
		/** 通道号ID */
		CSTR channelId;
		/** [int]购买分享次数 */
		int shareNum;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} CreateDevShareStrategyRequest;

C_API CreateDevShareStrategyRequest *HSAPI_INIT(CreateDevShareStrategyRequest);

typedef struct CreateDevShareStrategyResponse 
{
	HsviewResponse base;

	struct CreateDevShareStrategyResponseData
	{
		
		/** 订单信息; phone客户端则为请求支付订单信息，pc客户端则为表单信息 */
		CSTR orderInfo;
		/** 订单id */
		CSTR orderId;
 
	} data;

} CreateDevShareStrategyResponse;

C_API CreateDevShareStrategyResponse *HSAPI_INIT(CreateDevShareStrategyResponse);

#endif
