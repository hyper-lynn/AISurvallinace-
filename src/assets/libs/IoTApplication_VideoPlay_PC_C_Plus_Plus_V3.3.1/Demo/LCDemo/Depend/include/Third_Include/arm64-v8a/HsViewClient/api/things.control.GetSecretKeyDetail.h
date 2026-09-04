/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetSecretKeyDetail_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetSecretKeyDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取钥匙详情
【需要使用平台账号签名】
 */

typedef struct thingsControl_GetSecretKeyDetailRequest 
{
	HsviewRequest base;

	struct thingsControl_GetSecretKeyDetailRequestData
	{
		
		/** 密码、卡、指纹及临时秘钥唯一标示符 */
		CSTR keyId;
		/** 钥匙类型，password:密码；card:卡；fingerPrint：指纹 */
		CSTR type;
		/** 门锁序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetSecretKeyDetailRequest;

C_API thingsControl_GetSecretKeyDetailRequest *HSAPI_INIT(thingsControl_GetSecretKeyDetailRequest);

typedef struct thingsControl_GetSecretKeyDetailResponse 
{
	HsviewResponse base;

	struct thingsControl_GetSecretKeyDetailResponseData
	{
		
		/** [bool]是否为管理员钥匙，true:是；false:否 */
		BOOL bManager;
		/** 钥匙名称 */
		CSTR name;
		/** [O]地址，当bHijackAlarm为true时，表示用户设置地址 */
		CSTR location;
		/** [bool]true */
		BOOL bHijackAlarm;
		/** [O]当bHijackAlarm为true时，表示用户设置的劫持报警手机号 */
		CSTR phone;
		/** [int]钥匙有效天数 */
		int effectTime;
		/** define a list with struct of thingsControl_GetSecretKeyDetailResponseData_EffectPeriodElement */
		DECLARE_LIST(struct thingsControl_GetSecretKeyDetailResponseData_EffectPeriodElement
		{
			/** T122212 */
			CSTR endTime;
			/** T112211 */
			CSTR beginTime;
			/** Monday */
			CSTR period;
		}) effectPeriod;
 
	} data;

} thingsControl_GetSecretKeyDetailResponse;

C_API thingsControl_GetSecretKeyDetailResponse *HSAPI_INIT(thingsControl_GetSecretKeyDetailResponse);

#endif
