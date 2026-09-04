/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudFile_GetFileToken_H_
#define _HSVIEW_CLIENT_API_cloudFile_GetFileToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用于上传文件的服务信息，同一用户1分钟内不能调用获取上传文件token的接口超过50次

businessType为公有业务类型的将文件存在公有bucket：用户头像等。
businessType为私有业务类型的将文件存在私有bucket：家庭成员(时光相册)、自定义铃声等。
【用户平台鉴权】
 */

typedef struct cloudFile_GetFileTokenRequest 
{
	HsviewRequest base;

	struct cloudFile_GetFileTokenRequestData
	{
		
		/** [int]文件上传数 */
		int number;
		/** 文件存储的业务类型，家庭成员：faceMember,自定义铃声:customRingtone，陌生人提醒家人图片:strangerRemind */
		CSTR businessType;

	} data;

} cloudFile_GetFileTokenRequest;

C_API cloudFile_GetFileTokenRequest *HSAPI_INIT(cloudFile_GetFileTokenRequest);

typedef struct cloudFile_GetFileTokenResponse 
{
	HsviewResponse base;

	struct cloudFile_GetFileTokenResponseData
	{
		
		/** 文件服务入口地址 */
		CSTR addr;
		/** 平台分配的用来上传文件的Token,由平台分配,保证唯一 */
		CSTR token;
		/** TLS端口 */
		CSTR tlsPort;
 
	} data;

} cloudFile_GetFileTokenResponse;

C_API cloudFile_GetFileTokenResponse *HSAPI_INIT(cloudFile_GetFileTokenResponse);

#endif
