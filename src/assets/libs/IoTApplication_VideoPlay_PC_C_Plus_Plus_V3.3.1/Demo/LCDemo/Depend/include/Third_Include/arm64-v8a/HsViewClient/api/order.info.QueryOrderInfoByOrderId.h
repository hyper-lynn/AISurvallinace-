/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_orderInfo_QueryOrderInfoByOrderId_H_
#define _HSVIEW_CLIENT_API_orderInfo_QueryOrderInfoByOrderId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

查询套餐订单状态，orderId为商户订单号
【需要使用平台账号签名】
 */

typedef struct orderInfo_QueryOrderInfoByOrderIdRequest 
{
	HsviewRequest base;

	struct orderInfo_QueryOrderInfoByOrderIdRequestData
	{
		
		/** storage:云存储；wonderful：精彩一天;share:分享套餐; numberStat：客流量套餐 */
		CSTR type;
		/** 商户订单号 */
		CSTR orderId;

	} data;

} orderInfo_QueryOrderInfoByOrderIdRequest;

C_API orderInfo_QueryOrderInfoByOrderIdRequest *HSAPI_INIT(orderInfo_QueryOrderInfoByOrderIdRequest);

typedef struct orderInfo_QueryOrderInfoByOrderIdResponse 
{
	HsviewResponse base;

	struct orderInfo_QueryOrderInfoByOrderIdResponseData
	{
		
		/** 订单状态，wait_pay:未支付；success：支付成功 */
		CSTR state;
 
	} data;

} orderInfo_QueryOrderInfoByOrderIdResponse;

C_API orderInfo_QueryOrderInfoByOrderIdResponse *HSAPI_INIT(orderInfo_QueryOrderInfoByOrderIdResponse);

#endif
