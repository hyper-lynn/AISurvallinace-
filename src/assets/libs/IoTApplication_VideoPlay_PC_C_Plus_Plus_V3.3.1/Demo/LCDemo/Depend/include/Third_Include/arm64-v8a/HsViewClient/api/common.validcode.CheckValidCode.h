/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonValidcode_CheckValidCode_H_
#define _HSVIEW_CLIENT_API_commonValidcode_CheckValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
验证验证码接口

usage的枚举值如下
ChangeAccount：账号变更（绑定手机号或邮箱；解绑手机号或邮箱；更换手机号或邮箱 etc.）
GenerateSnapkey: k5门锁生成临时秘钥
CloudStorage：云存储密码修改
ResetCustomPassword：重置设备自定义秘钥
ResetDevicePassword：重置设备密码
ObtainApSnapKey：获取配件临时秘钥
CheckTwoStepVerify：二次认证（lorex使用）
【需要使用平台账号签名】
 */

typedef struct commonValidcode_CheckValidCodeRequest 
{
	HsviewRequest base;

	struct commonValidcode_CheckValidCodeRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 类型, phone、email */
		CSTR type;
		/** 用途，取值详见下面说明 */
		CSTR usage;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} commonValidcode_CheckValidCodeRequest;

C_API commonValidcode_CheckValidCodeRequest *HSAPI_INIT(commonValidcode_CheckValidCodeRequest);

typedef struct commonValidcode_CheckValidCodeResponse 
{
	HsviewResponse base;

	struct commonValidcode_CheckValidCodeResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
		/** [O]验证码token */
		CSTR accessToken;
 
	} data;

} commonValidcode_CheckValidCodeResponse;

C_API commonValidcode_CheckValidCodeResponse *HSAPI_INIT(commonValidcode_CheckValidCodeResponse);

#endif
