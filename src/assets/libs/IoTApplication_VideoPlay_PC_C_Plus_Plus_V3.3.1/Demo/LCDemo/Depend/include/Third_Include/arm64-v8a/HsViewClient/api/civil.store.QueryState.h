/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryState_H_
#define _HSVIEW_CLIENT_API_QueryState_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
订单状态
  success：成功。
  closed: 在指定时间段内未支付时关闭的交易；在交易完成全额退款成功时关闭的交易。
  finished：交易成功且结束，即不可再做任何操作。
  wait_pay：等待支付。

错误码：
1、8001 : 订单不存在
 */

typedef struct QueryStateRequest 
{
	HsviewRequest base;

	struct QueryStateRequestData
	{
		
		/** 订单ID，0123456789-123456 */
		CSTR orderId;

	} data;

} QueryStateRequest;

C_API QueryStateRequest *HSAPI_INIT(QueryStateRequest);

typedef struct QueryStateResponse 
{
	HsviewResponse base;

	struct QueryStateResponseData
	{
		
		/** 订单状态，success */
		CSTR state;
 
	} data;

} QueryStateResponse;

C_API QueryStateResponse *HSAPI_INIT(QueryStateResponse);

#endif
