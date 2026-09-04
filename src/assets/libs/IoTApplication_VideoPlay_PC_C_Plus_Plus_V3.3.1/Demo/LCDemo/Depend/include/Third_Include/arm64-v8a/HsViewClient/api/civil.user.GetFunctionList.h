/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFunctionList_H_
#define _HSVIEW_CLIENT_API_GetFunctionList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取账号对应的功能列表，如云存储、文件分享等。
功能项有：
	cloudStorage：云存储
	fileShare：文件分享
【需要使用平台账号认证】
 */

typedef struct GetFunctionListRequest 
{
	HsviewRequest base;

	struct GetFunctionListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetFunctionListRequest;

C_API GetFunctionListRequest *HSAPI_INIT(GetFunctionListRequest);

typedef struct GetFunctionListResponse 
{
	HsviewResponse base;

	struct GetFunctionListResponseData
	{
		
		/** 功能项 */
		DECLARE_LIST(CSTR) functions;
 
	} data;

} GetFunctionListResponse;

C_API GetFunctionListResponse *HSAPI_INIT(GetFunctionListResponse);

#endif
