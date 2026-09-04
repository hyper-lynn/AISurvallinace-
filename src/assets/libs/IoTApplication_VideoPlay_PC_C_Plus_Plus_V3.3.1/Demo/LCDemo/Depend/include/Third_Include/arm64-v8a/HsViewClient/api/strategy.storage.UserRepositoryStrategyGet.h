/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserRepositoryStrategyGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserRepositoryStrategyGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取我的库存未启用的套餐


【使用平台账号签名】
 */

typedef struct strategyStorage_UserRepositoryStrategyGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserRepositoryStrategyGetRequestData
	{
		
		/** [long]库存套餐id */
		int64 repositoryId;

	} data;

} strategyStorage_UserRepositoryStrategyGetRequest;

C_API strategyStorage_UserRepositoryStrategyGetRequest *HSAPI_INIT(strategyStorage_UserRepositoryStrategyGetRequest);

typedef struct strategyStorage_UserRepositoryStrategyGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserRepositoryStrategyGetResponseData
	{
		
		/** 套餐id */
		CSTR strategyId;
		/** 套餐唯一id */
		CSTR operateUniqueId;
		/** 服务时长(秒) */
		CSTR serviceTime;
		/** 录像保存天数 */
		CSTR recordSaveDays;
 
	} data;

} strategyStorage_UserRepositoryStrategyGetResponse;

C_API strategyStorage_UserRepositoryStrategyGetResponse *HSAPI_INIT(strategyStorage_UserRepositoryStrategyGetResponse);

#endif
