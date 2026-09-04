/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_orderInfo_OrderBindDev_H_
#define _HSVIEW_CLIENT_API_orderInfo_OrderBindDev_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

订单号与业务的绑定
【需要使用平台账号签名】
 */

typedef struct orderInfo_OrderBindDevRequest 
{
	HsviewRequest base;

	struct orderInfo_OrderBindDevRequestData
	{
		
		/** storage:云存储；wonderful：精彩一天;share:分享套餐; numberStat：客流量套餐 */
		CSTR type;
		/** 商户订单号 */
		CSTR orderId;
		/** [O]通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} orderInfo_OrderBindDevRequest;

C_API orderInfo_OrderBindDevRequest *HSAPI_INIT(orderInfo_OrderBindDevRequest);

typedef struct orderInfo_OrderBindDevResponse 
{
	HsviewResponse base;

	struct orderInfo_OrderBindDevResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} orderInfo_OrderBindDevResponse;

C_API orderInfo_OrderBindDevResponse *HSAPI_INIT(orderInfo_OrderBindDevResponse);

#endif
