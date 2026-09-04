/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CheckBindOrNotByThird_H_
#define _HSVIEW_CLIENT_API_CheckBindOrNotByThird_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
验证手机号或邮箱是否被第三方账号绑定。

若已经被绑定，那么isBind和isExists都为true。
若没有被绑定，isBind为false。

【无需签名认证】
 */

typedef struct CheckBindOrNotByThirdRequest 
{
	HsviewRequest base;

	struct CheckBindOrNotByThirdRequestData
	{
		
		/** 手机号或邮箱，如13912345678(或123456@gmail.com) */
		CSTR phoneNumber;
		/** 第三方账号类型，如“taobao”,“weixin” */
		CSTR type;

	} data;

} CheckBindOrNotByThirdRequest;

C_API CheckBindOrNotByThirdRequest *HSAPI_INIT(CheckBindOrNotByThirdRequest);

typedef struct CheckBindOrNotByThirdResponse 
{
	HsviewResponse base;

	struct CheckBindOrNotByThirdResponseData
	{
		
		/** [bool]是否被绑定到某个第三方账号, true表示绑定了 */
		BOOL isBind;
		/** [bool]手机或邮箱账号是否存在, true表示存在 */
		BOOL isExists;
 
	} data;

} CheckBindOrNotByThirdResponse;

C_API CheckBindOrNotByThirdResponse *HSAPI_INIT(CheckBindOrNotByThirdResponse);

#endif
