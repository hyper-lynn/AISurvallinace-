/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */

#include "api/userbindnoverify.h"
#include "LCOpenApi_Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/************************************************************************/
/* request                                                              */
/************************************************************************/
namespace LCOpenApi{
static metainfo_t *METAINFO(UserBindNoVerifyRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	UserBindNoVerifyRequest *req = (UserBindNoVerifyRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(UserBindNoVerifyRequestData),"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	UserBindNoVerifyRequest *req = (UserBindNoVerifyRequest *)p;
	
	OBJECT_CLEAR(req->data, UserBindNoVerifyRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

UserBindNoVerifyRequest *LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyRequest)
{
	UserBindNoVerifyRequest *ptr = (UserBindNoVerifyRequest *)malloc(sizeof(UserBindNoVerifyRequest));
	memset(ptr, 0, sizeof(UserBindNoVerifyRequest));
	
	if (METAINFO(UserBindNoVerifyRequestData) == NULL)
	{
		METAINFO_CREATE(UserBindNoVerifyRequestData,UserBindNoVerifyRequest);
		
		METAINFO_ADD_MEMBER(UserBindNoVerifyRequestData,UserBindNoVerifyRequest, FIELD_TYPE_CSTR, account);
		//METAINFO_ADD_MEMBER(UserBindNoVerifyRequestData, UserBindNoVerifyRequest,FIELD_TYPE_CSTR, smsCode);

	}

	ptr->base.apiname = CS("UserBindNoVerify");
	ptr->base.fullname = CS("userBindNoVerify");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/userBindNoVerify");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(UserBindNoVerifyResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	UserBindNoVerifyResponse *resp = (UserBindNoVerifyResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(UserBindNoVerifyResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	UserBindNoVerifyResponse *resp = (UserBindNoVerifyResponse *)p;
	UserBindNoVerifyResponse *resp_src = (UserBindNoVerifyResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, UserBindNoVerifyResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	UserBindNoVerifyResponse *resp = (UserBindNoVerifyResponse *)p;
	
	OBJECT_CLEAR(resp->data, UserBindNoVerifyResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

UserBindNoVerifyResponse *LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyResponse)
{
	UserBindNoVerifyResponse *ptr = (UserBindNoVerifyResponse *)malloc(sizeof(UserBindNoVerifyResponse));
	memset(ptr, 0, sizeof(UserBindNoVerifyResponse));

	if (METAINFO(UserBindNoVerifyResponseData) == NULL)
	{
		METAINFO_CREATE(UserBindNoVerifyResponseData,UserBindNoVerifyResponse);
		
		METAINFO_ADD_MEMBER(UserBindNoVerifyResponseData,UserBindNoVerifyResponse, FIELD_TYPE_INT, _nouse);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}

}