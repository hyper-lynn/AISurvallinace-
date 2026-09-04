/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UnbindThirdpartyWeiXinAccount_H_
#define _HSVIEW_CLIENT_API_UnbindThirdpartyWeiXinAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
手机或者邮箱登录, 解绑第三方账号。

错误码
1、1128 ：解绑第三方账号和当前绑定的第三方账号不一致
【使用平台账号签名】
 */

typedef struct UnbindThirdpartyWeiXinAccountRequest 
{
	HsviewRequest base;

	struct UnbindThirdpartyWeiXinAccountRequestData
	{
		
		/** 第三方账号类型，如“taobao”，“weixin” */
		CSTR type;
		/** 第三方请求授权码 */
		CSTR authCode;
		/** 第三方颁发的应用唯一标识 */
		CSTR appId;

	} data;

} UnbindThirdpartyWeiXinAccountRequest;

C_API UnbindThirdpartyWeiXinAccountRequest *HSAPI_INIT(UnbindThirdpartyWeiXinAccountRequest);

typedef struct UnbindThirdpartyWeiXinAccountResponse 
{
	HsviewResponse base;

	struct UnbindThirdpartyWeiXinAccountResponseData
	{
		
		/** [bool] true:解绑成功, false:解绑失败 */
		BOOL result;
 
	} data;

} UnbindThirdpartyWeiXinAccountResponse;

C_API UnbindThirdpartyWeiXinAccountResponse *HSAPI_INIT(UnbindThirdpartyWeiXinAccountResponse);

#endif
