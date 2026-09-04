/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetSnapkeyList_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetSnapkeyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取零时秘钥列表
【需要使用平台账号签名】
 */

typedef struct thingsControl_GetSnapkeyListRequest 
{
	HsviewRequest base;

	struct thingsControl_GetSnapkeyListRequestData
	{
		
		/** 门锁序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetSnapkeyListRequest;

C_API thingsControl_GetSnapkeyListRequest *HSAPI_INIT(thingsControl_GetSnapkeyListRequest);

typedef struct thingsControl_GetSnapkeyListResponse 
{
	HsviewResponse base;

	struct thingsControl_GetSnapkeyListResponseData
	{
		
		/** define a list with struct of thingsControl_GetSnapkeyListResponseData_SnapkeysElement */
		DECLARE_LIST(struct thingsControl_GetSnapkeyListResponseData_SnapkeysElement
		{
			/** [O]临时秘钥失效或者使用utc时间，格式20170418T162832Z */
			CSTR utcTime;
			/** 临时秘钥 */
			CSTR snapKey;
			/** 秘钥名称 */
			CSTR name;
			/** 创建的本地时间，20170418T162832格式 */
			CSTR createLocalTime;
			/** 临时秘钥唯一标示符 */
			CSTR keyId;
			/** 创建Utc时间，20170418T162832Z格式 */
			CSTR createUtcTime;
			/** [O]临时秘钥失效或者使用本地时间，格式20170418T162832 */
			CSTR localTime;
			/** 秘钥状态，notUsed:未使用；bUsed:已使用；failed:已失效 */
			CSTR status;
		}) snapkeys;
 
	} data;

} thingsControl_GetSnapkeyListResponse;

C_API thingsControl_GetSnapkeyListResponse *HSAPI_INIT(thingsControl_GetSnapkeyListResponse);

#endif
