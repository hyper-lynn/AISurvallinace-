/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_RenewDevShareStrategy_H_
#define _HSVIEW_CLIENT_API_RenewDevShareStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
套餐续费时，创建订单
【使用平台账号签名】
 */

typedef struct RenewDevShareStrategyRequest 
{
	HsviewRequest base;

	struct RenewDevShareStrategyRequestData
	{
		
		/** [long]套餐列表id */
		int64 strategyListId;
		/** [int]购买分享次数 */
		int shareNum;
		/** 第三方支付类型，alipay/weixin */
		CSTR thirdPay;
		/** 通道号ID */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} RenewDevShareStrategyRequest;

C_API RenewDevShareStrategyRequest *HSAPI_INIT(RenewDevShareStrategyRequest);

typedef struct RenewDevShareStrategyResponse 
{
	HsviewResponse base;

	struct RenewDevShareStrategyResponseData
	{
		
		/** 订单信息; phone客户端则为请求支付订单信息，pc客户端则为表单信息 */
		CSTR orderInfo;
		/** 订单id */
		CSTR orderId;
 
	} data;

} RenewDevShareStrategyResponse;

C_API RenewDevShareStrategyResponse *HSAPI_INIT(RenewDevShareStrategyResponse);

#endif
