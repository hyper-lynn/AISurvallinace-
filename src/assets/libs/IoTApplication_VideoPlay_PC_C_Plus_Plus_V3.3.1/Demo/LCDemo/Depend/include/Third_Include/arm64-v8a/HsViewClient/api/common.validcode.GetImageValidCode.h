/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonValidcode_GetImageValidCode_H_
#define _HSVIEW_CLIENT_API_commonValidcode_GetImageValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取图片验证码

【使用固定密钥校验，无需签名】
 */

typedef struct commonValidcode_GetImageValidCodeRequest 
{
	HsviewRequest base;

	struct commonValidcode_GetImageValidCodeRequestData
	{
		
		/** [int]高度 */
		int height;
		/** [int]宽度 */
		int width;

	} data;

} commonValidcode_GetImageValidCodeRequest;

C_API commonValidcode_GetImageValidCodeRequest *HSAPI_INIT(commonValidcode_GetImageValidCodeRequest);

typedef struct commonValidcode_GetImageValidCodeResponse 
{
	HsviewResponse base;

	struct commonValidcode_GetImageValidCodeResponseData
	{
		
		/** 返回验证码的唯一标识 */
		CSTR codeId;
		/** 图片验证码base64编码 */
		CSTR image;
		/** [int]有效时间，单位秒（例:120S） */
		int expiredTime;
 
	} data;

} commonValidcode_GetImageValidCodeResponse;

C_API commonValidcode_GetImageValidCodeResponse *HSAPI_INIT(commonValidcode_GetImageValidCodeResponse);

#endif
