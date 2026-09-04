/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorsLinkageList_H_
#define _LC_OPENAPI_CLIENT_DoorsLinkageList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询与铃铛相关联的的所有门铃
 */

typedef struct DoorsLinkageListRequest 
{
	LCOpenApiRequest base;

	struct DoorsLinkageListRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 铃铛的ID */
		CSTR bellId;

	} data;

} DoorsLinkageListRequest;

C_API DoorsLinkageListRequest *LCOPENAPI_INIT(DoorsLinkageListRequest);

typedef struct DoorsLinkageListResponse 
{
	LCOpenApiResponse base;

	struct DoorsLinkageListResponseData
	{
		
		/** define a list with struct of DoorsLinkageListResponseData_InfosElement */
		DECLARE_LIST(struct DoorsLinkageListResponseData_InfosElement
		{
			/** 相关联的门铃ID */
			CSTR doorId;
			/** 相关联的门铃名称 */
			CSTR doorName;
		}) infos;
 
	} data;

} DoorsLinkageListResponse;

C_API DoorsLinkageListResponse *LCOPENAPI_INIT(DoorsLinkageListResponse);

#endif
