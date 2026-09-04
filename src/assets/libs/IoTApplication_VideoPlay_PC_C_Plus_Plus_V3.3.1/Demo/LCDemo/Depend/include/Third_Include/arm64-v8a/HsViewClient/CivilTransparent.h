/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_CIVIL_TRANSPARENT_REQUEST_H_
#define _HSVIEW_CLIENT_CIVIL_TRANSPARENT_REQUEST_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加配件。
【需要使用平台账号签名】
 */

typedef struct CivilTransparentRequest 
{
	HsviewRequest base;

	struct CivilTransparentRequestData
	{
		CSTR method;
		CSTR apiName;
		CSTR jsonString;
	} data;

} CivilTransparentRequest;

C_API CivilTransparentRequest *HSAPI_INIT(CivilTransparentRequest);

typedef struct CivilTransparentResponse 
{
	HsviewResponse base;

	struct CivilTransparentData
	{
		CSTR jsonString;
	} data;

} CivilTransparentResponse;

C_API CivilTransparentResponse *HSAPI_INIT(CivilTransparentResponse);

#endif
