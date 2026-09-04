/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageRepositoryList_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageRepositoryList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取我的库存未启用和已启用的套餐列表

userRepositoryStrategyList表示用户库存中未启用的套餐列表。

userDeviceStrategyList表示用户已启用在其绑定的设备上的正在使用或者列队的套餐列表。

userRepositoryStrategyList未启用和userDeviceStrategyList已启用排列顺序按照购买的先后排列，先买的套餐在下方，后买的在上方


【使用平台账号签名】
 */

typedef struct strategyStorage_UserCloudStorageRepositoryListRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserCloudStorageRepositoryListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyStorage_UserCloudStorageRepositoryListRequest;

C_API strategyStorage_UserCloudStorageRepositoryListRequest *HSAPI_INIT(strategyStorage_UserCloudStorageRepositoryListRequest);

typedef struct strategyStorage_UserCloudStorageRepositoryListResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserCloudStorageRepositoryListResponseData
	{
		
		/** define a list with struct of strategyStorage_UserCloudStorageRepositoryListResponseData_UserDeviceStrategyListElement */
		DECLARE_LIST(struct strategyStorage_UserCloudStorageRepositoryListResponseData_UserDeviceStrategyListElement
		{
			/** [O]true/false，该套餐如果是自动续费套餐的，即为true */
			CSTR autoRenewal;
			/** 设备通道名称 */
			CSTR channelName;
			/** 设备通道号 */
			CSTR channelId;
			/** [int][O]套餐剩余天数 */
			int remainDays;
			/** 失效时间，yyyyMMddTHHmmssZ格式 */
			CSTR endTime;
			/** 生效时间，yyyyMMddTHHmmssZ格式 */
			CSTR startTime;
			/** 设备序列号 */
			CSTR deviceId;
			/** 录像保存天数 */
			CSTR recordSaveDays;
		}) userDeviceStrategyList;
		/** define a list with struct of strategyStorage_UserCloudStorageRepositoryListResponseData_UserRepositoryStrategyListElement */
		DECLARE_LIST(struct strategyStorage_UserCloudStorageRepositoryListResponseData_UserRepositoryStrategyListElement
		{
			/** 服务时长(秒) */
			CSTR serviceTime;
			/** 表记录id */
			CSTR repositoryId;
			/** 录像保存天数 */
			CSTR recordSaveDays;
		}) userRepositoryStrategyList;
 
	} data;

} strategyStorage_UserCloudStorageRepositoryListResponse;

C_API strategyStorage_UserCloudStorageRepositoryListResponse *HSAPI_INIT(strategyStorage_UserCloudStorageRepositoryListResponse);

#endif
