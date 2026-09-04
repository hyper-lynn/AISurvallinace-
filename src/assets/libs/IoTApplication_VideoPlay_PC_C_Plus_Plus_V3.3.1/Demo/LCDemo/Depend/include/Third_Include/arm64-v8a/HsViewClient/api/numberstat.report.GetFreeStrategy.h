/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetFreeStrategy_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetFreeStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
领取试用套餐
错误码：
13503用户已领取试用套餐，不可重复领取
【使用平台账号签名】
 */

typedef struct numberstatReport_GetFreeStrategyRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetFreeStrategyRequestData
	{
		
		/**  [long]报表id */
		CSTR reportId;

	} data;

} numberstatReport_GetFreeStrategyRequest;

C_API numberstatReport_GetFreeStrategyRequest *HSAPI_INIT(numberstatReport_GetFreeStrategyRequest);

typedef struct numberstatReport_GetFreeStrategyResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetFreeStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_GetFreeStrategyResponse;

C_API numberstatReport_GetFreeStrategyResponse *HSAPI_INIT(numberstatReport_GetFreeStrategyResponse);

#endif
