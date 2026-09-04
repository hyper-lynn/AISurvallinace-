/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_GetToken_H_
#define _HSVIEW_CLIENT_API_userAccount_GetToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
客户端通过账号、密码获取token。

客户端无法获取longitude和latitude时，客户端需要默认传0，平台判断为0时就不能处理。
【使用平台账号签名】
 */

typedef struct userAccount_GetTokenRequest 
{
	HsviewRequest base;

	struct userAccount_GetTokenRequestData
	{
		
		/** struct of userAccount_GetTokenRequestData_GpsInfo */
		struct userAccount_GetTokenRequestData_GpsInfo {
			/** [double]经度，东经0~180度，西经-180~0度 */
			double longitude;
			/** [double]纬度，北纬0~90度, 南纬-90~0度 */
			double latitude;
		} gpsInfo;

	} data;

} userAccount_GetTokenRequest;

C_API userAccount_GetTokenRequest *HSAPI_INIT(userAccount_GetTokenRequest);

typedef struct userAccount_GetTokenResponse 
{
	HsviewResponse base;

	struct userAccount_GetTokenResponseData
	{
		
		/** [O]唯一用户id */
		CSTR username;
		/** [O]大华自签发证书SaaS入口地址,使用预埋根证书组件进行接口调用的可用 */
		CSTR entryUrlV2;
		/** [O]后续用于请求签名的token */
		CSTR token;
		/** [O]客户端第一次登陆时，平台生成的全局唯一标示，后续请求头x-pcs-session-id都必须携带这个值 */
		CSTR sessionId;
		/** [O]当且仅当在用户名密码错误时，返回。而且当failNum存在时，没有其他参数 */
		CSTR failNum;
 
	} data;

} userAccount_GetTokenResponse;

C_API userAccount_GetTokenResponse *HSAPI_INIT(userAccount_GetTokenResponse);

#endif
