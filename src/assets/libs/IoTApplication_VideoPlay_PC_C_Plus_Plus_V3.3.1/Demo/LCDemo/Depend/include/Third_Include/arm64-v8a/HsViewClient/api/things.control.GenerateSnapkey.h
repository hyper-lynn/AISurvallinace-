/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GenerateSnapkey_H_
#define _HSVIEW_CLIENT_API_thingsControl_GenerateSnapkey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
生成临时秘钥
错误码：13701：临时秘钥生成次数超限制
【需要使用平台账号签名】
 */

typedef struct thingsControl_GenerateSnapkeyRequest 
{
	HsviewRequest base;

	struct thingsControl_GenerateSnapkeyRequestData
	{
		
		/** [int]临时秘钥有效次数，-1：不限次数， */
		int number;
		/** [O]要验证的帐号类型, phone、email，开放平台非必填 */
		CSTR type;
		/** 秘钥名称 */
		CSTR name;
		/** define a list with struct of thingsControl_GenerateSnapkeyRequestData_EffectPeriodElement */
		DECLARE_LIST(struct thingsControl_GenerateSnapkeyRequestData_EffectPeriodElement
		{
			/** T112308 结束时间 时间格式为THHMMSS */
			CSTR endTime;
			/** T112208 开始时间 时间格式为THHMMSS */
			CSTR beginTime;
			/** Monday */
			CSTR period;
		}) effectPeriod;
		/** [int]有效时长，天数（最小1，最大90） */
		int effectTime;
		/** 门锁序列号 */
		CSTR deviceId;
		/** [O]验证码token，开放平台非必填 */
		CSTR accessToken;
		/** [O]要验证的帐号, 手机号码、邮箱，开放平台非必填 */
		CSTR account;

	} data;

} thingsControl_GenerateSnapkeyRequest;

C_API thingsControl_GenerateSnapkeyRequest *HSAPI_INIT(thingsControl_GenerateSnapkeyRequest);

typedef struct thingsControl_GenerateSnapkeyResponse 
{
	HsviewResponse base;

	struct thingsControl_GenerateSnapkeyResponseData
	{
		
		/** 秘钥名称 */
		CSTR name;
		/** 秘钥唯一标示符 */
		CSTR keyId;
		/** 临时秘钥生成的设备本地时间，格式20170418T162832 */
		CSTR localTime;
		/** 临时秘钥生成的UTC时间，格式20170418T162832Z */
		CSTR utcTime;
		/** 临时秘钥 */
		CSTR key;
 
	} data;

} thingsControl_GenerateSnapkeyResponse;

C_API thingsControl_GenerateSnapkeyResponse *HSAPI_INIT(thingsControl_GenerateSnapkeyResponse);

#endif
