/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageAndOrderStatusGet_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageAndOrderStatusGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

查询订单状态
 */

typedef struct strategyOrder_CloudStorageAndOrderStatusGetRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageAndOrderStatusGetRequestData
	{
		
		/** 订单id */
		CSTR orderNo;

	} data;

} strategyOrder_CloudStorageAndOrderStatusGetRequest;

C_API strategyOrder_CloudStorageAndOrderStatusGetRequest *HSAPI_INIT(strategyOrder_CloudStorageAndOrderStatusGetRequest);

typedef struct strategyOrder_CloudStorageAndOrderStatusGetResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageAndOrderStatusGetResponseData
	{
		
		/** [O]通道号 */
		CSTR channelId;
		/** [O]设备序列号 */
		CSTR deviceId;
		/** [int] 订单状态  0-待支付 1-交易完成 2-已关闭 (只有0可以pay或者cancel) */
		int orderStatus;
 
	} data;

} strategyOrder_CloudStorageAndOrderStatusGetResponse;

C_API strategyOrder_CloudStorageAndOrderStatusGetResponse *HSAPI_INIT(strategyOrder_CloudStorageAndOrderStatusGetResponse);

#endif
