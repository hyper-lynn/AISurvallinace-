/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoDetailGet_H_
#define _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoDetailGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取时光相册套餐详情,有在使用套餐才有返回

【使用平台账号签名】
 */

typedef struct strategyTimePhoto_TimePhotoDetailGetRequest 
{
	HsviewRequest base;

	struct strategyTimePhoto_TimePhotoDetailGetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyTimePhoto_TimePhotoDetailGetRequest;

C_API strategyTimePhoto_TimePhotoDetailGetRequest *HSAPI_INIT(strategyTimePhoto_TimePhotoDetailGetRequest);

typedef struct strategyTimePhoto_TimePhotoDetailGetResponse 
{
	HsviewResponse base;

	struct strategyTimePhoto_TimePhotoDetailGetResponseData
	{
		
		/** [O]失效时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
		/** [O]on：时光相册开启，off 时光相册关闭 */
		CSTR switchStatus;
 
	} data;

} strategyTimePhoto_TimePhotoDetailGetResponse;

C_API strategyTimePhoto_TimePhotoDetailGetResponse *HSAPI_INIT(strategyTimePhoto_TimePhotoDetailGetResponse);

#endif
