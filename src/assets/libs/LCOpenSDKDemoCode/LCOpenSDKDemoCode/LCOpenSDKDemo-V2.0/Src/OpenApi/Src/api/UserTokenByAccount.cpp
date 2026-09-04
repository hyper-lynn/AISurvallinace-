/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */

#include "api/usertokenbyaccount.h"
#include "LCOpenApi_Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/************************************************************************/
/* request                                                              */
/************************************************************************/
namespace LCOpenApi{
static metainfo_t *METAINFO(UserTokenByAccountRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	UserTokenByAccountRequest *req = (UserTokenByAccountRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(UserTokenByAccountRequestData),"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	UserTokenByAccountRequest *req = (UserTokenByAccountRequest *)p;
	
	OBJECT_CLEAR(req->data, UserTokenByAccountRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

UserTokenByAccountRequest *LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountRequest)
{
	UserTokenByAccountRequest *ptr = (UserTokenByAccountRequest *)malloc(sizeof(UserTokenByAccountRequest));
	memset(ptr, 0, sizeof(UserTokenByAccountRequest));
	
	if (METAINFO(UserTokenByAccountRequestData) == NULL)
	{
		METAINFO_CREATE(UserTokenByAccountRequestData,UserTokenByAccountRequest);
		
		METAINFO_ADD_MEMBER(UserTokenByAccountRequestData,UserTokenByAccountRequest, FIELD_TYPE_CSTR, account);

	}

	ptr->base.apiname = CS("UserTokenByAccount");
	ptr->base.fullname = CS("userTokenByAccount");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/userTokenByAccount");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(UserTokenByAccountResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	UserTokenByAccountResponse *resp = (UserTokenByAccountResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(UserTokenByAccountResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	UserTokenByAccountResponse *resp = (UserTokenByAccountResponse *)p;
	UserTokenByAccountResponse *resp_src = (UserTokenByAccountResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, UserTokenByAccountResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	UserTokenByAccountResponse *resp = (UserTokenByAccountResponse *)p;
	
	OBJECT_CLEAR(resp->data, UserTokenByAccountResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

UserTokenByAccountResponse *LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountResponse)
{
	UserTokenByAccountResponse *ptr = (UserTokenByAccountResponse *)malloc(sizeof(UserTokenByAccountResponse));
	memset(ptr, 0, sizeof(UserTokenByAccountResponse));

	if (METAINFO(UserTokenByAccountResponseData) == NULL)
	{
		METAINFO_CREATE(UserTokenByAccountResponseData,UserTokenByAccountResponse);
		
		METAINFO_ADD_MEMBER(UserTokenByAccountResponseData,UserTokenByAccountResponse, FIELD_TYPE_CSTR, userToken);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}
}