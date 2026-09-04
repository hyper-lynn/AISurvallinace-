/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_CloudStorageFreeStrategyDetail_H_
#define _HSVIEW_CLIENT_API_strategyStorage_CloudStorageFreeStrategyDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取设备未开通过的相应的免费套餐信息

若设备已经开通过云存储、不存在免费云存储、已开通免费云存储并过期，那么返回的字段都为空。


【使用平台账号签名】
 */

typedef struct strategyStorage_CloudStorageFreeStrategyDetailRequest 
{
	HsviewRequest base;

	struct strategyStorage_CloudStorageFreeStrategyDetailRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_CloudStorageFreeStrategyDetailRequest;

C_API strategyStorage_CloudStorageFreeStrategyDetailRequest *HSAPI_INIT(strategyStorage_CloudStorageFreeStrategyDetailRequest);

typedef struct strategyStorage_CloudStorageFreeStrategyDetailResponse 
{
	HsviewResponse base;

	struct strategyStorage_CloudStorageFreeStrategyDetailResponseData
	{
		
		/** [O]码流类型：main：主码流extra1：辅码流 */
		CSTR streamType;
		/** [O]服务时长(秒) */
		CSTR seviceTime;
		/** [O]录像保存天数 */
		CSTR recordSaveDays;
 
	} data;

} strategyStorage_CloudStorageFreeStrategyDetailResponse;

C_API strategyStorage_CloudStorageFreeStrategyDetailResponse *HSAPI_INIT(strategyStorage_CloudStorageFreeStrategyDetailResponse);

#endif
