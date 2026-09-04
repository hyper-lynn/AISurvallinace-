/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifySignature_H_
#define _HSVIEW_CLIENT_API_VerifySignature_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
验证签名。
RESTAPI返回值如下：
1000：验证通过。
其他：验证失败，具体看原因。

请求中的signMode目前有以下两种取值：
1：将stringToSign与账号密码组合，然后做sha1，最后结果变换为base64。适用于WSSE认证。
2：将stringToSign直接做hmacsha1，使用账号密码做密钥，最后结果变换为base64。适用于乐橙RESTAPI。
 */

typedef struct VerifySignatureRequest 
{
	HsviewRequest base;

	struct VerifySignatureRequestData
	{
		
		/** 请求方计算得到的签名 */
		CSTR signature;
		/** [int]签名方式，见接口详细说明 */
		int signMode;
		/** 用于签名的字符串 */
		CSTR stringToSign;
		/** 用户的乐橙账号 */
		CSTR account;

	} data;

} VerifySignatureRequest;

C_API VerifySignatureRequest *HSAPI_INIT(VerifySignatureRequest);

typedef struct VerifySignatureResponse 
{
	HsviewResponse base;

	struct VerifySignatureResponseData
	{
		
		/** 平台返回一个AccessToken，后续也可使用该AccessToken做认证。 */
		CSTR accessToken;
 
	} data;

} VerifySignatureResponse;

C_API VerifySignatureResponse *HSAPI_INIT(VerifySignatureResponse);

#endif
