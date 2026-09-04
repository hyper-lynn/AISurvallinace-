/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyWindow_UserWindowStrategyGet_H_
#define _HSVIEW_CLIENT_API_strategyWindow_UserWindowStrategyGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询已经购买不断流的窗口
1:表示第一个窗口，2:表示第二个，以此类推
【使用平台账号签名】
 */

typedef struct strategyWindow_UserWindowStrategyGetRequest 
{
	HsviewRequest base;

	struct strategyWindow_UserWindowStrategyGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyWindow_UserWindowStrategyGetRequest;

C_API strategyWindow_UserWindowStrategyGetRequest *HSAPI_INIT(strategyWindow_UserWindowStrategyGetRequest);

typedef struct strategyWindow_UserWindowStrategyGetResponse 
{
	HsviewResponse base;

	struct strategyWindow_UserWindowStrategyGetResponseData
	{
		
		/** define a list with struct of strategyWindow_UserWindowStrategyGetResponseData_WindowsInfoElement */
		DECLARE_LIST(struct strategyWindow_UserWindowStrategyGetResponseData_WindowsInfoElement
		{
			/** 套餐结束时间,形如yyyyMMddTHHmmssZ时间格式 */
			CSTR endTime;
			/** 套餐开始时间,形如yyyyMMddTHHmmssZ时间格式 */
			CSTR startTime;
			/** 窗口号 */
			CSTR windowNum;
		}) windowsInfo;
 
	} data;

} strategyWindow_UserWindowStrategyGetResponse;

C_API strategyWindow_UserWindowStrategyGetResponse *HSAPI_INIT(strategyWindow_UserWindowStrategyGetResponse);

#endif
