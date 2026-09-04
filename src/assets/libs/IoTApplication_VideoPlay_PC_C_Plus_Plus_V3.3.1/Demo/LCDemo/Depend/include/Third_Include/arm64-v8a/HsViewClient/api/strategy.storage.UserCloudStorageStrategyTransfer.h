/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageStrategyTransfer_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageStrategyTransfer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
未启用状态的库存转移给好友

【使用平台账号签名】
 */

typedef struct strategyStorage_UserCloudStorageStrategyTransferRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserCloudStorageStrategyTransferRequestData
	{
		
		/** 库存记录id */
		CSTR repositoryId;
		/** 被转移用户id */
		CSTR acceptUserId;

	} data;

} strategyStorage_UserCloudStorageStrategyTransferRequest;

C_API strategyStorage_UserCloudStorageStrategyTransferRequest *HSAPI_INIT(strategyStorage_UserCloudStorageStrategyTransferRequest);

typedef struct strategyStorage_UserCloudStorageStrategyTransferResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserCloudStorageStrategyTransferResponseData
	{
		
		/** success: 操作成功， repositoryIdInvalid：操作失败，不满足操作条件，套餐已经不在用户库存中， notFriend：操作失败，非好友关系 */
		CSTR result;
 
	} data;

} strategyStorage_UserCloudStorageStrategyTransferResponse;

C_API strategyStorage_UserCloudStorageStrategyTransferResponse *HSAPI_INIT(strategyStorage_UserCloudStorageStrategyTransferResponse);

#endif
