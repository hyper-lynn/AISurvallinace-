/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserDeviceStrategyListPageGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserDeviceStrategyListPageGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户所有设备云存储套餐详情

【使用平台账号签名】
 */

typedef struct strategyStorage_UserDeviceStrategyListPageGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserDeviceStrategyListPageGetRequestData
	{
		
		/** [int]条数,最大16 */
		int limit;
		/** [long]上次查询最后一个设备id，为-1表示从最后一个开始获取 */
		int64 bindId;

	} data;

} strategyStorage_UserDeviceStrategyListPageGetRequest;

C_API strategyStorage_UserDeviceStrategyListPageGetRequest *HSAPI_INIT(strategyStorage_UserDeviceStrategyListPageGetRequest);

typedef struct strategyStorage_UserDeviceStrategyListPageGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserDeviceStrategyListPageGetResponseData
	{
		
		/** define a list with struct of strategyStorage_UserDeviceStrategyListPageGetResponseData_DeviceListElement */
		DECLARE_LIST(struct strategyStorage_UserDeviceStrategyListPageGetResponseData_DeviceListElement
		{
			/** [O]on：云录像开启，off 云录像关闭 */
			CSTR recordSwitchStatus;
			/** [O]设备通道名称 */
			CSTR channelName;
			/** define a list with struct of strategyStorage_UserDeviceStrategyListPageGetResponseData_DeviceListElement_StrategiesElement */
			DECLARE_LIST(struct strategyStorage_UserDeviceStrategyListPageGetResponseData_DeviceListElement_StrategiesElement
			{
				/** 套餐id */
				CSTR strategyId;
				/** 失效时间，yyyyMMddTHHmmssZ格式 */
				CSTR endTime;
				/** 生效时间，yyyyMMddTHHmmssZ格式 */
				CSTR startTime;
				/** using：正在使用，waiting：列队状态， expired：套餐过期 */
				CSTR strategyStatus;
				/** 录像保存天数 */
				CSTR recordSaveDays;
			}) strategies;
			/** [O]设备通道号 */
			CSTR channelId;
			/** [long]绑定表自增id */
			int64 bindId;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} strategyStorage_UserDeviceStrategyListPageGetResponse;

C_API strategyStorage_UserDeviceStrategyListPageGetResponse *HSAPI_INIT(strategyStorage_UserDeviceStrategyListPageGetResponse);

#endif
