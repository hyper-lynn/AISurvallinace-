/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSignDomain_H_
#define _HSVIEW_CLIENT_API_GetSignDomain_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取需要签名的地址或者ip列表,如：www.lechangebug.com或者121.10.223.188

请求参数说明：
鉴权版本authVersion：取值范围是V1.0、V2.0，
authVersion为空或者不存在表示V1.0

authVersion=V1.0表示乐橙APP只支持第一版lc_mall_m的鉴权方式，响应中返回的clientId为lc_mall_m。
authVersion=V2.0表示乐橙APP支持第一版lc_mall_m和第二版lc_app的鉴权方式，平台根据当前支持的版本返回相应的clientId和authVersion，客户端根据平台返回的鉴权方式来选择走第一版或者第二版的鉴权流程。

【不鉴权】
 */

typedef struct GetSignDomainRequest 
{
	HsviewRequest base;

	struct GetSignDomainRequestData
	{
		
		/** [O]鉴权版本，可选 */
		CSTR authVersion;

	} data;

} GetSignDomainRequest;

C_API GetSignDomainRequest *HSAPI_INIT(GetSignDomainRequest);

typedef struct GetSignDomainResponse 
{
	HsviewResponse base;

	struct GetSignDomainResponseData
	{
		
		/** define a list with struct of GetSignDomainResponseData_DomainsElement */
		DECLARE_LIST(struct GetSignDomainResponseData_DomainsElement
		{
			/** 地址,www.lechangebuy.com或者域名对应的ip */
			CSTR host;
			/** 颁发给客户端访问这个地址时用于签名的id */
			CSTR clientId;
			/** oauth地址 */
			CSTR oauthAddress;
			/** 鉴权版本 */
			CSTR authVersion;
			/** 授权成功后302重定向url */
			CSTR redirectUri;
		}) domains;
 
	} data;

} GetSignDomainResponse;

C_API GetSignDomainResponse *HSAPI_INIT(GetSignDomainResponse);

#endif
