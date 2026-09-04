/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_CreateReportStrategyOrder_H_
#define _HSVIEW_CLIENT_API_numberstatReport_CreateReportStrategyOrder_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
购买客流统计套餐
=== description
orderId：订单ID，平台需保证唯一
orderInfo：平台通过第三方支付的协议约定，生成带签名的支付订单信息
orderInfo：BASE64(订单信息),平台通过第三方支付的协议约定，生成带签名的支付订单信息

错误码：
1、13504 :套餐不存在
2、13502 ：第三方支付类型不支持
【使用平台账号签名】
 */

typedef struct numberstatReport_CreateReportStrategyOrderRequest 
{
	HsviewRequest base;

	struct numberstatReport_CreateReportStrategyOrderRequestData
	{
		
		/** 第三方支付类型，alipay/wechat */
		CSTR thirdPay;
		/** [int]套餐的购买数量 */
		int num;
		/**  [long]报表id */
		CSTR reportId;
		/** [long]套餐ID */
		int64 strategyId;

	} data;

} numberstatReport_CreateReportStrategyOrderRequest;

C_API numberstatReport_CreateReportStrategyOrderRequest *HSAPI_INIT(numberstatReport_CreateReportStrategyOrderRequest);

typedef struct numberstatReport_CreateReportStrategyOrderResponse 
{
	HsviewResponse base;

	struct numberstatReport_CreateReportStrategyOrderResponseData
	{
		
		/** BASE64(支付订单信息),如果是pc客户端请求，则为表单信息 */
		CSTR orderInfo;
		/** 订单ID，0123456789-123456 */
		CSTR orderId;
 
	} data;

} numberstatReport_CreateReportStrategyOrderResponse;

C_API numberstatReport_CreateReportStrategyOrderResponse *HSAPI_INIT(numberstatReport_CreateReportStrategyOrderResponse);

#endif
