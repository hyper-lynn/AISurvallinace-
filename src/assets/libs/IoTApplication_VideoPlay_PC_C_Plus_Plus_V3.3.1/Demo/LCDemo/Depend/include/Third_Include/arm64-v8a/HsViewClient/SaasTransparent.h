/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_SAAS_TRANSPARENT_REQUEST_H_
#define _HSVIEW_CLIENT_SAAS_TRANSPARENT_REQUEST_H_

#include "HsviewClientSdk.h"

typedef struct SaasTransparentRequest 
{
	HsviewRequest base;

	struct SaasTransparentRequestData
	{
		CSTR method;
		CSTR apiName;
		CSTR jsonString;
	} data;

} SaasTransparentRequest;

C_API SaasTransparentRequest *HSAPI_INIT(SaasTransparentRequest);

typedef struct SaasTransparentResponse 
{
	HsviewResponse base;

	struct SaasTransparentData
	{
		CSTR jsonString;
	} data;

} SaasTransparentResponse;

C_API SaasTransparentResponse *HSAPI_INIT(SaasTransparentResponse);

#endif
