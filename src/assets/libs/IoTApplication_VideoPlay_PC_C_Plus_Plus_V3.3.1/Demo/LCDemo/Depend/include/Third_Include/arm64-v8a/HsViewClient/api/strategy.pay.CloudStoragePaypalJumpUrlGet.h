/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPay_CloudStoragePaypalJumpUrlGet_H_
#define _HSVIEW_CLIENT_API_strategyPay_CloudStoragePaypalJumpUrlGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取paypal跳转地址
 */

typedef struct strategyPay_CloudStoragePaypalJumpUrlGetRequest 
{
	HsviewRequest base;

	struct strategyPay_CloudStoragePaypalJumpUrlGetRequestData
	{
		
		/** 订单id */
		CSTR orderNo;

	} data;

} strategyPay_CloudStoragePaypalJumpUrlGetRequest;

C_API strategyPay_CloudStoragePaypalJumpUrlGetRequest *HSAPI_INIT(strategyPay_CloudStoragePaypalJumpUrlGetRequest);

typedef struct strategyPay_CloudStoragePaypalJumpUrlGetResponse 
{
	HsviewResponse base;

	struct strategyPay_CloudStoragePaypalJumpUrlGetResponseData
	{
		
		/** www.XXXX.com?XXXX paypal跳转地址 */
		CSTR paypalJumpUrl;
 
	} data;

} strategyPay_CloudStoragePaypalJumpUrlGetResponse;

C_API strategyPay_CloudStoragePaypalJumpUrlGetResponse *HSAPI_INIT(strategyPay_CloudStoragePaypalJumpUrlGetResponse);

#endif
