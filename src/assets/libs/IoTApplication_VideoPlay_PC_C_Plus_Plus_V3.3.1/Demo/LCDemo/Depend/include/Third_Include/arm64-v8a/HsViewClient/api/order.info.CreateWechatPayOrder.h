/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_orderInfo_CreateWechatPayOrder_H_
#define _HSVIEW_CLIENT_API_orderInfo_CreateWechatPayOrder_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建微信订单接口，
错误码：
13504：操作套餐不存在
【需要使用平台账号签名】
 */

typedef struct orderInfo_CreateWechatPayOrderRequest 
{
	HsviewRequest base;

	struct orderInfo_CreateWechatPayOrderRequestData
	{
		
		/** [long]商品唯一id */
		int64 id;
		/** storage:云存储；wonderful：精彩一天;share:分享套餐; numberStat：客流量套餐 */
		CSTR type;
		/** [int]购买数量 */
		int num;

	} data;

} orderInfo_CreateWechatPayOrderRequest;

C_API orderInfo_CreateWechatPayOrderRequest *HSAPI_INIT(orderInfo_CreateWechatPayOrderRequest);

typedef struct orderInfo_CreateWechatPayOrderResponse 
{
	HsviewResponse base;

	struct orderInfo_CreateWechatPayOrderResponseData
	{
		
		/** [long][O]时间戳，app请求时，为必选字段，pc请求为空 */
		int64 timestamp;
		/** [O]随机字符串，app请求时，为必选字段，pc请求为空 */
		CSTR noncestr;
		/** [O]app移动支付签名字符串信息，app请求时，为必选字段，pc请求为空 */
		CSTR appSign;
		/** 平台订单订单号 */
		CSTR orderId;
		/** [O]商户号，app请求时，为必选字段，pc请求为空 */
		CSTR partnerid;
		/**  pc客户端请求时为二维码链接（Base64编码后），app请求则为预付单信息，即prepayId */
		CSTR prepayInfo;
 
	} data;

} orderInfo_CreateWechatPayOrderResponse;

C_API orderInfo_CreateWechatPayOrderResponse *HSAPI_INIT(orderInfo_CreateWechatPayOrderResponse);

#endif
