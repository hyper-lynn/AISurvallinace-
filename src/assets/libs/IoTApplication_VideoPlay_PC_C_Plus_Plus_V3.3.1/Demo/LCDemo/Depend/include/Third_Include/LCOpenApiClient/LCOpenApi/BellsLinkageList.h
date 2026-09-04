/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BellsLinkageList_H_
#define _LC_OPENAPI_CLIENT_BellsLinkageList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询与门铃相关联的的所有铃铛
 */

typedef struct BellsLinkageListRequest 
{
	LCOpenApiRequest base;

	struct BellsLinkageListRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃的ID */
		CSTR doorId;

	} data;

} BellsLinkageListRequest;

C_API BellsLinkageListRequest *LCOPENAPI_INIT(BellsLinkageListRequest);

typedef struct BellsLinkageListResponse 
{
	LCOpenApiResponse base;

	struct BellsLinkageListResponseData
	{
		
		/** define a list with struct of BellsLinkageListResponseData_InfosElement */
		DECLARE_LIST(struct BellsLinkageListResponseData_InfosElement
		{
			/** 铃铛的名称 */
			CSTR bellName;
			/** 铃铛的ID */
			CSTR bellId;
		}) infos;
 
	} data;

} BellsLinkageListResponse;

C_API BellsLinkageListResponse *LCOPENAPI_INIT(BellsLinkageListResponse);

#endif
