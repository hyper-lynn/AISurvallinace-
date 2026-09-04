/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserRepositoryStrategyListGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserRepositoryStrategyListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取我的库存未启用的套餐列表

userRepositoryStrategyList表示用户库存中未启用的套餐列表。


【使用平台账号签名】
 */

typedef struct strategyStorage_UserRepositoryStrategyListGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserRepositoryStrategyListGetRequestData
	{
		
		/** [long]上次查询最后一个id 为-1表示从最开始获取 */
		int64 repositoryId;
		/** [int]条数,最大16 */
		int limit;

	} data;

} strategyStorage_UserRepositoryStrategyListGetRequest;

C_API strategyStorage_UserRepositoryStrategyListGetRequest *HSAPI_INIT(strategyStorage_UserRepositoryStrategyListGetRequest);

typedef struct strategyStorage_UserRepositoryStrategyListGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserRepositoryStrategyListGetResponseData
	{
		
		/** define a list with struct of strategyStorage_UserRepositoryStrategyListGetResponseData_UserRepositoryStrategyListElement */
		DECLARE_LIST(struct strategyStorage_UserRepositoryStrategyListGetResponseData_UserRepositoryStrategyListElement
		{
			/** 套餐唯一id */
			CSTR operateUniqueId;
			/** 表记录id */
			CSTR repositoryId;
			/** 套餐id */
			CSTR strategyId;
			/** 服务时长(秒) */
			CSTR serviceTime;
			/** 录像保存天数 */
			CSTR recordSaveDays;
		}) userRepositoryStrategyList;
 
	} data;

} strategyStorage_UserRepositoryStrategyListGetResponse;

C_API strategyStorage_UserRepositoryStrategyListGetResponse *HSAPI_INIT(strategyStorage_UserRepositoryStrategyListGetResponse);

#endif
