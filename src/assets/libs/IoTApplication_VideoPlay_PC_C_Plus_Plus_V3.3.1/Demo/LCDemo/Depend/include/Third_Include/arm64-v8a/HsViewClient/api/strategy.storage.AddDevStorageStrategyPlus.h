/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_AddDevStorageStrategyPlus_H_
#define _HSVIEW_CLIENT_API_strategyStorage_AddDevStorageStrategyPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
给设备通道添加新套餐，套餐详情即为请求参数
【需要使用平台账号签名】
 */

typedef struct strategyStorage_AddDevStorageStrategyPlusRequest 
{
	HsviewRequest base;

	struct strategyStorage_AddDevStorageStrategyPlusRequestData
	{
		
		/** [O]云录像保存天数 */
		CSTR recordSave;
		/** 过期时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
		/** 开始时间，yyyyMMddTHHmmssZ格式 */
		CSTR beginTime;
		/** 通道id */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_AddDevStorageStrategyPlusRequest;

C_API strategyStorage_AddDevStorageStrategyPlusRequest *HSAPI_INIT(strategyStorage_AddDevStorageStrategyPlusRequest);

typedef struct strategyStorage_AddDevStorageStrategyPlusResponse 
{
	HsviewResponse base;

	struct strategyStorage_AddDevStorageStrategyPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyStorage_AddDevStorageStrategyPlusResponse;

C_API strategyStorage_AddDevStorageStrategyPlusResponse *HSAPI_INIT(strategyStorage_AddDevStorageStrategyPlusResponse);

#endif
