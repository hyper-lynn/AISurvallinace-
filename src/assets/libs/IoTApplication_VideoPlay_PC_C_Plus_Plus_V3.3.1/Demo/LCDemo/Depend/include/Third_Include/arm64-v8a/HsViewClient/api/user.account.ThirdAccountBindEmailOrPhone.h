/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ThirdAccountBindEmailOrPhone_H_
#define _HSVIEW_CLIENT_API_userAccount_ThirdAccountBindEmailOrPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
第三方账号绑定乐橙用户。
设置密码的usage： SetUserPassword
错误码参见:https://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E9%94%99%E8%AF%AF%E7%A0%81.md&s=pj

海外需求: 用户在绑定邮箱/手机号时,如果该邮箱已经注册, 需要提示用户,用户确认后再将两个帐号合并.
	* app 第一次调用时, merge = 0. 服务端检测到邮箱/手机号已经绑定,返回错误, 错误码 12003, 12004, 12005
	* app 第二次调用时, merge = 1. areaCode 填写第一次的 areaCode. (第二次调用需要在验证码有效期内, 第一次调用后会更新areaCode的有效期)



【使用账号签名】
 */

typedef struct userAccount_ThirdAccountBindEmailOrPhoneRequest 
{
	HsviewRequest base;

	struct userAccount_ThirdAccountBindEmailOrPhoneRequestData
	{
		
		/** [O]验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, phone、email */
		CSTR type;
		/** 国际区号,海外需要该字段，且type为phone时填写 */
		CSTR areaCode;
		/** [int][O] 如果该帐号已经存在,是否合并.海外需要该字段, 0-不合并, 1-合并. 如果不存在默认为 1-合并 */
		int merge;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_ThirdAccountBindEmailOrPhoneRequest;

C_API userAccount_ThirdAccountBindEmailOrPhoneRequest *HSAPI_INIT(userAccount_ThirdAccountBindEmailOrPhoneRequest);

typedef struct userAccount_ThirdAccountBindEmailOrPhoneResponse 
{
	HsviewResponse base;

	struct userAccount_ThirdAccountBindEmailOrPhoneResponseData
	{
		
		/** [O]用户昵称 */
		CSTR nickname;
		/** [O]用户头像URL */
		CSTR avatarUrl;
		/** [O]用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;
		/** [O] 只会在 account 没有注册过平台账号的情况下返回， 用于设置密码事校验使用，有效期15分钟(可配置) */
		CSTR setPasswordValidCode;
		/** [long][O]用户账号ID */
		int64 userId;
		/** [O]用户头像的md5值 */
		CSTR avatarMD5;
 
	} data;

} userAccount_ThirdAccountBindEmailOrPhoneResponse;

C_API userAccount_ThirdAccountBindEmailOrPhoneResponse *HSAPI_INIT(userAccount_ThirdAccountBindEmailOrPhoneResponse);

#endif
