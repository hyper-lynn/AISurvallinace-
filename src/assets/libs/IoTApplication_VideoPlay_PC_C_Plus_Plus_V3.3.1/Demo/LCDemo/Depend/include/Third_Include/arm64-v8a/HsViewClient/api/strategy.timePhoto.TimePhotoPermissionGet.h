/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoPermissionGet_H_
#define _HSVIEW_CLIENT_API_strategyTimePhoto_TimePhotoPermissionGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
是否有权限试用时光相册功能,有权时同时具备失效时间


【使用平台账号签名】
 */

typedef struct strategyTimePhoto_TimePhotoPermissionGetRequest 
{
	HsviewRequest base;

	struct strategyTimePhoto_TimePhotoPermissionGetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyTimePhoto_TimePhotoPermissionGetRequest;

C_API strategyTimePhoto_TimePhotoPermissionGetRequest *HSAPI_INIT(strategyTimePhoto_TimePhotoPermissionGetRequest);

typedef struct strategyTimePhoto_TimePhotoPermissionGetResponse 
{
	HsviewResponse base;

	struct strategyTimePhoto_TimePhotoPermissionGetResponseData
	{
		
		/** true:具有资格,false:无资格 */
		CSTR result;
		/** [O]失效时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
 
	} data;

} strategyTimePhoto_TimePhotoPermissionGetResponse;

C_API strategyTimePhoto_TimePhotoPermissionGetResponse *HSAPI_INIT(strategyTimePhoto_TimePhotoPermissionGetResponse);

#endif
