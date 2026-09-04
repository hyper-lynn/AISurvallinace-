/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_DeveloperAppUserRegister_H_
#define _HSVIEW_CLIENT_API_userAccount_DeveloperAppUserRegister_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开发者应用下的用户注册。
* 只提供给开放平台调用
【需开放平台签名认证】
 */

typedef struct userAccount_DeveloperAppUserRegisterRequest 
{
	HsviewRequest base;

	struct userAccount_DeveloperAppUserRegisterRequestData
	{
		
		/** 用户昵称 */
		CSTR nickname;
		/** 帐号类型, phone、email、username */
		CSTR type;
		/**  用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;
		/** 帐号, 手机号码、邮箱、用户名 */
		CSTR account;

	} data;

} userAccount_DeveloperAppUserRegisterRequest;

C_API userAccount_DeveloperAppUserRegisterRequest *HSAPI_INIT(userAccount_DeveloperAppUserRegisterRequest);

typedef struct userAccount_DeveloperAppUserRegisterResponse 
{
	HsviewResponse base;

	struct userAccount_DeveloperAppUserRegisterResponseData
	{
		
		/** [long]用户的唯一标识 */
		int64 userId;
		/** [bool]用户是否已经存在，false-新创建，true-已经存在 */
		BOOL isExists;
 
	} data;

} userAccount_DeveloperAppUserRegisterResponse;

C_API userAccount_DeveloperAppUserRegisterResponse *HSAPI_INIT(userAccount_DeveloperAppUserRegisterResponse);

#endif
