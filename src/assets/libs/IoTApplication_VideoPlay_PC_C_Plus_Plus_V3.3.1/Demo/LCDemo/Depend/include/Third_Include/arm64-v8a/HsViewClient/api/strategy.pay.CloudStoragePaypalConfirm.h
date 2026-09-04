/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPay_CloudStoragePaypalConfirm_H_
#define _HSVIEW_CLIENT_API_strategyPay_CloudStoragePaypalConfirm_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
paypal确认支付

备注：此时确认支付完成，前端直接请求  pcs/v1/strategy.order.getPayStatus接口 ，查询支付状态
 */

typedef struct strategyPay_CloudStoragePaypalConfirmRequest 
{
	HsviewRequest base;

	struct strategyPay_CloudStoragePaypalConfirmRequestData
	{
		
		/** 交易号,paypal支付return_url会附带的值 */
		CSTR payerId;
		/** 订单ID */
		CSTR orderNo;
		/** 交易唯一token，paypal支付return_url会附带的值 */
		CSTR token;
		/** 透传变量 paypal支付return_url会附带的值 */
		CSTR custom;

	} data;

} strategyPay_CloudStoragePaypalConfirmRequest;

C_API strategyPay_CloudStoragePaypalConfirmRequest *HSAPI_INIT(strategyPay_CloudStoragePaypalConfirmRequest);

typedef struct strategyPay_CloudStoragePaypalConfirmResponse 
{
	HsviewResponse base;

	struct strategyPay_CloudStoragePaypalConfirmResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyPay_CloudStoragePaypalConfirmResponse;

C_API strategyPay_CloudStoragePaypalConfirmResponse *HSAPI_INIT(strategyPay_CloudStoragePaypalConfirmResponse);

#endif
