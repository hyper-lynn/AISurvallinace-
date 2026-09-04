/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyValidCodeForBabyCms_H_
#define _HSVIEW_CLIENT_API_VerifyValidCodeForBabyCms_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验手机号与对应的验证码。【注意：此接口提供给乐橙宝宝的后台CMS管理系统使用，与APP客户端无关】
【无需签名认证】
 */

typedef struct VerifyValidCodeForBabyCmsRequest 
{
	HsviewRequest base;

	struct VerifyValidCodeForBabyCmsRequestData
	{
		
		/** 手机号，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNumber;
		/** 验证码，如123456 */
		CSTR validCode;

	} data;

} VerifyValidCodeForBabyCmsRequest;

C_API VerifyValidCodeForBabyCmsRequest *HSAPI_INIT(VerifyValidCodeForBabyCmsRequest);

typedef struct VerifyValidCodeForBabyCmsResponse 
{
	HsviewResponse base;

	struct VerifyValidCodeForBabyCmsResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
 
	} data;

} VerifyValidCodeForBabyCmsResponse;

C_API VerifyValidCodeForBabyCmsResponse *HSAPI_INIT(VerifyValidCodeForBabyCmsResponse);

#endif
