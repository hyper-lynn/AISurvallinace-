/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPay_CloudStoragePayStatusGet_H_
#define _HSVIEW_CLIENT_API_strategyPay_CloudStoragePayStatusGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
海外云存储查询支付状态接口
 */

typedef struct strategyPay_CloudStoragePayStatusGetRequest 
{
	HsviewRequest base;

	struct strategyPay_CloudStoragePayStatusGetRequestData
	{
		
		/** 订单id */
		CSTR orderNo;

	} data;

} strategyPay_CloudStoragePayStatusGetRequest;

C_API strategyPay_CloudStoragePayStatusGetRequest *HSAPI_INIT(strategyPay_CloudStoragePayStatusGetRequest);

typedef struct strategyPay_CloudStoragePayStatusGetResponse 
{
	HsviewResponse base;

	struct strategyPay_CloudStoragePayStatusGetResponseData
	{
		
		/** [int] 支付状态  0-支付失败 1-支付完成 */
		int payStatus;
 
	} data;

} strategyPay_CloudStoragePayStatusGetResponse;

C_API strategyPay_CloudStoragePayStatusGetResponse *HSAPI_INIT(strategyPay_CloudStoragePayStatusGetResponse);

#endif
