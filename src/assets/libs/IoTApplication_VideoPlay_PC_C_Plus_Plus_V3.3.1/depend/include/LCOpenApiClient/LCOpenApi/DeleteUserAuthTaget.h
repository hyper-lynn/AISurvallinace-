/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteUserAuthTaget_H_
#define _LC_OPENAPI_CLIENT_DeleteUserAuthTaget_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除授权对象
 */

typedef struct DeleteUserAuthTagetRequest 
{
	LCOpenApiRequest base;

	struct DeleteUserAuthTagetRequestData
	{
		
		/** [long]授权Id */
		int64 authId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteUserAuthTaget */
		#define _STATIC_DeleteUserAuthTagetRequestData_method "deleteUserAuthTaget"
		CSTR method;

	} data;

} DeleteUserAuthTagetRequest;

C_API DeleteUserAuthTagetRequest *LCOPENAPI_INIT(DeleteUserAuthTagetRequest);

typedef struct DeleteUserAuthTagetResponse 
{
	LCOpenApiResponse base;

	struct DeleteUserAuthTagetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserAuthTagetResponse;

C_API DeleteUserAuthTagetResponse *LCOPENAPI_INIT(DeleteUserAuthTagetResponse);

#endif
