/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUploadToken_H_
#define _HSVIEW_CLIENT_API_GetUploadToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取文件上传的uploadToken和上传地址。
当mode为1时，文件上传的URL形如：http://www.lechange.cn/uploadCustomizedFile/nj2k3hp90h2iojdh9y82he1iklafjsef
【需要使用平台账号签名】
 */

typedef struct GetUploadTokenRequest 
{
	HsviewRequest base;

	struct GetUploadTokenRequestData
	{
		
		/** [int][O]上传类型 0-平台上传服务，1-show环境上传服务（缺省时默认回复平台上传服务地址） */
		int mode;

	} data;

} GetUploadTokenRequest;

C_API GetUploadTokenRequest *HSAPI_INIT(GetUploadTokenRequest);

typedef struct GetUploadTokenResponse 
{
	HsviewResponse base;

	struct GetUploadTokenResponseData
	{
		
		/** 文件上传token，32位随机字符串，例如：nj2k3hp90h2iojdh9y82he1iklafjsef */
		CSTR uploadToken;
		/** 文件上传URL，例如：http://www.lechange.cn/uploadfile/nj2k3hp90h2iojdh9y82he1iklafjsef */
		CSTR uploadUrl;
 
	} data;

} GetUploadTokenResponse;

C_API GetUploadTokenResponse *HSAPI_INIT(GetUploadTokenResponse);

#endif
