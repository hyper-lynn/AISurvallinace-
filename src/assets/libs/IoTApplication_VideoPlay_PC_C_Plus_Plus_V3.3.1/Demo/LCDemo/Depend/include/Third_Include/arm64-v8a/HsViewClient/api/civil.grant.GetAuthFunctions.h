/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAuthFunctions_H_
#define _HSVIEW_CLIENT_API_GetAuthFunctions_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取权限列表
【需要使用平台账号签名】

 */

typedef struct GetAuthFunctionsRequest 
{
	HsviewRequest base;

	struct GetAuthFunctionsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetAuthFunctionsRequest;

C_API GetAuthFunctionsRequest *HSAPI_INIT(GetAuthFunctionsRequest);

typedef struct GetAuthFunctionsResponse 
{
	HsviewResponse base;

	struct GetAuthFunctionsResponseData
	{
		
		/** define a list with struct of GetAuthFunctionsResponseData_AuthFunctionsElement */
		DECLARE_LIST(struct GetAuthFunctionsResponseData_AuthFunctionsElement
		{
			/** 权限标示 */
			CSTR function;
			/** 权限描述 */
			CSTR remark;
		}) authFunctions;
 
	} data;

} GetAuthFunctionsResponse;

C_API GetAuthFunctionsResponse *HSAPI_INIT(GetAuthFunctionsResponse);

#endif
