/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetImageValidCode_H_
#define _HSVIEW_CLIENT_API_GetImageValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取图片验证码

【使用固定密钥校验，无需签名】
 */

typedef struct GetImageValidCodeRequest 
{
	HsviewRequest base;

	struct GetImageValidCodeRequestData
	{
		
		/** [int]高度 */
		int height;
		/** [int]宽度 */
		int width;

	} data;

} GetImageValidCodeRequest;

C_API GetImageValidCodeRequest *HSAPI_INIT(GetImageValidCodeRequest);

typedef struct GetImageValidCodeResponse 
{
	HsviewResponse base;

	struct GetImageValidCodeResponseData
	{
		
		/** 返回验证码的唯一标识 */
		CSTR codeId;
		/** 图片验证码base64编码 */
		CSTR image;
		/** [int]有效时间，单位秒（例:120S） */
		int expiredTime;
 
	} data;

} GetImageValidCodeResponse;

C_API GetImageValidCodeResponse *HSAPI_INIT(GetImageValidCodeResponse);

#endif
