/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_Login_H_
#define _HSVIEW_CLIENT_API_userAccount_Login_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
客户端登录接口。
客户端调用登录接口前，必须先调用GetToken接口来获取token。


thirdAccounts：第三方账户信息，不存在表示没有绑定第三方授权账户。

【使用平台账号签名】
 */

typedef struct userAccount_LoginRequest 
{
	HsviewRequest base;

	struct userAccount_LoginRequestData
	{
		
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;

	} data;

} userAccount_LoginRequest;

C_API userAccount_LoginRequest *HSAPI_INIT(userAccount_LoginRequest);

typedef struct userAccount_LoginResponse 
{
	HsviewResponse base;

	struct userAccount_LoginResponseData
	{
		
		/** [O]用户昵称 */
		CSTR nickname;
		/** [O]大华自签发证书SaaS入口地址,使用预埋根证书组件进行接口调用的可用 */
		CSTR entryUrlV2;
		/** [O]用户头像URL */
		CSTR avatarUrl;
		/** [O]用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;
		/** [O]SaaS入口地址（挂载第三方机构颁发证书，web和第三方应用回调等使用） */
		CSTR entryUrl;
		/** [O]用户国家名称 */
		CSTR countryName;
		/** [long]用户账号ID */
		int64 userId;
		/** [O]用户邮箱 */
		CSTR email;
		/** [O]用户头像的md5值 */
		CSTR avatarMD5;
		/** define a list with struct of userAccount_LoginResponseData_ThirdAccountsElement */
		DECLARE_LIST(struct userAccount_LoginResponseData_ThirdAccountsElement
		{
			/** 第三方昵称 */
			CSTR nickname;
			/** 微信, 取值为：weixin、facebook、apple */
			CSTR type;
		}) thirdAccounts;
		/** [bool][O]是否存在密码 */
		BOOL hasPwd;
		/** [O]用户手机号码 */
		CSTR phone;
		/** [O]用户手机号区号，海外手机号注册的用户会返回该字段 */
		CSTR areaCode;
 
	} data;

} userAccount_LoginResponse;

C_API userAccount_LoginResponse *HSAPI_INIT(userAccount_LoginResponse);

#endif
