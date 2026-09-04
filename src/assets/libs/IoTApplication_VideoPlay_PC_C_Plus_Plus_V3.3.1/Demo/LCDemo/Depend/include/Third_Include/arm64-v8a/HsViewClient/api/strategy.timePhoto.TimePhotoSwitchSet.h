/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoSwitchSet_H_
#define _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoSwitchSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启暂停套餐对应的开关

【使用平台账号签名】
 */

typedef struct strategyTimePhoto_TimePhotoSwitchSetRequest 
{
	HsviewRequest base;

	struct strategyTimePhoto_TimePhotoSwitchSetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** on：开关开启，off 开关关闭 */
		CSTR switchStatus;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyTimePhoto_TimePhotoSwitchSetRequest;

C_API strategyTimePhoto_TimePhotoSwitchSetRequest *HSAPI_INIT(strategyTimePhoto_TimePhotoSwitchSetRequest);

typedef struct strategyTimePhoto_TimePhotoSwitchSetResponse 
{
	HsviewResponse base;

	struct strategyTimePhoto_TimePhotoSwitchSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyTimePhoto_TimePhotoSwitchSetResponse;

C_API strategyTimePhoto_TimePhotoSwitchSetResponse *HSAPI_INIT(strategyTimePhoto_TimePhotoSwitchSetResponse);

#endif
