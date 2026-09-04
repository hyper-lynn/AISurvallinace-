/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageRepositoryBuyList_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageRepositoryBuyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取购买成功可用的套餐数量


【使用平台账号签名】
 */

typedef struct strategyStorage_UserCloudStorageRepositoryBuyListRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserCloudStorageRepositoryBuyListRequestData
	{
		
		/** 操作id(订单id) */
		CSTR operateId;

	} data;

} strategyStorage_UserCloudStorageRepositoryBuyListRequest;

C_API strategyStorage_UserCloudStorageRepositoryBuyListRequest *HSAPI_INIT(strategyStorage_UserCloudStorageRepositoryBuyListRequest);

typedef struct strategyStorage_UserCloudStorageRepositoryBuyListResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserCloudStorageRepositoryBuyListResponseData
	{
		
		/** define a list with struct of strategyStorage_UserCloudStorageRepositoryBuyListResponseData_UserRepositoryStrategyListElement */
		DECLARE_LIST(struct strategyStorage_UserCloudStorageRepositoryBuyListResponseData_UserRepositoryStrategyListElement
		{
			/** 服务时长(秒) */
			CSTR serviceTime;
			/** 表记录id */
			CSTR repositoryId;
			/** 录像保存天数 */
			CSTR recordSaveDays;
		}) userRepositoryStrategyList;
 
	} data;

} strategyStorage_UserCloudStorageRepositoryBuyListResponse;

C_API strategyStorage_UserCloudStorageRepositoryBuyListResponse *HSAPI_INIT(strategyStorage_UserCloudStorageRepositoryBuyListResponse);

#endif
