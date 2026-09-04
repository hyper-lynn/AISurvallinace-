/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoFreeTry_H_
#define _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoFreeTry_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开始试用免费


【使用平台账号签名】
 */

typedef struct strategyTimePhoto_TimePhotoFreeTryRequest 
{
	HsviewRequest base;

	struct strategyTimePhoto_TimePhotoFreeTryRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyTimePhoto_TimePhotoFreeTryRequest;

C_API strategyTimePhoto_TimePhotoFreeTryRequest *HSAPI_INIT(strategyTimePhoto_TimePhotoFreeTryRequest);

typedef struct strategyTimePhoto_TimePhotoFreeTryResponse 
{
	HsviewResponse base;

	struct strategyTimePhoto_TimePhotoFreeTryResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyTimePhoto_TimePhotoFreeTryResponse;

C_API strategyTimePhoto_TimePhotoFreeTryResponse *HSAPI_INIT(strategyTimePhoto_TimePhotoFreeTryResponse);

#endif
