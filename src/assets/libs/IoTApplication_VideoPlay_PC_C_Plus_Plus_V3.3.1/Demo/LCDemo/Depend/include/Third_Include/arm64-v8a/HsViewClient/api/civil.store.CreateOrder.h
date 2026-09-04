/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CreateOrder_H_
#define _HSVIEW_CLIENT_API_CreateOrder_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
orderId：订单ID，平台需保证唯一
orderInfo：平台通过第三方支付的协议约定，生成带签名的支付订单信息
orderInfo：BASE64(订单信息),平台通过第三方支付的协议约定，生成带签名的支付订单信息

错误码：
1、1604 : 云存储套餐不存在
2、8002 ：第三方支付类型不支持
 */

typedef struct CreateOrderRequest 
{
	HsviewRequest base;

	struct CreateOrderRequestData
	{
		
		/** [int]套餐的购买数量 */
		int num;
		/** [long]云存储收费套餐ID */
		int64 strategyId;
		/** 第三方支付类型，alipay/weixin */
		CSTR thirdPay;
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} CreateOrderRequest;

C_API CreateOrderRequest *HSAPI_INIT(CreateOrderRequest);

typedef struct CreateOrderResponse 
{
	HsviewResponse base;

	struct CreateOrderResponseData
	{
		
		/** BASE64(支付订单信息),如果是pc客户端请求，则为表单信息 */
		CSTR orderInfo;
		/** 订单ID，0123456789-123456 */
		CSTR orderId;
 
	} data;

} CreateOrderResponse;

C_API CreateOrderResponse *HSAPI_INIT(CreateOrderResponse);

#endif
