#include "Src/OpenApi/Include/api/AccessToken.h"
#include "Src/OpenApi/Include/api/UserToken.h"
#include "Src/OpenApi/Include/api/UserBindSms.h"
#include "Src/OpenApi/Include/api/UserBind.h"
#include "Src/OpenApi/Include/api/usertokenbyaccount.h"
#include "Src/OpenApi/Include/api/userbindnoverify.h"
#include "TokenCtrl.h"
using namespace LCOpenApi;

TokenCtrl::TokenCtrl()
{

}

TokenCtrl::~TokenCtrl()
{

}

int TokenCtrl::getAccessToken(const TOKEN_PARAMETERS* param, OUT QString& token, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	token = "";
	ret_code = "";
	ret_msg = "";

	if (NULL == param)
	{
		return RET_FAIL;
	}

	LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create(param->host.toStdString().c_str(), param->port);
	LCOpenApi_lcopenapi_client_set_appId(param->appId.toStdString().c_str());
	LCOpenApi_lcopenapi_client_set_appSecret(param->appSecret.toStdString().c_str());

	AccessTokenRequest *req;
	AccessTokenResponse *resp;
	req = LCOpenApi_LCOPENAPI_INIT(AccessTokenRequest);
	resp = LCOpenApi_LCOPENAPI_INIT(AccessTokenResponse);

	do
	{
		if (RET_OK != LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10))
		{
			ret = HTTP_ERR;
			DLOG("request failed\n");
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = BUSINESS_ERR;
			ret_code = resp->base.ret_code.cstr;
			ret_msg = QString::fromUtf8(resp->base.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", resp->base.ret_code.cstr);
			break;
		}

		if (NULL == resp->data.accessToken.cstr)
		{
			ret = RET_FAIL;
			DLOG("data.accessToken.cstr is null!!!\n");
			break;
		}

		token = resp->data.accessToken.cstr;
		DLOG("accessToken[%s]\n", token.toStdString().c_str());

	} while (0);

	LCOpenApi_LCOPENAPI_DESTROY(req);
	LCOpenApi_LCOPENAPI_DESTROY(resp);
	LCOpenApi_lcopenapi_client_destroy(chc);

	return ret;
}

int TokenCtrl::getUserToken(const TOKEN_PARAMETERS* param, OUT QString& token, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	token = "";
	ret_code = "";
	ret_msg = "";

	if (NULL == param)
	{
		return RET_FAIL;
	}

	LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create(param->host.toStdString().c_str(), param->port);
	LCOpenApi_lcopenapi_client_set_appId(param->appId.toStdString().c_str());
	LCOpenApi_lcopenapi_client_set_appSecret(param->appSecret.toStdString().c_str());

	/* UserTokenRequest *req;
	 UserTokenResponse *resp;
	 req = LCOpenApi_LCOPENAPI_INIT(UserTokenRequest);
	 resp = LCOpenApi_LCOPENAPI_INIT(UserTokenResponse);
	 req->data.phone = CS(param->phone.toStdString().c_str());*/

	UserTokenByAccountRequest *req;
	UserTokenByAccountResponse *resp;
	req = LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountRequest);
	resp = LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountResponse);
	req->data.account = CS(param->phone.toStdString().c_str());

	do
	{
		if (RET_OK != LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10))
		{
			ret = HTTP_ERR;
			DLOG("request failed\n");
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = BUSINESS_ERR;
			ret_code = resp->base.ret_code.cstr;
			ret_msg = QString::fromUtf8(resp->base.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", resp->base.ret_code.cstr);
			break;
		}

		if (NULL == resp->data.userToken.cstr)
		{
			ret = RET_FAIL;
			DLOG("data.userToken.cstr is null!!!\n");
			break;
		}

		token = resp->data.userToken.cstr;
		DLOG("userToken[%s]\n", token.toStdString().c_str());

	} while (0);

	LCOpenApi_LCOPENAPI_DESTROY(req);
	LCOpenApi_LCOPENAPI_DESTROY(resp);
	LCOpenApi_lcopenapi_client_destroy(chc);

	return ret;
}

int TokenCtrl::userBindSms(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	ret_code = "";
	ret_msg = "";

	if (NULL == param)
	{
		return RET_FAIL;
	}

	LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create(param->host.toStdString().c_str(), param->port);
	LCOpenApi_lcopenapi_client_set_appId(param->appId.toStdString().c_str());
	LCOpenApi_lcopenapi_client_set_appSecret(param->appSecret.toStdString().c_str());

	userBindSmsRequest *req;
	userBindSmsResponse *resp;
	req = LCOpenApi_LCOPENAPI_INIT(userBindSmsRequest);
	resp = LCOpenApi_LCOPENAPI_INIT(userBindSmsResponse);
	req->data.phone = CS(param->phone.toStdString().c_str());

	do
	{
		if (RET_OK != LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10))
		{
			ret = HTTP_ERR;
			DLOG("request failed\n");
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = BUSINESS_ERR;
			ret_code = resp->base.ret_code.cstr;
			ret_msg = QString::fromUtf8(resp->base.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", resp->base.ret_code.cstr);
			break;
		}

		DLOG("userBindSms success\n");

	} while (0);

	LCOpenApi_LCOPENAPI_DESTROY(req);
	LCOpenApi_LCOPENAPI_DESTROY(resp);
	LCOpenApi_lcopenapi_client_destroy(chc);

	return ret;
}

int TokenCtrl::userBind(const USERBIND_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	ret_code = "";
	ret_msg = "";

	if (NULL == param)
	{
		return RET_FAIL;
	}

	LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create(param->info.host.toStdString().c_str(), param->info.port);
	LCOpenApi_lcopenapi_client_set_appId(param->info.appId.toStdString().c_str());
	LCOpenApi_lcopenapi_client_set_appSecret(param->info.appSecret.toStdString().c_str());

	/* UserBindRequest *req;
	 UserBindResponse *resp;
	 req = LCOpenApi_LCOPENAPI_INIT(UserBindRequest);
	 resp = LCOpenApi_LCOPENAPI_INIT(UserBindResponse);
	 req->data.phone = CS(param->info.phone.toStdString().c_str());
	 req->data.smsCode = CS(param->smsCode.toStdString().c_str());*/

	UserBindNoVerifyRequest *req;
	UserBindNoVerifyResponse *resp;
	req = LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyRequest);
	resp = LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyResponse);
	req->data.account = CS(param->info.phone.toStdString().c_str());
	//req->data.smsCode = CS(param->smsCode.toStdString().c_str());

	do
	{
		if (RET_OK != LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10))
		{
			ret = HTTP_ERR;
			DLOG("request failed\n");
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = BUSINESS_ERR;
			ret_code = resp->base.ret_code.cstr;
			ret_msg = QString::fromUtf8(resp->base.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", resp->base.ret_code.cstr);
			break;
		}

		DLOG("userBind success\n");

	} while (0);

	LCOpenApi_LCOPENAPI_DESTROY(req);
	LCOpenApi_LCOPENAPI_DESTROY(resp);
	LCOpenApi_lcopenapi_client_destroy(chc);

	return ret;
}

