/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderCancel_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderCancel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
海外云存储取消订单

【使用平台账号签名】
 */

typedef struct strategyOrder_CloudStorageOrderCancelRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageOrderCancelRequestData
	{
		
		/** 订单id */
		CSTR orderNo;

	} data;

} strategyOrder_CloudStorageOrderCancelRequest;

C_API strategyOrder_CloudStorageOrderCancelRequest *HSAPI_INIT(strategyOrder_CloudStorageOrderCancelRequest);

typedef struct strategyOrder_CloudStorageOrderCancelResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageOrderCancelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyOrder_CloudStorageOrderCancelResponse;

C_API strategyOrder_CloudStorageOrderCancelResponse *HSAPI_INIT(strategyOrder_CloudStorageOrderCancelResponse);

#endif
